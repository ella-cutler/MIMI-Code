#include <wiringPi.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

 
void leds ( void );


void bell_on (void);
void bell_off (void);

 
int main()
{
    

 
  //  pthread_create ( &th2, NULL, ( void* ) leds, NULL );
 //pthread_create ( &th1, NULL, ( void* ) audio, NULL );
 
  
 

  
    
  while (1)
    {
        
          printf("LEDs \r\n");
        
        // wait a bit
        delay(500);
       
       
       //int pthread_detach(pthread_t th1);
       
    }
 
}
 
 
void bell_on( void )
{
  
   pthread_t th1;
    pthread_create ( &th1, NULL, ( void* ) play_bell, NULL );  
  FILE *fp;
  fp = fopen("./bell.mp3", "r");
    while (1)
    {
        // Turn it on
          printf("Bell on \r\n");
          //play bell over and over
        
        // wait a bit
       delay(5000);
         printf("finshed audio \r\n");
     
    }return;
}
 
void bell_off( void )
{
    fclose(fp);
    pthread_kill;
    
         printf("bell off \r\n");
     
    return;
}


