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
	int ch;
	unsigned int msec;
	int bk;
	int stover, rstover;
	int col;
	int max,addx,addy;
     int space;
	int errorcode;
	int intro(void);

     intro();

	msec=0;
	bk=1;
	stover=0;
	space=3;

	driver = DETECT;
	mode = 0;
	initgraph(&driver, &mode, "");
	errorcode=graphresult();
	if( errorcode != grOk ){
		printf(" Graphics System Error: %s\n", grapherrormsg( errorcode ) );
		exit(1);
	}

	if(getmaxx()>getmaxy()) {
		max=getmaxy();
		addx=(getmaxx()-getmaxy())/2;
		addy=0;
	}
	else {
		max=getmaxx();
		addx=0;
          	addy=(getmaxy()-getmaxx())/2;
	}

	#define MAX max
	#define MAXCOLOR getmaxcolor()+1
	#define ADDX addx
     	#define ADDY addy

	randomize();
     col=random(MAXCOLOR);
	for(;;) {
		if(ch=='b' || ch=='c' || ch=='B' || ch=='C' || ch=='I' || ch=='i') {
			setbkcolor(random(bk));
		}
		loop:
		rstover=random(20+space);
		moveto(random(MAX), random(MAX));
		startx=getx();
		starty=gety();
		endx=startx;
		endy=starty;
		do {
			for(num=0; num<5; num++) {
				sign=random(2);
				if(sign==0) sign=-1;
				switch(num) {
					case 0:
						addsx=random(space)*sign;
						break;
					case 1:
						addsy=random(space)*sign;
						break;
					case 2:
						addex=random(space)*sign;
						break;
					case 3:
						addey=random(space)*sign;
						break;
					case 4:
						setcolor(col+sign*random(3));
						break;
				}
			}
			repeat=random(20);
			for(now=1; now<repeat; now++) {
				if(startx>=MAX || endx>=MAX || starty>=MAX || endy>=MAX || startx<=0 || starty <=0 || endx <=0 || endy<=0) {
					stover++;
					if(stover>=rstover) {
						cleardevice();
						stover=0;
						setbkcolor(random(bk));
                         	col=random(MAXCOLOR);
                         }
					goto loop;
				}
				line(startx+ADDX, starty+ADDY, endx+ADDX, endy+ADDY);
				line(MAX-startx+ADDX, MAX-starty+ADDY, MAX-endx+ADDX, MAX-endy+ADDY);
				line(starty+ADDX, startx+ADDY, endy+ADDX, endx+ADDY);
				line(MAX-starty+ADDX, MAX-startx+ADDY, MAX-endy+ADDX, MAX-endx+ADDY);
				line(startx+ADDX, MAX-starty+ADDY, endx+ADDX, MAX-endy+ADDY);
				line(MAX-startx+ADDX, starty+ADDY, MAX-endx+ADDX, endy+ADDY);
				line(starty+ADDX, MAX-startx+ADDY, endy+ADDX, MAX-endx+ADDY);
				line(MAX-starty+ADDX, startx+ADDY, MAX-endy+ADDX, endx+ADDY);
				delay(msec);
				startx+=addsx;
				starty+=addsy;
				endx+=addex;
				endy+=addey;
			}
		} while(!kbhit());
		ch=getch();
		switch(ch) {
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
				if(space<=10){
					space+=1;
				} else{
					sound(440);
					delay(100);
					nosound();
				}
				break;
			default:
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
					case 'c':
						cleardevice();
						stover=0;
						break;
					case 'b':
						if(bk==1) bk=MAXCOLOR;
						else bk=1;
						break;
					case 'p':
						getch();
						break;
					case 'h':
						restorecrtmode();
						intro();
						setgraphmode(getgraphmode());
						break;
					case 'd':
						bk=1;
						space=3;
						msec=0;
						setbkcolor(0);
						break;
					case 0x1b:
						restorecrtmode();
						return 0;
				}
				break;
		}
	}
}

int intro(void)
{
	char ch;

	clrscr();
	printf("                                WONDER\n\r");
	printf("                              Version 3.0\n\r");
	printf("                            Copyright 1993\n\r");
	printf("                             Avery Regier\n\r");
	printf("                           cAVEman Software\n\r\n\n");
	printf("               If you enjoy this program, let me know!!\n\r");
	printf("               Send your name, address, and comments to:\n\r");
	printf("                           3311 6th Avenue\n\r");
	printf("                        Sioux City, IA  51106\n\r");
	printf("                       Compuserve [71214,1301]\n\r\n");
	printf("               'B'         toggles background\n\r");
	printf("               'C'         clears the screen and starts over\n\r");
	printf("               'D'         set options to default\n\r");
	printf("               'H'         this screen\n\r");
	printf("               'P'         pauses the screen\n\r");
	printf("               '0'-'9'     sets the speed (0 is maximum speed)\n\r");
	printf("               right & left\n\r");
	printf("               arrow keys  set the space between lines\n\r");
	printf("               ESC key     quit\n\r");
	printf("\n\r                       Press any key to start.\n\r");
	ch=getch();
	if(ch==0x1b) exit(0);
	return 0;
}
