#include <stdio.h>
#include "cbblib.h"

int main( void ) {
	int  hi, si, ho, so ;
	char * side[] = { "Top", "Right", "Bottom", "Left" } ;
	int c=1 ;
	do {
		switch (c) {
		case 1 :printf( "box number? " ); 
						scanf( "%d", &c ) ;
						printf( "size=%d\n", Initialize( c ) ) ;
						break ;
		case 2 : ResetBox( ) ;  break ;
		case 3 : ToggleDeflectors( ) ;  break ;
		case 4 : scanf( "%d %d", &hi, &si ) ;
						 printf( "hits=%d ", throwBall( hi, si, &ho, &so ) ) ;
						 printf( "hole=%d side=%s %d\n", ho, side[so-1], so ) ;
						 break ;
		case 5 : Finalize( ) ;
	} 
	scanf( "%d", &c ) ; 
	} while( 1 ) ;
}

