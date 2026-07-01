# Bình luận kỳ thi ICPC Asia Pacific Championship 2026

Tác giả: Hoàng Xuân Bách

## Bình luận trước kỳ thi

Kỳ thi ICPC Asia Pacific Championship 2026 là kỳ thi nhằm tuyển chọn các đội xuất sắc nhất thuộc khu vực Châu Á - Thái Bình Dương để tham dự ICPC World Finals. Cuộc thi quy tụ những đội vượt qua các vòng ICPC Regional. 

Cuộc thi năm nay được tổ chức tại Đài Loan từ ngày 5/3 đến ngày 9/3/2026. Cuộc thi có khoảng 70 đội tham gia, trong đó Việt Nam có 19 đội từ 10 trường đại học. 

## Đánh giá về đề thi 

Đề thi năm nay gồm 13 bài. Dựa vào kết quả cuối cùng, bộ đề thi năm nay khá thành công với việc tất cả các bài đều có team AC và độ khó được dàn trải đều. 

- **Bài easy: H,J,K**
    - Bài H: Bài adhoc này khá dễ, cần nhận xét được là $|a_i-a_{i+1}|$ ko đổi

    - Bài J: Bài này một bài xử lý truy vấn khá dễ. 

    - Bài K: Đây là một bài chặt nhị phân cơ bản. 

- **Bài trung bình: C,E**
    - Bài C: Bài constructive khá hay. Nhận thấy do luôn lấy đỉnh có distance lớn nhất nên dãy s thực chất chính là một thứ tự dfs. 

    - Bài E: Bài cấu trúc dữ liệu với ý tưởng khá là trực tiếp. Đa số các team đều làm trong độ phức tạp $O(N\sqrt N)$, tuy nhiên bài có thể làm trong $O(NlogN)$
- **Bài hơi khó: B,F,D**
    - Bài B: Đây là một bài về game có thể gọi là vừa khó vừa dễ. Đa phần các team đều nghĩ được đến hướng chặt nhị phân đáp án nhưng để nghĩ ra được điều kiện kiểm tra thì đa phần các team đoán mò. 

    - Bài F: Ý tưởng bài này khá là trực tiếp là tính hết các $f(w)$ nhanh nhưng phần tính toán là việc khó bài này vì cần đến FFT. 

    - Bài D: Bài cấu trúc dữ liệu khá nặng về cài đặt. Bài yêu cầu phải cập nhật $dp$ của cây sử dụng Heavy-Light Decomposition nên nếu team nào lần đầu tiên cài đặt thuật này sẽ khá rối. 

- **Bài khó: I**
    - Bài I: Đây là một bài toán khó cần phải tối ưu công thức bằng DP. Đây là một bài khó hơn hẳn các bài trên. 
- **Bài rất khó: A,G,M**
    - Đây là 3 bài mà mỗi bài chỉ có một team AC. Các team làm được một trong các bài này gần như phải giành gần 2 tiếng để có thể AC. 
- **Bài kinh khủng: L**
    - Bài L: Bài này cũng chỉ có một team AC tuy nhiên lý do bài L được đặt ở mức độ kinh khủng do bài này đã ngăn cản được cả những người giỏi nhất thế giới trên  mirror contest. 

Đề thi lần này không có bài nào quá dễ mà các bài đều cần nhận xét và một khoảng thời gian nhất định để các đội có thể làm được. 


## Kết quả chung cuộc 

- **Đội Vô địch:** Strong Zero(NUS). Team đã trở thành nhà vô địch với 10 bài giải được, và hơn tận 200 penalty so với team về nhì. 

- **Huy Chương Vàng:** Fox is cute(KAIST), std_abs(NTU Taiwan)

- **Huy Chương Bạc:** Infinity(UET),HCMUS-ThaiFamily(HCMUS), NEU.Anarchaos(NEU)

- **Huy Chương Đồng:** BKDN.LoveBaku(BKDN),PTIT.Star(PTIT),VNUHCM.UIT.Jobseekers(VNUHCM.UIT)

Trong cuộc thi năm nay, Strong Zero tiếp tục thể hiện một sức mạnh gần như áp đảo khi team gần như giữ rank 1 trong gần hết thới gian của cuộc thi. 

Với các team đến từ Việt Nam, HCMUS-ThaiFamily cũng cho thấy một phong độ với việc luôn giữ vị trí trong top 10 bảng xếp hạng. Team Infinity thuộc UET tuy hơi troll trong phần lớn thời gian cuộc thi nhưng đã kịp AC 2 bài để vươn lên top 8, tuy nhiên là cuộc thi lấy 7 huy chương vàng. 

Dựa vào kết quả của kỳ thi, Việt Nam sẽ có 3 team góp mặt ở sân chơi ICPC World Final ở UAE là HCMUS-ThaiFamily, Infinity, và NEU.Anarchaos. 
