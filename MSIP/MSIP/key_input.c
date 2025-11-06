
#include <stdio.h>
#include <curses.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <wiringPiI2C.h>
#include <stdlib.h>
#include <time.h>




int main()
{
   printf("start\r\n");
   
   printf("start\r\n");
   printf("start\r\n");
   printf("start\r\n");
   printf("start\r\n");
  int input;
  

  
initscr();  // setup curses
 // setlocale(LC_ALL,"");
 

   keypad(stdscr, TRUE);	
//initscr();
 nonl();
intrflush(stdscr,FALSE);
 	
	
fflush(stdout);
	
	
 noecho();
  
  printf("here\r\n");	
	while(1){

 printf("WAIT FOR KEY\r\n");
  input = getch(); //   Get
  printf("Key was  %d\r\n",input);
}
	return 0;

}

