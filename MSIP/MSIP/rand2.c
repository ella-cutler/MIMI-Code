#include <stdio.h>
#include <curses.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <wiringPiI2C.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int array[10];
    int x, p;
  
    int i=0;

    srandom(time(NULL));

 
    while(i<10){
        int r=random()%10;

        for (x = 0; x < i; x++)
        {
            if(array[x]==r){
                break;
            }
        }
        if(x==i){
            array[i++]=r;
        }
    }
    for(p=0;p<10;p++){
        printf("%d ", array[p]);
    }
    return 0;
}
