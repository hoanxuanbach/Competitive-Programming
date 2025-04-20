uses  pbblib ;

var
   c, hi, si, ho, so : integer;
const
   side : array[1..4] of string = ( 'Top', 'Right', 'Bottom', 'Left' ) ;

begin
   c := 1 ;
   repeat
      case  c  of
           1 : begin
                  write( 'box number? ' ); 
                  readln( c ) ;
		  writeln( 'size=', Initialize( c ) ) ;
		  end ;
	   2 : ResetBox( ) ;  
	   3 : ToggleDeflectors( ) ; 
	   4 : begin
                  read( hi, si ) ;
		  write( 'hits=', throwBall( hi, si, ho, so ) ) ;
                  writeln( '  hole=', ho, '  side=', side[so], ' ', so ) ;
                  end ;
	   5 : Finalize ;
	   end ; 
        readln( c ) ; 
      until( false ) ;
   end.
			 
