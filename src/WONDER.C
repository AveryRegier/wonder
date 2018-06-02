#include <conio.h>
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <dos.h>


main(void)
{
	int driver, mode;
	int startx, starty, endx, endy;
	int repeat, now;
	int addsx, addsy, addex, addey;
	int sign, num;
	int colors, hcolr;
	int ch;
	unsigned int msec;
	int bk;
	int stover, rstover;
	int col;

	int intro(void);
     intro();

	msec=0;
	bk=1;
	stover=0;

	#define MAXX getmaxy()
	#define MAXY getmaxy()

	driver = DETECT;
	mode = 0;
	initgraph(&driver, &mode, "");

     #define MAXCOLOR getmaxcolor()+1
	randomize();
	for(;;) {
		if(ch=='b' || ch=='c' || ch=='B' || ch=='C') {
			setbkcolor(random(bk));
		}
		loop:
		rstover=random(20);
		moveto(random(MAXX), random(MAXY));
		startx=getx();
		starty=gety();
		endx=startx+random(5);
		endy=starty+random(5);
          col=random(MAXCOLOR);
		do {
			for(num=0; num<5; num++) {
				sign=random(2);
				if(sign==0) {
                    	sign=-1;
				}
				switch(num) {
					case 0:
						addsx=random(3)*sign;
						break;
					case 1:
						addsy=random(3)*sign;
						break;
					case 2:
						addex=random(3)*sign;
						break;
					case 3:
						addey=random(3)*sign;
						break;
					case 4:
						setcolor(col+sign*random(3));
						break;
				}
			}
			repeat=random(20);
			for(now=1; now<repeat; now++) {
				if(startx>=MAXX || endx>=MAXX || starty>=MAXY || endy>=MAXY || startx<=0 || starty <=0 || endx <=0 || endy<=0) {
					stover++;
					if(stover>=rstover) {
						cleardevice();
						stover=0;
						setbkcolor(random(bk));
                         }
					goto loop;
				}
				line(startx, starty, endx, endy);
		 		line(MAXX-startx, MAXY-starty, MAXX-endx, MAXY -endy);
				line(starty, startx, endy, endx);
				line(MAXX-starty, MAXY-startx, MAXX-endy, MAXY-endx);
				line(startx, MAXY-starty, endx, MAXY-endy);
				line(MAXX-startx, starty, MAXX-endx, endy);
				line(starty, MAXY-startx, endy, MAXY-endx);
				line(MAXX-starty, startx, MAXX-endy, endx);
				delay(msec);
				startx+=addsx;
				starty+=addsy;
				endx+=addex;
				endy+=addey;
			}
		} while(!kbhit());
		ch=getch();
		tolower(ch);
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
				if(msec<=50){
					msec+=5;
				} else{
					sound(440);
					delay(100);
					nosound();
				}
				break;
               case 'C':
			case 'c':
				cleardevice();
				stover=0;
				break;
               case 'B':
			case 'b':
				if(bk==1) {
					bk=16;
				} else bk=1;
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

int intro(void)
{
	clrscr();
	printf("                                WONDER\n\r");
	printf("                              Version 1.0\n\r");
	printf("                            Copyright 1993\n\r");
	printf("                             Avery Regier\n\r");
	printf("                           cAVEman Software\n\r\n\n");
	printf("               If you enjoy this program, let me know!!\n\r");
	printf("               Send your name, address, and comments to:\n\r");
	printf("                           3311 6th Avenue\n\r");
	printf("                        Sioux City, IA  51106\n\r");
	printf("                       Compuserve [71214,1301]\n\r\n\n\n");
	printf("		     'B'         toggles background\n\r");
	printf("		     'C'         clears the screen and starts over\n\r");
	printf("		     'P'         pauses the screen\n\r");
	printf("		     '0'-'9'     sets the speed\n\r             (0 is full speed, 9 is the slowest speed)\n\r");
	printf("                     ESC key     quit\n\r");
	printf("\n\r                       Press any key to start.\n\r");
	getch();
	return 0;
}