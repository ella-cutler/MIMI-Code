#include <wiringPi.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

 #define BELL 1  //uses these to call audio and play
#define BUZZER 2
#define PSA 3

void leds ( void );
void audio ( null );
FILE *fp;
 
int main()
{
    
 pthread_t th1;
 
  //  pthread_create ( &th2, NULL, ( void* ) leds, NULL );
 //pthread_create ( &th1, NULL, ( void* ) audio, NULL );
 
 
   pthread_create ( &th1, NULL, ( void* ) audio, NULL );  // creat a thread audio
 
    
  while (1)
    {
        
          printf("LEDs \r\n");
        
        // wait a bit
        delay(500);
        
  fp = fopen("./test", "r");  // open the file for "r"eading
 
 
       
    }
  fclose(fp); // clean up the pointer
   int pthread_detach(pthread_t th1); //clean up the thread
}
 
 
void audio( null)
{
    
    while (1)
    {
        // Audio on all the time pass pointer to file that will play
        //mute and unmute in other thread
          printf("Audio,%d \r\n",play_this);
        fprintf(fp, "%c",getc(fp));
        // wait a bit
       delay(5000);
         printf("finshed audio \r\n");
     
    }return;
}
 



