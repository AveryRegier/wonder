#include <conio.h>
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <dos.h>

int kaleid(void);

unsigned int msec;
/*int col;*/
int space = 4;
int stover = 0;
int max = 31, addx = 1, addy = 1, maxx, maxy, out = 0;
int maxcolor;
	
int main(void)
{
	int driver, mode, errorcode;
	int n;
     char *ch;

     /* Initialize Graphics */
	driver = DETECT;
	mode = 0;
	initgraph(&driver, &mode, "");
	errorcode=graphresult();
	if( errorcode != grOk ){
		printf(" Graphics System Error: %s\n", grapherrormsg( errorcode ) );
		exit(1);
	}
	maxx = getmaxx();
     maxy = getmaxy();
	maxcolor = getmaxcolor();
	randomize();
/*	col=random(maxcolor);*/

     for(;;) if(!kaleid()) break;
	return 0;
}

int start_over(void)
{
	stover = 0;
/*	col = random(maxcolor);*/
	addx += 40;
	if(addx > maxx - max) {
		addx = 1;
		addy += 40;
		if(addy > maxy - max) {
		 /*	getch();       */
               cleardevice();
			addy = 1;
		}
	}
     setcolor(15);
	line(addx-1, addy-1, addx-1, addy + 33);
	line(addx-1, addy-1, addx + 33, addy-1);
	line(addx-1, addy + 33, addx + 33, addy + 33);
	line(addx + 33, addy-1, addx + 33, addy + 33);
	return 0;
}

int kaleid()
{
     int startx, starty, endx, endy;
	int addsx, addsy, addex, addey;
	unsigned int repeat, now, rstover;
	int sign, num;
	int ch;

	rstover=random(20);
	endx = startx = random( max );
	endy = starty = random( max );
	for(;;) {
		for(num=0; num<5; num++) {
			sign=random(2);
			if(sign==0) sign=-1;
			switch(num) {
				case 0:
					addsx = random( space ) * sign;
					break;
				case 1:
					addsy = random( space ) * sign;
					break;
				case 2:
					addex = random( space ) * sign;
					break;
				case 3:
					addey = random( space ) * sign;
					break;
				case 4:
					setcolor( random( maxcolor ) );
					break;
			}
		}
		repeat = random(10);
		for(now=1; now<repeat; now++) {
			/* WRITE LINES TO SCREEN */
			/* LARGEST POSSIBLE SQUARE MODE */
			line(startx+addx, starty+addy, endx+addx, endy+addy);
			line((max-startx)+addx, (max-starty)+addy, (max-endx)+addx, (max-endy)+addy);
			line(starty+addx, startx+addy, endy+addx, endx+addy);
			line((max-starty)+addx, (max-startx)+addy, (max-endy)+addx, (max-endx)+addy);
			line(startx+addx, (max-starty)+addy, endx+addx, (max-endy)+addy);
			line((max-startx)+addx, starty+addy, (max-endx)+addx, endy+addy);
			line(starty+addx, (max-startx)+addy, endy+addx, (max-endx)+addy);
			line((max-starty)+addx, (startx+addy), (max-endy)+addx, endx+addy);
			delay( msec );
			startx += addsx;
			starty += addsy;
			endx   += addex;
			endy   += addey;
          	/* CHECK BORDERS */
			if(startx > max || starty > max || endx > max || endy > max ||
			   startx < 0   || starty < 0   || endx < 0   || endy < 0) {
				if( ++stover >= rstover ) {
					start_over();
                         return 1;
				} else {
                    out = 1;
                    while(out){
				if( startx > max ){
					if(addsx > 0) addsx = (0 - addsx);
					startx += (2 * addsx);
				
				}
				if( startx < 0 ){
                         if(addsx < 0) addsx = (0 - addsx);
					startx += (2*addsx);

				}
				if( starty > max ){
					if(addsy > 0) addsy = (0 - addsy);
					starty += (2*addsy);
					
				}
                    if( starty < 0 ){
					if(addsy < 0) addsy = (0 - addsy);
					starty += (2*addsy);
					
				}
				if( endx > max ) {
					if(addex > 0) addex = (0 - addex);
					endx += (2*addex);
				
				}
				if( endx < 0 ){
					if(addex < 0) addex = (0 - addex);
					endx += (2*addex);
				}
				if( endy > max ){
					if(addey > 0) addey = (0 - addey);
					endy += (2*addey);
				}
				if( endy < 0 ){
					if(addey < 0) addey = (0 - addey);
					endy += (2*addey);
				}
				if(startx > max || starty > max || endx > max || endy > max || startx < 0   || starty < 0   || endx < 0   || endy < 0) {
					out = 1;
				}

				else out = 0;
				}         
				}
			}

		}
		if( kbhit() ) {
			ch = getch();
			ch=tolower(ch);
					 switch(ch) {
						case '0':
						case '1':
						case '2':
						case '3':
						case '4':
						case '5':
						case '6':
						case '7':
						case '8':
						case '9':
							msec=(ch-48)*5;
							break;
						case 'p':
							getch();
							break;
						case 0x1b:
							restorecrtmode();
							return 0;
					}
			}
		}
	
}