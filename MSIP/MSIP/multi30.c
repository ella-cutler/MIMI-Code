#include <wiringPi.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
char audio_on;
 
void leds ( void );
void audio ( void );

 
int main()
{
    
 pthread_t th1;
 audio_on =1;

 
  pthread_create ( &th1, NULL, ( void* ) audio, NULL );  
  //FILE *fp;
  //fp = fopen("./bell.mp3", "r");
 
  //fclose(fp);
  
    
  while (1)
    {
        
          printf("LEDs \r\n");
        
        // wait a bit
        delay(5000);
       
audio_on = 0;

       //int pthread_detach(pthread_t th1);
       
    }
 
}
 
 
void audio( void )
{
   
    while (audio_on)
    {
      
     
        // Turn it on
          printf("Audio on \r\n");
        
        // wait a bit
       delay(50);
         
     
    }return;
}
 



