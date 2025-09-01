#include<bits/stdc++.h>
#include<x86intrin.h>
using namespace std;


// Internally, the numbers are stored in binary in little endian order.
// Negative numbers are assumed to have infinite leading ones, represented in two's complement.
// No leading ~0 allowed for negative numbers, and no leading 0 allowed for non-negative numbers. This ensures that each integer has a unique representation.
struct bigint{
	using T = unsigned long long;
	using T_large = __uint128_t;
	static constexpr signed int width = 8 * sizeof(T);
	static constexpr T pad[2] = {T(0), ~T(0)};
	bool sign = 0; // 0 (non-negative), 1 (negative)
	vector<T> data;
	void _trim(){
		while(!data.empty() && data.back() == pad[sign]) data.pop_back();
	}
	bool _is_valid() const{
		return data.empty() || data.back() != pad[sign];
	}
	// Assumes x is non-zero
	static void _negate(vector<T> &x){
		for(auto &d: x) d = ~d;
		int i = 0;
		while(i < (int)x.size() && !~x[i]) x[i ++] = 0;
		if(i == (int)x.size()) x.push_back(1);
		else ++ x[i];
	}
	static void _add_apply(bool &xsign, vector<T> &x, bool ysign, const vector<T> &y){
		if(!ysign && y.empty()) return;
		if(x.size() < y.size()) x.resize(y.size(), pad[xsign]);
		unsigned char carry = 0;
		for(auto i = 0; i < (int)y.size(); ++ i) carry = _addcarry_u64(carry, x[i], y[i], &x[i]);
		for(auto i = (int)y.size(); i < (int)x.size() && carry != ysign; ++ i) carry = _addcarry_u64(carry, x[i], pad[ysign], &x[i]);
		if(carry != ysign){
			if(xsign == ysign) x.push_back(pad[xsign] << 1 | carry);
			else xsign = !xsign;
		}
	}
	static void _subtract_apply(bool &xsign, vector<T> &x, bool ysign, const vector<T> &y){
		if(!ysign && y.empty()) return;
		if(x.size() < y.size()) x.resize(y.size(), pad[xsign]);
		unsigned char borrow = 0;
		for(auto i = 0; i < (int)y.size(); ++ i) borrow = _subborrow_u64(borrow, x[i], y[i], &x[i]);
		for(auto i = (int)y.size(); i < (int)x.size() && borrow != ysign; ++ i) borrow = _subborrow_u64(borrow, x[i], pad[ysign], &x[i]);
		if(borrow != ysign){
			if(xsign == ysign) xsign = !xsign;
			else x.push_back(pad[xsign] ^ 1);
		}
	}
	// Assumes both x and y are positive.
	static vector<T> _naive_multiplication(const vector<T> &x, const vector<T> &y){
		if(x.empty() || y.empty()) return {};
		vector<T> z(x.size() + y.size() - 1);
		for(auto i = 0; i < (int)x.size(); ++ i) for(auto j = 0; j < (int)y.size(); ++ j){
			T_large rem = (T_large)x[i] * y[j];
			for(auto k = i + j; rem; ++ k){
				if((int)z.size() <= k) z.push_back(0);
				rem += z[k];
				z[k] = rem & ~T(0);
				rem >>= width;
			}
		}
		return z;
	}
	template<int karatsuba_threshold = 90>
	static vector<T> _karatsuba_multiplication(const vector<T> &x, const vector<T> &y){
		int n = (int)x.size(), m = (int)y.size();
		if(min(n, m) <= karatsuba_threshold) return _naive_multiplication(x, y);
		int split = min(max(n, m) >> 1, min(n, m));
		vector<T> x0(x.begin(), x.begin() + split), x1(x.begin() + split, x.end());
		vector<T> y0(y.begin(), y.begin() + split), y1(y.begin() + split, y.end());
		auto z0 = _karatsuba_multiplication(x0, y0);
		auto z2 = _karatsuba_multiplication(x1, y1);
		bool temp = 0;
		_add_apply(temp, x0, temp, x1);
		_add_apply(temp, y0, temp, y1);
		auto z1 = _karatsuba_multiplication(x0, y0);
		_subtract_apply(temp, z1, temp, z0);
		_subtract_apply(temp, z1, temp, z2);
		z1.insert(z1.begin(), split, 0);
		z2.insert(z2.begin(), split << 1, 0);
		_add_apply(temp, z2, temp, z1);
		_add_apply(temp, z2, temp, z0);
		return z2;
	}
	// TODO: implement Toom-Cook, and Schönhage–Strassen
	static vector<T> _multiply(const vector<T> &x, const vector<T> &y){
		return _karatsuba_multiplication(x, y);
	}
	bigint(){ }
	template<class U, typename enable_if<is_integral_v<U>>::type* = nullptr>
	bigint(U x){
		if(x < 0){
			*this = -bigint(-x);
			return;
		}
		while(x){
			data.push_back(x & ~T(0));
			x /= T_large(1) << width;
		}
	}
	template<class U, typename enable_if<is_floating_point_v<U>>::type* = nullptr>
	bigint(U x): bigint(llround(x)){ }
	// MSB at a.back()
	template<class U, typename enable_if<is_integral_v<U>>::type* = nullptr>
	bigint(bool sign, const vector<U> &a, U base){
		bigint x{};
		for(auto d: a){
			assert(0 <= d && d < base);
			x = base * x + d;
		}
		*this = sign ? -x : x;
	}
	// MSB at s.front()
	bigint(const string &s, unsigned int base){
		assert(base >= 2);
		int pos = 0;
		while(pos < (int)s.size() && (s[pos] == '-' || s[pos] == '+')){
			if(s[pos] == '-') sign = !sign;
			++ pos;
		}
		assert(pos < (int)s.size());
		if(base == 2){
			for(auto i = (int)s.size() - 1; i >= pos; i -= width){
				T x = 0;
				for(auto j = max(pos, i - width + 1); j <= i; ++ j){
					assert('0' <= s[j] && s[j] <= '1');
					x = x << 1 | s[j] - '0';
				}
				data.push_back(x);
			}
			while(!data.empty() && !data.back()) data.pop_back();
		}
		else if(base <= 10){
			bigint x{};
			for(auto i = pos; i < (int)s.size(); ++ i){
				assert(isdigit(s[i]));
				x = base * x + (s[i] - '0');
			}
			if(sign) x = -x;
			*this = x;
		}
		else if(base == 16){
			// 0, ..., 9, A, B, C, D, E, F
			bigint x{};
			for(auto i = pos; i < (int)s.size(); ++ i){
				assert(isdigit(s[i]) || isupper(s[i]) && s[i] <= 'F');
				x = base * x + (isdigit(s[i]) ? s[i] - '0' : s[i] - 'A' + 10);
			}
			if(sign) x = -x;
			*this = x;
		}
		else assert(false);
		_trim();
		assert(_is_valid());
	}
	bool has_single_bit() const{
		assert(sign == 0);
		int cnt = 0;
		for(auto x: data){
			cnt += __builtin_popcountll(x);
			if(cnt == 2) return false;
		}
		return cnt == 1;
	}
	int bit_width() const{
		assert(sign == 0);
		if(data.empty()) return 0;
		return __lg(data.back()) + 64 * ((int)data.size() - 1) + 1;
	}
	bigint bit_ceil() const{
		if(*this <= 1) return bigint{1};
		return bigint{1} << (*this - 1).bit_width();
	}
	bigint bit_floor() const{
		if(*this == 0) return 0;
		return bigint{1} << this->bit_width() - 1;
	}
	int popcount() const{
		assert(sign == 0);
		int cnt = 0;
		for(auto x: data) cnt += __builtin_popcountll(x);
		return cnt;
	}
	int countr_zero() const{
		assert(sign == 0);
		int res = 0;
		for(auto i = 0; i < (int)data.size(); ++ i){
			if(data[i]){
				res += __builtin_ctzll(data[i]);
				break;
			}
			res += 64;
		}
		return res;
	}
	int countr_one() const{
		assert(sign == 0);
		int res = 0;
		for(auto i = 0; i < (int)data.size(); ++ i){
			if(data[i] != ~T{0}){
				res += __builtin_ctzll(~data[i]);
				break;
			}
			res += 64;
		}
		return res;
	}
	int find_first() const{
		assert(sign == 0);
		if(!*this) return numeric_limits<int>::max();
		int i = 0;
		while(!data[i]) ++ i;
		return 64 * i + __builtin_ctzll(data[i]);
	}
	int find_next(int pos) const{
		assert(sign == 0);
		assert(0 <= pos);
		int b = (pos + 1) / 64;
		if(b >= (int)data.size()) return numeric_limits<int>::max();
		if(data[b] >> (pos + 1) % 64) return __builtin_ctzll(data[b] >> (pos + 1) % 64) + pos + 1;
		++ b;
		while(!data[b]) ++ b;
		return 64 * b + __builtin_ctzll(data[b]);
	}
	int find_last() const{
		assert(sign == 0);
		if(!*this) return -1;
		return 64 * ((int)data.size() - 1) + __builtin_ctzll(data.back());
	}
	int find_prev(int pos) const{
		assert(sign == 0);
		assert(0 <= pos);
		if(!*this) return -1;
		int b = pos / 64;
		if(b >= (int)data.size()) return 64 * ((int)data.size() - 1) + __builtin_ctzll(data.back());
		if(data[b] << 64 - pos) return __lg(data[b] << 64 - pos >> 64 - pos) + 64 * b;
		-- b;
		while(b >= 0 && !data[b]) -- b;
		return b >= 0 ? __builtin_ctzll(data[b]) : -1;
	}
	bool operator[](int pos) const{
		assert(sign == 0);
		assert(0 <= pos);
		if(pos / 64 < (int)data.size()) return data[pos / 64] >> pos % 64 & 1;
		return false;
	}
	void set(int pos, bool x){
		assert(sign == 0);
		assert(0 <= pos);
		if(pos / 64 < (int)data.size()) if((data[pos / 64] >> pos % 64 & 1) != x) data[pos / 64] ^= T{1} << pos % 64;
		else if(x){
			data.resize(pos / 64 + 1, pad[sign]);
			data[pos / 64] ^= T{1} << pos % 64;
		}
	}
	// MSB at back()
	template<class U, typename enable_if<is_integral_v<U>>::type* = nullptr>
	friend pair<bool, vector<U>> to_vector(const bigint &x, U base){
		assert(base >= 2);
		if(x < 0) return {1, to_vector(-x, base).second};
		vector<U> v;
		for(auto y = x; y; y /= base) v.push_back(y % base);
		return {0, v};
	}
	// TODO: Implement Schoenhage
	// MSB at front()
	friend string to_string(const bigint &x, unsigned int base){
		assert(base >= 2);
		if(!x) return "0";
		if(x < 0) return '-' + to_string(-x, base);
		if(base == 2){
			string s;
			for(int i = __lg(x.data.back()); i >= 0; -- i) s.push_back('0' + (x.data.back() >> i & 1));
			for(auto i = (int)x.data.size() - 2; i >= 0; -- i) s += bitset<width>(x.data[i]).to_string();
			return s;
		}
		else if(base <= 10){
			string s;
			for(auto y = x; y; y /= base) s.push_back('0' + int(y % base));
			reverse(s.begin(), s.end());
			return s;
		}
		else if(base == 16){
			// 0, ..., 9, A, B, C, D, E, F
			string s;
			for(auto y = x; y; y /= base){
				int rem = y % base;
				s.push_back(rem < 10 ? '0' + rem : rem - 10 + 'A');
			}
			reverse(s.begin(), s.end());
			return s;
		}
		else assert(false);
	}
	friend ostream &operator<<(ostream &out, const bigint &x){
		return out << to_string(x, 10);
	}
	operator bool() const{
		return sign || !data.empty();
	}
	template<class U, typename enable_if<is_integral_v<U> && !is_same<U, bool>::value>::type* = nullptr>
	operator U() const{
		U x = 0;
		if(!sign) for(auto i = (int)data.size() - 1; i >= 0; -- i) x = x << min<int>(width, sizeof(U)) | data[i];
		else x = -U(-*this);
		return x;
	}
	template<class U, typename enable_if<is_floating_point_v<U>>::type* = nullptr>
	operator U() const{
		U x = 0;
		if(!sign) for(auto i = (int)data.size() - 1; i >= 0; -- i) x = x * (T_large(1) << width) + data[i];
		else x = -U(-*this);
		return x;
	}
	bool operator==(const bigint &x) const{ return sign == x.sign && data == x.data; }
	bool operator!=(const bigint &x) const{ return !(*this == x); }
	bool operator<(const bigint &x) const{
		if(sign != x.sign) return sign > x.sign;
		if(!x) return false;
		if(data.size() != x.data.size()) return data.size() < x.data.size() ^ sign;
		for(auto i = (int)data.size() - 1; i >= 0; -- i) if(data[i] != x.data[i]) return data[i] < x.data[i];
		return false;
	}
	bool operator<=(const bigint &x) const{ return !(x < *this); }
	bool operator>=(const bigint &x) const{ return !(*this < x); }
	bool operator>(const bigint &x) const{ return x < *this; }
#define COMPARE_OP(OP)\
template<class U, typename enable_if<is_integral_v<U>>::type* = nullptr>\
bool operator OP(U x) const{\
	return *this OP bigint(x);\
}\
template<class U, typename enable_if<is_integral_v<U>>::type* = nullptr>\
friend bool operator OP(U x, const bigint &y){\
	return bigint(x) OP y;\
}
// TODO: Make this more efficient
COMPARE_OP(==) COMPARE_OP(!=) COMPARE_OP(<) COMPARE_OP(<=) COMPARE_OP(>=) COMPARE_OP(>)
#undef COMPARE_OP
	bigint &operator>>=(const bigint &_x){
		assert(0 <= _x && _x <= numeric_limits<int>::max());
		int x = int(_x);
		if(x == 0) return *this;
		if((int)data.size() <= x / 64){
			data.clear();
			return *this;
		}
		data.erase(data.begin(), data.begin() + x / 64);
		data.push_back(pad[sign]);
		x %= 64;
		for(auto i = 0; i < (int)data.size() - 1; ++ i) data[i] = data[i + 1] << 64 - x | data[i] >> x;
		_trim();
		return *this;
	}
	bigint operator>>(const bigint &x) const{
		return bigint(*this) >>= x;
	}
	bigint &operator<<=(const bigint &_x){
		assert(0 <= _x && _x <= numeric_limits<int>::max());
		int x = int(_x);
		if(x == 0) return *this;
		data.insert(data.begin(), x / 64, T{0});
		data.push_back(pad[sign]);
		const int upto = x / 64;
		x %= 64;
		for(auto i = (int)data.size() - 1; i >= upto; -- i) data[i] = data[i] << x | (i > 0 ? data[i - 1] >> 64 - x : T{0});
		_trim();
		return *this;
	}
	bigint operator<<(const bigint &x) const{
		return bigint(*this) <<= x;
	}
	bigint &operator&=(const bigint &x){
		if(data.size() < x.data.size()) data.resize(x.data.size(), pad[sign]);
		for(auto i = 0; i < (int)x.data.size(); ++ i) data[i] &= x.data[i];
		if(!x.sign) data.resize(x.data.size());
		sign &= x.sign;
		_trim();
		return *this;
	}
	bigint operator&(const bigint &x) const{
		return bigint(*this) &= x;
	}
	bigint &operator|=(const bigint &x){
		if(data.size() < x.data.size()) data.resize(x.data.size(), pad[sign]);
		for(auto i = 0; i < (int)x.data.size(); ++ i) data[i] |= x.data[i];
		if(x.sign) data.resize(x.data.size());
		sign |= x.sign;
		_trim();
		return *this;
	}
	bigint operator|(const bigint &x) const{
		return bigint(*this) |= x;
	}
	bigint &operator^=(const bigint &x){
		if(data.size() < x.data.size()) data.resize(x.data.size(), pad[sign]);
		for(auto i = 0; i < (int)x.data.size(); ++ i) data[i] ^= x.data[i];
		if(x.sign) for(auto i = (int)x.data.size(); i < (int)data.size(); ++ i) data[i] = ~data[i];
		sign ^= x.sign;
		_trim();
		return *this;
	}
	bigint operator^(const bigint &x) const{
		return bigint(*this) ^= x;
	}
	bigint operator+() const{
		return *this;
	}
	bigint operator-() const{
		if(!*this) return *this;
		bigint x(*this);
		x.sign = !x.sign;
		_negate(x.data);
		x._trim();
		return x;
	}
	friend bigint abs(bigint x){
		return x.sign ? -x : x;
	}
	bigint &operator+=(const bigint &x){
		if(!x) return *this;
		if(!*this) return *this = x;
		_add_apply(sign, data, x.sign, x.data);
		_trim();
		return *this;
	}
	bigint operator+(const bigint &x) const{
		return bigint(*this) += x;
	}
	bigint &operator-=(const bigint &x){
		if(!x) return *this;
		if(!*this) return *this = -x;
		_subtract_apply(sign, data, x.sign, x.data);
		_trim();
		return *this;
	}
	bigint operator-(const bigint &x) const{
		return bigint(*this) -= x;
	}
	bigint &operator++(){
		unsigned char carry = 1;
		for(auto i = 0; i < (int)data.size() && carry; ++ i) carry = _addcarry_u64(carry, data[i], 0ULL, &data[i]);
		if(carry){
			if(!sign) data.push_back(1);
			else sign = !sign;
		}
		_trim();
		return *this;
	}
	bigint operator++(int){
		bigint x = *this;
		++ *this;
		return x;
	}
	bigint &operator--(){
		unsigned char borrow = 1;
		for(auto i = 0; i < (int)data.size() && borrow; ++ i) borrow = _subborrow_u64(borrow, data[i], 0ULL, &data[i]);
		if(borrow){
			if(!sign) sign = !sign;
			else data.push_back(pad[sign] ^ 1);
		}
		_trim();
		return *this;
	}
	bigint operator--(int){
		bigint x = *this;
		-- *this;
		return x;
	}
	bigint &operator*=(const bigint &x){
		if(!*this || !x) return *this = bigint();
		data = _multiply(abs(*this).data, abs(x).data);
		sign ^= x.sign;
		if(sign) _negate(data);
		_trim();
		return *this;
	}
	bigint operator*(const bigint &x) const{
		return bigint(*this) *= x;
	}
	template<class U, typename enable_if<is_integral_v<U>>::type* = nullptr>
	bigint &inplace_power(U e){
		assert(e >= 0);
		bigint res(1);
		for(; e; e >>= 1, *this *= *this) if(e & 1) res *= *this;
		return *this = res;
	}
	template<class U, typename enable_if<is_integral_v<U>>::type* = nullptr>
	bigint power(U e) const{
		return bigint(*this).inplace_power(e);
	}
	static pair<vector<T>, T> small_div(const vector<T> &x, T y){
		assert(y);
		T_large rem = 0;
		vector<T> q((int)x.size());
		for(auto i = (int)x.size() - 1; i >= 0; -- i){
			rem = rem << width | x[i];
			q[i] = rem / y;
			rem = rem % y;
		}
		return {q, rem};
	}
	// Todo: Implement Burnikel-Ziegler
	// Assumes x is non-negative and y is positive
	// Returns {quotient, remainder} pair
	static pair<vector<T>, vector<T>> large_div(const vector<T> &x, const vector<T> &y){
		assert(!y.empty());
		int m = (int)x.size(), n = (int)y.size();
		if(m < n) return {{}, x};
		if(n == 1){
			auto [q, r] = small_div(x, y[0]);
			return {q, {r}};
		}
		vector<T> q(m - n + 1), r(n), xn(m + 1), yn(n);
		T_large qhat, rhat, p;
		int s = __builtin_clzll(y[n - 1]);
		for(auto i = n - 1; i > 0; -- i) yn[i] = y[i] << s | (T_large)y[i - 1] >> width - s;
		yn[0] = y[0] << s;
		xn[m] = (T_large)x[m - 1] >> width - s;
		for(auto i = m - 1; i > 0; -- i) xn[i] = x[i] << s | (T_large)x[i - 1] >> width - s;
		xn[0] = x[0] << s;
		__int128_t t, k;
		static const T_large base = T_large(1) << width;
		for(auto j = m - n; j >= 0; -- j){
			qhat = (xn[j + n] * base + xn[j + n - 1]) / yn[n - 1];
			rhat = (xn[j + n] * base + xn[j + n - 1]) % yn[n - 1];
			FLAG:
			if(qhat >= base || (T)qhat * (T_large)yn[n - 2] > base * rhat + xn[j + n - 2]){
				-- qhat;
				rhat += yn[n - 1];
				if(rhat < base) goto FLAG;
			}
			k = 0;
			for(auto i = 0; i < n; ++ i){
				p = (T)qhat * (T_large)yn[i];
				t = xn[i + j] - k - (p & base - 1);
				xn[i + j] = t;
				k = (p >> width) - (t >> width);
			}
			t = xn[j + n] - k;
			xn[j + n] = t;
			q[j] = qhat;
			if(t < 0){
				-- q[j];
				k = 0;
				for(auto i = 0; i < n; ++ i){
					t = (T_large)xn[i + j] + yn[i] + k;
					xn[i + j] = t;
					k = t >> width;
				}
				xn[j + n] += k;
			}
		}
		if(!r.empty()){
			for(auto i = 0; i < n - 1; ++ i) r[i] = xn[i] >> s | (T_large)xn[i + 1] << width - s;
			r[n - 1] = xn[n - 1] >> s;
		}
		return {q, r};
	}
	friend pair<bigint, bigint> bigint_div(const bigint &x, const bigint &y){
		assert(y);
		bigint q, r;
		tie(q.data, r.data) = large_div(abs(x).data, abs(y).data);
		q.sign = x.sign ^ y.sign;
		r.sign = x.sign;
		while(!q.data.empty() && !q.data.back()) q.data.pop_back();
		if(q.data.empty()) q.sign = 0;
		else if(q.sign) _negate(q.data);
		while(!r.data.empty() && !r.data.back()) r.data.pop_back();
		if(r.data.empty()) r.sign = 0;
		else if(r.sign) _negate(r.data);
		q._trim();
		r._trim();
		if(x.sign != y.sign && r){
			-- q;
			r += y;
		}
		return {q, r};
	}
	bigint &operator/=(const bigint &x){
		return *this = bigint_div(*this, x).first;
	}
	bigint operator/(const bigint &x) const{
		return bigint(*this) /= x;
	}
	bigint &operator%=(const bigint &x){
		return *this = bigint_div(*this, x).second;
	}
	bigint operator%(const bigint &x) const{
		return bigint(*this) %= x;
	}
#define BINARY_OP(APPLY_OP, OP)\
template<class U, typename enable_if<is_integral_v<U>>::type* = nullptr>\
bigint &operator APPLY_OP(U x){\
	return *this APPLY_OP bigint(x);\
}\
template<class U, typename enable_if<is_integral_v<U>>::type* = nullptr>\
bigint operator OP(U x) const{\
	return bigint(*this) APPLY_OP bigint(x);\
}\
template<class U, typename enable_if<is_integral_v<U>>::type* = nullptr>\
friend bigint operator OP(U x, const bigint &y){\
	return bigint(y) APPLY_OP bigint(x);\
}
// TODO: Make this more efficient
BINARY_OP(>>=, >>) BINARY_OP(<<=, <<) BINARY_OP(&=, &) BINARY_OP(|=, |) BINARY_OP(^=, ^) BINARY_OP(+=, +) BINARY_OP(-=, -) BINARY_OP(*=, *) BINARY_OP(/=, /) BINARY_OP(%=, %)
#undef BINARY_OP
	// TODO: Implement half-gcd
	friend bigint gcd(const bigint &x, const bigint &y){
		if(x.sign || y.sign) return gcd(abs(x), abs(y));
		return y ? gcd(y, x % y) : x;
	}
	friend bigint lcm(const bigint &x, const bigint &y){
		if(x.sign || y.sign) return lcm(abs(x), abs(y));
		return x / gcd(x, y) * y;
	}
	template<class Iter>
	static bigint sum(Iter begin, Iter end){
		int n = end - begin;
		vector<bigint> temp(n << 1);
		for(auto i = 0; i < n; ++ i) temp[n + i] = *(begin + i);
		for(auto i = n - 1; i >= 1; -- i) temp[i] = temp[i << 1] + temp[i << 1 | 1];
		bigint res = 0;
		for(auto l = n, r = n << 1; l < r; l >>= 1, r >>= 1){
			if(l & 1) res += temp[l ++];
			if(r & 1) res += temp[-- r];
		}
		return res;
	}
	template<class Iter>
	static bigint product(Iter begin, Iter end){
		int n = end - begin;
		vector<bigint> temp(n << 1);
		for(auto i = 0; i < n; ++ i) temp[n + i] = *(begin + i);
		for(auto i = n - 1; i >= 1; -- i) temp[i] = temp[i << 1] * temp[i << 1 | 1];
		bigint res = 1;
		for(auto l = n, r = n << 1; l < r; l >>= 1, r >>= 1){
			if(l & 1) res *= temp[l ++];
			if(r & 1) res *= temp[-- r];
		}
		return res;
	}
#if __cplusplus > 201703L
	template<ranges::random_access_range R>
	static bigint sum(R &&r){
		return sum(r.begin(), r.end());
	}
	template<ranges::random_access_range R>
	static bigint product(R &&r){
		return product(r.begin(), r.end());
	}
#endif
};

