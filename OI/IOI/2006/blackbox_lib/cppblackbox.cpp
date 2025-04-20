#include <stdio.h>
#include "cppbblib.h"

int main( void ) {
int  hi, si, ho, so,c ;
char * side[] = { "Top", "Right", "Bottom", "Left" } ;
  scanf("%d",&c);
  printf( "size=%d\n", Initialize( c ) ) ;
  scanf("%d",&c);
  do{  switch( c){
	   
           case 1 : ResetBox( ) ;  break ;
	   case 2 : ToggleDeflectors( ) ;  break ;
	   case 3 : scanf( "%d %d", &hi, &si ) ;
		    printf( "hits=%d ", throwBall( hi, si, ho, so ) ) ;
                    printf( "hole=%d side=%s %d\n", ho, side[so-1], so ) ;
                    break ;
	   case 4 : Finalize( ) ;
	   } 
        scanf( "%d", &c ) ; 
     } while( 1 ) ;
   }
			 
