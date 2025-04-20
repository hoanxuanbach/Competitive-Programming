{read deflectors as a list}
{$INLINE ON}
UNIT  PBBLIB ;

INTERFACE

   Procedure  ResetBox ;
   Function  Initialize( which : Integer ) : Integer ;
   Procedure  ToggleDeflectors ;
   Function  throwBall( hi, si : integer ; var ho, so : integer ): LongInt ;
   Function  HowManyThrows : QWord ;  { not documented function }
   Procedure  Finalize ;
   var  Sounds : boolean ;

   {Procedure BoxExplain ;
   Procedure ShowBox ;}

IMPLEMENTATION

{uses dos, sockets        , crt ;}

type
   COORD = integer ;
   SIDE = ( Basura, Top, Right, Bottom, Left ) ;


const
   X = false ;
   Y = true ;
   MAXSIZE = 30 ;

   RECEIVE_KILL			= '1, More than one app'
   INVALID_BOX_NUMBER		= '2, Invalid box'
   INVALID_DEFLECTOR_POSITION	= '3, Invalid deflector'
   INVALID_DEFLECTOR_SYMBOL	= '4, Invalid symbol'
   INVALID_BOX_SIZE		= '5, Invalid size'
   INVALID_INPUT_HOLE		= '6, Invalid input hole'
   ALARM			= '7, ALARM'



var
   box, boxi : array[0..MAXSIZE+1,0..MAXSIZE+1] of Char ;  { only values: .,/,\,? }
   Sb, S1 : COORD ;
   Count : QWord ;
   Local : boolean ;
   pin, pout : file of char ;

Procedure  ERROR( s : string ) {  writeln( stderr, s ) ;  halt( 1 ) ;  }

Function   ReceiveChar: Char ;
var  c : char ;
begin
   read( pin, c ) ;
   if  c = '\'  then  ERROR( RECEIVE_KILL ) ;
   ReceiveChar := c ;
   {writeln( 'pbblib0: ReceiveChar: ', c ) ;}
   end ;

Procedure  SendChar( c : char ) ;
begin
   {writeln( 'pbblib0: SendChar: ', c ) ;}
   write( pout, c ) ;
   end ;

Procedure  Finalize ;
begin
   if  not  Local  then  begin
      write( pout, 'F' ) ;
      close( pout ) ;
      close( pin ) ;
      end ;
   halt ;
   end ;

Function  HowManyThrows  : QWord ;
begin  HowManyThrows := Count end ;

Procedure  ResetBox ;
begin
   if  Local  then  Box := Boxi
   else  begin
      write( pout, 'R' ) ;
      {write( pout, sign ) ;}
      end
   end ;

Function  Initialize( which : Integer ) : Integer ;

var
   ar : Text ;
   i, j : COORD ;
   {error, v :  LongWord ;}
   k : integer ;
   c, c1 : char ;

  Function Swapword( w: word ): word ;
  begin  swapword := w shl 8 or w shr 8  end ;