#define int long long 
#define pii pair<int,int>
int inv(int a,int mod){
    int res=1,n=mod-2;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
 
const int maxn = 2e5+5;
const int inf = 1e18;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

int D=0;
bigint A[105];

void init(){
    string C;cin >> C;
    int n=(int)C.size();C+='.';
    auto get = [&](int i){
        bigint x=0;
        while(C[i]>='0' && C[i]<='9') x=x*10+C[i++]-'0';
        return make_pair(i,x);
    };

    int i=0;
    while(i<n){
        int sign=1;
        if(C[i]=='-') sign=-1;
        if(C[i]=='+' || C[i]=='-') i++;
        if(C[i]=='x'){
            i++;
            if(C[i]=='^'){
                i++;
                auto [k,d]=get(i);
                A[(int)d]=sign;
                if(!D) D=d;
                i=k;
            }
            else A[1]=sign;
        }
        else{
            auto [j,x]=get(i);
            i=j;x*=sign;
            if(C[i]=='.') A[0]=x;
            else{
                assert(C[i]=='x');i++;
                if(C[i]=='^'){
                    i++;
                    auto [k,d]=get(i);
                    A[(int)d]=x;
                    if(!D) D=d;
                    i=k;
                }
                else A[1]=x;
            }
        }
    }
    bigint T=A[D];
    if(T<0){
        T=-T;
        cout << "-";
    }
    if(T>1) cout << T;
}

const int M=1000000;
vector<int> P={543892411,567498259,643448581,772660877,802279559,823153213,847485637,907170331,919507003,923425961,929812711,935151689,938910911,962946403,970870897,977946113,985116131,989743967,991308817,994793521,995403061,997310857,998623607,999049111,999860857,1000885111,1002002609,1002270383,1002326077,1002351107,1002642457,1002681557,1003013519,1004475841,1005879367,1006478441,1007120461,1007468677,1007576071,1008054149,1008640013,1008894637,1009316083,1009528721,1009862393,1010510329,1010915173,1011460739,1012072651,1012612079,1012668131,1012825181,1014091867,1014515053,1014904973,1015114333,1015944323,1016003431,1016121461,1017088367,1017307463,1017423811,1017620873,1018394743,1018932493,1019199101,1019208581,1019319187,1019376101,1019831203};
int S=(int)P.size();

void solve(){
    init();
    vector<array<int,3>> res;
    
    int k=0;
    while(A[k]==0) k++;
    if(k) res.push_back({0,1,k});
    for(int i=k;i<=D;i++) A[i-k]=A[i];
    D-=k;

    vector<vector<int>> B(S,vector<int>(D+1,0));
    for(int i=0;i<S;i++){
        for(int j=0;j<=D;j++){
            B[i][j]=((int)(A[j]%P[i])+P[i])%P[i];
        }
    }

    auto g = [&](int x,int y){
        for(int i=0;i<S;i++){
            int t=(x+P[i])*inv(y,P[i])%P[i],val=0;
            for(int j=D;j>=0;j--) val=(val*t+B[i][j])%P[i];
            if(val) return false;
        }
        for(int i=0;i<S;i++){
            int t=(x+P[i])*inv(y,P[i])%P[i];
            for(int j=D-1;j>=0;j--) B[i][j]=(B[i][j+1]*t+B[i][j])%P[i];
        }
        return true;
    };

    auto cal = [&](int x,int y){
        int k=0;
        while(g(x,y)) k++;
        if(k) res.push_back({x,y,k});
    };

    vector<int> X,Y;
    for(int i=1;i<=M;i++){
        if(A[0]%i==0) X.push_back(i);
        if(A[D]%i==0) Y.push_back(i);
    }
    for(int x:X) for(int y:Y){
        if(__gcd(x,y)!=1) continue;
        cal(x,y);
        cal(-x,y);
    }
    sort(res.begin(),res.end(),[&](array<int,3> a,array<int,3> b){
        return a[0]*b[1]>a[1]*b[0];
    });
    for(auto [x,y,k]:res){
        if(!x) cout << "x";
        else if(y==1){
            cout << "(x";
            if(x<0) cout << "+";
            cout << -x << ")";
        }
        else{
          cout << "(x";
            if(x<0) cout << "+";
            cout << -x << "/" << y << ")";  
        }
        if(k>1) cout << "^" << k;
    }
    cout << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
