#include <wiringPi.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

 
void leds ( void );
void audio ( void );

 
int main()
{
    pthread_t th1, th2;
 
 
    pthread_create ( &th1, NULL, ( void* ) leds, NULL );
    pthread_create ( &th2, NULL, ( void* ) audio, NULL );
    
  while(1); 
 
}
 
void leds ( void )
{
    
    
    
    while (1)
    {
        
          printf("LEDs \r\n");
        
        // wait a bit
        delay(500);
        audio();        
       printf("after \r\n");
    }
}
 
void audio( void )
{
    
   // while (1)
  //  {
        // Turn it on
          printf("Audio \r\n");
        
        // wait a bit
       delay(5000);
        
       return;
   // }
}
 



