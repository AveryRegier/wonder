#include <conio.h>
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <dos.h>
#include <ctype.h>

int kaleid(void);
int intro(void);
int write_default(void);
int get_default(void);

unsigned int msec;
int bk, col, randomColors;
int space;
int full;
int stover = 0;
int max, addx, addy;
float xratio, yratio;
int maxcolor;

int main(void)
{
	int driver, mode, errorcode;
	int n;
     char *ch;
     float maxx, maxy;

     /* Set all default parameters */
     if(get_default()){
		msec = 0;
		bk = 1;
		space = 4;
		full = 0;
		randomColors = 0;
	}

     if( intro() ) return 0;

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

	if(maxx>maxy) {
		max=maxy;
		addx=(maxx-maxy)/2;
		addy=0;
		xratio = (maxx+1) / (maxy+1);
		yratio = 1;
	}
	else {
		max=maxx;
		addx=0;
		addy=(maxy-maxx)/2;
		xratio = 1;
		yratio = (maxy+1) / (maxx+1);
	}

	randomize();
	col=random(maxcolor);
     setbkcolor(random(bk));

	while( kaleid() );       /* If kaleid() returns a value of 0,
						   then break from the loop and end program. */
	return 0;
}

int intro(void)
{
	char ch;

	clrscr();
	printf("                                WONDER\n\r");
	printf("                              Version 6.0\n\r");
	printf("                            Copyright 1993\n\r");
	printf("                             Avery Regier\n\r");
	printf("                           cAVEman Software\n\r\n");
	printf("               If you enjoy this program, let me know!!\n\r");
	printf("              E-mail your name, address, and comments to:\n\r");
	printf("                       regier@wehner.cs.uni.edu\n\r");
	printf("\n\r\n");
	printf("               'B'          toggle background\n\r");
	printf("               'C'          clear the screen and starts over\n\r");
	printf("               'D'          set default parameters\n\r");
	printf("               'F'          toggle full screen mode\n\r");
	printf("               'H'          this screen\n\r");
	printf("               'P'          pause the screen\n\r");
	printf("               'R'          toggle color schemes & random color selection\n\r");
	printf("               '0'-'9'      set the delay ('0' is the fastest)\n\r");
	printf("               arrow keys:  \n\r");
	printf("               up & down    decrement and increment the delay\n\r");
	printf("               right & left set the space between lines\n\r");
	printf("               ESC key      quit\n\r");
	printf("\n\r                         Press any key to start.");
	ch=getch();
	if(ch==0x1b) return 1;
	return 0;
}

int write_default(void)
{
	FILE *fp;

	if((fp = fopen("wonder.def", "wt"))==NULL){
		printf("write_default unsuccessful");
		return 1;
	}

	fprintf(fp, "%d\n", full);
	fprintf(fp, "%d\n", space);
	fprintf(fp, "%d\n", bk);
	fprintf(fp, "%d\n", msec/5);
     fprintf(fp, "%d\n", randomColors);
	fclose(fp);
	return 0;
}

int get_default(void)
{
	FILE *fp;
	char *ch;

	if((fp = fopen("wonder.def", "rt"))==NULL){
		return 1;
	}
     fseek(fp, 0, 0);
	fgets(ch, 3, fp);
	full = atoi(ch);
	fgets(ch, 4, fp);
	space = atoi(ch);
	fgets(ch, 4, fp);
	bk = atoi(ch);
	if(bk > 1) bk = 16;
     else bk = 1;
	fgets(ch, 4, fp);
	msec = atoi(ch)*5;
	fgets(ch, 3, fp);
     randomColors = atoi(ch);

	fclose(fp);
	return 0;
}

int start_over(void)
{
	cleardevice();
	stover = 0;
	setbkcolor(random(bk));
	col = random(maxcolor);
	return 0;
}