begin
   FillChar( boxi, sizeof(boxi), '.' ) ;

   if  ( which < 0 )  or  ( which > 15 )  then  ERROR( INVALID_BOX_NUMBER ) ;

   Local := which = 0 ;

   if  Local  then  begin
      assign( ar, 'blackbox.in' ) ;
      reset( ar ) ;

      readln( ar, Sb ) ;
      if  ( Sb < 1 ) or ( Sb > MAXSIZE )  then  ERROR( INVALID_BOX_SIZE ) ;

      Initialize := Sb ;
      S1 := Sb + 1 ;
      for  i := 1 to Sb do
         for  j := 1 to Sb  do
            boxi[i,j] := '.' ;

      readln( ar, k ) ;
      for  k := k  downto 1  do begin
         readln( ar, j, i, c1, c ) ;
         boxi[i,j] := c ;
         if  ( i < 1 ) or ( i > Sb ) or ( j < 1 ) or ( j > Sb )  
         then   ERROR( INVALID_DEFLECTOR_POSITION ) ;
         if  ( c <> '/' )  and  ( c <> '\'  )   
         then  ERROR( INVALID_DEFLECTOR_SYMBOL ) ;
         end ;

      close( ar ) ;
      ResetBox ;
      Count := 0 ;
      end
   else  { socket initializing }  begin
      assign( pin, '/var/tmp/from_box' ) ;
      reset( pin ) ;
      assign( pout, '/var/tmp/to_box' ) ;
      rewrite( pout ) ; 
      write( pout, '{' ) ;
      c := ReceiveChar ;
      if  c <> '}'  then  ERROR( ALARM ) ;

      SendChar( char( which + 32 ) ) ;
      c := ReceiveChar ;
      Sb := ord( c ) - 32 ;
      end ;

   Initialize := Sb ;
   S1 := Sb + 1 ;
   end ;



Procedure  ToggleDeflectors ;
var
   i, j : COORD ;
begin
   if  Local  then
      for  i := 1 to Sb do
         for  j := 1 to Sb  do
                  if  Box[i,j] = '/'  then  Box[i,j] := '\'
            else  if  Box[i,j] = '\'  then  Box[i,j] := '/' else
   else  begin
      write( pout, 'I' ) ;
      end 
   end ;

Function  throwBall( hi, si : integer ; var ho, so : integer ): LongInt ;

const  av : array[boolean,SIDE] of Integer = ( ( 27, 0, -1, 0, 1 ),
                                               ( 84, -1, 0, 1, 0 ) ) ;
var
   hits, i : LongInt ;
   p : array[boolean] of COORD ;
   b : boolean ;
   c, c1 : Char ;

begin

   if  ( si < 1 )  or  ( si > 4 )  or  ( hi < 1 )  or  ( hi > Sb )
   then  ERROR( INVALID_INPUT_HOLE ) ;

   if  Local  then  begin
      Inc( Count ) ;
      hits := 0 ;
      case SIDE(si)  of
        Top    : begin p[X] := hi      ; p[Y] := S1 ; end ;
        Right  : begin p[Y] := S1 - hi ; p[X] := S1 ; end ;
        Bottom : begin p[X] := hi      ; p[Y] := 0  ; end ;
        Left   : begin p[Y] := S1 - hi ; p[X] := 0  ; end ;
        end ;

      repeat
        for  b := X to Y  do  Inc( p[b], av[b,SIDE(si)] ) ;
        if  Box[S1-p[Y],p[X]] <> '.'  then  begin
            Inc( hits ) ;
            si := (si-1) xor 1 xor 2*ord( Box[S1-p[Y],p[X]] = '\' ) + 1 ;

   {   coming from    Top     Right   Bottom  Left         1  2  3  4
           /           Right   Top     Left    Bottom      2  1  4  3
           \           Left    Bottom  Right   Top         4  3  2  1    }
           Box[S1-p[Y],p[X]] := Char( ord('/') xor ord('\') xor ord(Box[S1-p[Y],p[X]]) ) ;
           end ;
        until  ( p[X] = 0 ) or ( p[X] = S1 ) or ( p[Y] = 0 ) or ( p[Y] = S1 ) ;
      case SIDE(si)  of
        Top, Bottom : ho := p[X] ;
        Right, Left : ho := S1-p[Y] ;
        end ;
      so := (si-1) xor 2 + 1 ;
      end
   else  begin
      write( pout, 'T' ) ;
      write( pout, chr( si+64 ) ) ;
      write( pout, chr( hi+32 ) ) ;
      read( pin, c ) ;
      read( pin, c1 ) ;
      so := ord( c ) - 64 ;
      ho := ord( c1 ) - 32 ;
      hits := 0 ;
      for  i := 0 to 3 do begin
         c := ReceiveChar ;
         hits := LongWord(ord(c)-32) shl (6*i) or hits ;
         end ;
      end ;
   Inc( Count ) ;
   throwBall := hits ;
   end ;


INITIALIZATION
   Count := 0 ;

end.


