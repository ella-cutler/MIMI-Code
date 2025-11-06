#include <bcm2835.h>
#include <pthread.h>
#include <unistd.h>
 
#define PIN1 RPI_GPIO_P1_11
#define PIN2 RPI_GPIO_P1_12
#define PIN3 RPI_GPIO_P1_24
#define PIN4 RPI_GPIO_P1_15
#define PIN5 RPI_GPIO_P1_16
#define PIN6 RPI_GPIO_P1_18
#define PIN7 RPI_GPIO_P1_22
#define PIN8 RPI_GPIO_P1_07
 
void blink1 ( void );
void blink2 ( void );
void blink3 ( void );
void blink4 ( void );
void blink5 ( void );
void blink6 ( void );
void blink7 ( void );
void blink8 ( void );
 
int main()
{
    pthread_t th1, th2, th3, th4, th5, th6, th7, th8;
 
    if (!bcm2835_init())
        return 1;
 
    pthread_create ( &th1, NULL, ( void* ) blink1, NULL );
    pthread_create ( &th2, NULL, ( void* ) blink2, NULL );
    pthread_create ( &th3, NULL, ( void* ) blink3, NULL );
    pthread_create ( &th4, NULL, ( void* ) blink4, NULL );
    pthread_create ( &th5, NULL, ( void* ) blink5, NULL );
    pthread_create ( &th6, NULL, ( void* ) blink6, NULL );
    pthread_create ( &th7, NULL, ( void* ) blink7, NULL );
    pthread_create ( &th8, NULL, ( void* ) blink8, NULL );
 
    while ( 1 );  
  
    bcm2835_close();
 
    return 0;
}
 
void blink1 ( void )
{
    // Set the pin to be an output
    bcm2835_gpio_fsel(PIN1, BCM2835_GPIO_FSEL_OUTP);
    // Blink
    while (1)
    {
        // Turn it on
        bcm2835_gpio_write(PIN1, HIGH);
        
        // wait a bit
        bcm2835_delay(500);
        
        // turn it off
        bcm2835_gpio_write(PIN1, LOW);
        
        // wait a bit
        bcm2835_delay(500);
    }
}
 
void blink2 ( void )
{
    // Set the pin to be an output
    bcm2835_gpio_fsel(PIN2, BCM2835_GPIO_FSEL_OUTP);
    // Blink
    while (1)
    {
        // Turn it on
        bcm2835_gpio_write(PIN2, HIGH);
        
        // wait a bit
        bcm2835_delay(1000);
        
        // turn it off
        bcm2835_gpio_write(PIN2, LOW);
        
        // wait a bit
        bcm2835_delay(1000);
    }
}
 
void blink3 ( void )
{
    // Set the pin to be an output
    bcm2835_gpio_fsel(PIN3, BCM2835_GPIO_FSEL_OUTP);
    // Blink
    while (1)
    {
        // Turn it on
        bcm2835_gpio_write(PIN3, HIGH);
        
        // wait a bit
        bcm2835_delay(1500);
        
        // turn it off
        bcm2835_gpio_write(PIN3, LOW);
        
        // wait a bit
        bcm2835_delay(1500);
    }
}
 
void blink4 ( void )
{
    // Set the pin to be an output
    bcm2835_gpio_fsel(PIN4, BCM2835_GPIO_FSEL_OUTP);
    // Blink
    while (1)
    {
        // Turn it on
        bcm2835_gpio_write(PIN4, HIGH);
        
        // wait a bit
        bcm2835_delay(2000);
        
        // turn it off
        bcm2835_gpio_write(PIN4, LOW);
        
        // wait a bit
        bcm2835_delay(2000);
    }
}
 
void blink5 ( void )
{
    // Set the pin to be an output
    bcm2835_gpio_fsel(PIN5, BCM2835_GPIO_FSEL_OUTP);
    // Blink
    while (1)
    {
        // Turn it on
        bcm2835_gpio_write(PIN5, HIGH);
        
        // wait a bit
        bcm2835_delay(2500);
        
        // turn it off
        bcm2835_gpio_write(PIN5, LOW);
        
        // wait a bit
        bcm2835_delay(2500);
    }
}
 
void blink6 ( void )
{
    // Set the pin to be an output
    bcm2835_gpio_fsel(PIN6, BCM2835_GPIO_FSEL_OUTP);
    // Blink
    while (1)
    {
        // Turn it on
        bcm2835_gpio_write(PIN6, HIGH);
        
        // wait a bit
        bcm2835_delay(3000);
        
        // turn it off
        bcm2835_gpio_write(PIN6, LOW);
        
        // wait a bit
        bcm2835_delay(3000);
    }
}
 
void blink7 ( void )
{
    // Set the pin to be an output
    bcm2835_gpio_fsel(PIN7, BCM2835_GPIO_FSEL_OUTP);
    // Blink
    while (1)
    {
        // Turn it on
        bcm2835_gpio_write(PIN7, HIGH);
        
        // wait a bit
        bcm2835_delay(3500);
        
        // turn it off
        bcm2835_gpio_write(PIN7, LOW);
        
        // wait a bit
        bcm2835_delay(3500);
    }
}
 
void blink8 ( void )
{
    // Set the pin to be an output
    bcm2835_gpio_fsel(PIN8, BCM2835_GPIO_FSEL_OUTP);
    // Blink
    while (1)
    {
        // Turn it on
        bcm2835_gpio_write(PIN8, HIGH);
        
        // wait a bit
        bcm2835_delay(4000);
        
        // turn it off
        bcm2835_gpio_write(PIN8, LOW);
        
        // wait a bit
        bcm2835_delay(4000);
    }
}