int kaleid()
{
	int startx = 0, starty = 0, endx = 0, endy = 0;
	int addsx = 0, addsy = 0, addex = 0, addey = 0;
	unsigned int repeat = 0, now = 0, rstover = 0;
	int sign = 0, num = 0;
	int ch;

	rstover=random( 30 + space );
	moveto( random( max ), random( max ) );
	endx = startx = getx();
	endy = starty = gety();
	for(;;) {
		for( num=0; num<5; num++ ) {
			sign = random( 2 );
			if( sign == 0 ) sign =- 1;
			switch( num ) {
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
					if( randomColors ) setcolor (random ( maxcolor ) );
			 else setcolor( col + sign * random( 3 ) );
					break;
			}
		}
		repeat = random( 20 );
		for(now=1; now<repeat; now++) {

			/* WRITE LINES TO SCREEN */
			if(full){
		/* FULL SCREEN MODE */
				line(xratio*startx, yratio*starty, xratio*endx, yratio*endy);
				line(xratio*(max-startx), yratio*(max-starty), xratio*(max-endx), yratio*(max-endy));
				line(xratio*starty, yratio*startx, xratio*endy, yratio*endx);
				line(xratio*(max-starty), yratio*(max-startx), xratio*(max-endy), yratio*(max-endx));
				line(xratio*startx, yratio*(max-starty), xratio*endx, yratio*(max-endy));
				line(xratio*(max-startx), yratio*starty, xratio*(max-endx), yratio*endy);
				line(xratio*starty, yratio*(max-startx), xratio*endy, yratio*(max-endx));
				line(xratio*(max-starty), yratio*startx, xratio*(max-endy), yratio*endx);
			}else{
		/* LARGEST POSSIBLE SQUARE MODE */
				line(startx+addx, starty+addy, endx+addx, endy+addy);
				line((max-startx)+addx, (max-starty)+addy, (max-endx)+addx, (max-endy)+addy);
				line(starty+addx, startx+addy, endy+addx, endx+addy);
				line((max-starty)+addx, (max-startx)+addy, (max-endy)+addx, (max-endx)+addy);
				line(startx+addx, (max-starty)+addy, endx+addx, (max-endy)+addy);
				line((max-startx)+addx, starty+addy, (max-endx)+addx, endy+addy);
				line(starty+addx, (max-startx)+addy, endy+addx, (max-endx)+addy);
				line((max-starty)+addx, (startx+addy), (max-endy)+addx, endx+addy);
			}
			delay( msec );
			startx += addsx;
			starty += addsy;
			endx   += addex;
			endy   += addey;
		/* CHECK BORDERS */
			if( startx > max || starty > max || startx < 0 || starty < 0
			  || endx > max || endy > max || endx < 0 || endy < 0 ) {
				if( ++stover >= rstover ) {
					start_over();
			 return 1;
				} else {
				if( startx > max || startx < 0 ){
					addsx = 0 - addsx;
					startx += (2 * addsx);
				}
				if( starty > max || starty < 0 ){
					addsy = 0 - addsy;
					starty += (2 * addsy );
				}
				if( endx > max || endx < 0 ){
					addex = 0 - addex;
					endx += ( 2 * addex );
				}
				if( endy > max || endy < 0 ){
					addey = 0 - addey;
					endy += ( 2 * addey );
				}
				}
	       }
		}
		if( kbhit() ) {
			ch = getch();
			if( ch == NULL ) {
				ch = getch();
				switch(ch) {
					case 72:
						if(msec>0){
							msec-=5;
						} else{
							sound(440);
							delay(100);
							nosound();
						}
						break;
					case 80:
						if(msec<50){
							msec+=5;
						} else{
							sound(440);
							delay(100);
							nosound();
						}
						break;
					case 75:
						if(space>2){
							space-=1;
						} else{
							sound(440);
							delay(100);
							nosound();
						}
						break;
					case 77:
						if(space<9){
							space+=1;
						} else{
							sound(440);
							delay(100);
							nosound();
						}
						break;
		    }
			}else{
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
						case 'b':
							if( bk==1 ) bk=16;
							else bk=1;
							setbkcolor( random( bk ) );
							break;
						case 'p':
							getch();
							break;
						case 'r':
							if( randomColors ) randomColors = 0;
							else randomColors = 1;
				   break;
						case 'h':
							restorecrtmode();
							if( intro() ) return 0;
							setgraphmode( getgraphmode() );
							start_over();
				   return 1;
						case 'd':
							write_default();
							break;
						case 'f':
							if( full ) full = 0;
							else full = 1;
						case 'c':
							start_over();
				   return 1;
						case 0x1b:
							restorecrtmode();
							return 0;
					}
			}
		}
	}
}
