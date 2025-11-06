



#include <stdio.h>
#include <curses.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <wiringPiI2C.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>



#define     Strobe_LE_R_E_pin 10 // SPI
#define     Strobe_CS_L_pin 25 //SPI

//#define     Audio_ENABLE_L_pin 23
//#define     MUTE_L_pin 15

//#define   MCLK_pin  =7 //I2S GPIO4
//#define   Digital_audio_CLK_u_pin  =1  // Digital_audio_CLK_u
//#define   L/R_audio_CLK_u_pin  // L/R_audio_CLK_u
//#define   Audio_Data_u_pin  =29   // Audio_Data_u

#define     OE_ALL_u_L_pin 26
#define     Mux0_pin 3
#define     Mux1_pin 4 
#define     Mux2_pin 5
#define     Mux3_pin 6
#define     Strobe_CS_L 25


// GPIO1_pin 31  Not connected
// GPIO0 pin 30 Not Connected
// GPIO22 pin 22 Not Connected
// GPIO6_pin 6  Not connected

//#define     GPIO5_pin 5 // To connector
//#define     GPIO15_pin 16  // To connector
//#define     GPIO16_pin 27  // To connector
//#define     GPIO17_pin 0  // To connector   This maybe used by AUDIO!
//#define     GPIO27_pin 2  // To connector
//#define     CS_Conn_pin 11  // To connector




#define     delay_min   1000  // min delay time in milliseconds
#define     delay_delta 4000  // Maximum delay time is delay_min + delay_delta in milliseconds
//#define BELL 1  //uses these to call audio and play
//#define BUZZER 2
//#define PAS 3



void annunciator (unsigned char ,  unsigned short int );
void run_demo_seq(void);
void lamp_test(void);
void run_launch_seq(void);

volatile unsigned char status_N = 0;
volatile unsigned char lamp_test_N = 0;
void initialize(void);
void All_OFF(void);
void All_ON(void);
void run_seq(void);  // only good for test
unsigned char random_N(void);
void bell_on(void);
void buzzer_on(void);
void pas_on(void);
//void volume_control_up(void);
//void volume_control_down(void);
void home(void);
void security (unsigned char);
void fault (unsigned char);
void not_authenticated (unsigned char);
void anti_jam_mode (unsigned char);
void missile_away (unsigned char);
volatile unsigned short int A_Left_copy;
volatile unsigned short int A_Right_copy;
volatile unsigned short int B_Left_copy;
volatile unsigned short int B_Right_copy;
volatile unsigned short int C_Left_copy;
volatile unsigned short int C_Right_copy;
volatile unsigned short int D_Left_copy;
volatile unsigned short int D_Right_copy;
volatile unsigned short int E_Left_copy;
volatile unsigned short int E_Right_copy;
int fd;    // file descriptor for I2C
//char volume;


void play(void){
	system("sudo mpg123 /home/pi/MSIP/bell_2s.mp3");
	return;
}

int main(int argc, char **argv)
{
	 wiringPiSetup();
	 printf ("call2");

//	pinMode(Mux0_pin, OUTPUT);	// Configure GPIOs
	
 
	pinMode(Mux3_pin, OUTPUT);
//	pinMode(Strobe_CS_L_pin, OUTPUT);
	pinMode(OE_ALL_u_L_pin, OUTPUT);
	digitalWrite(OE_ALL_u_L_pin, 1);  // put Output enable high so LEDs are off
	
	pinMode(Mux2_pin, OUTPUT);	
	  pinMode(Mux1_pin, OUTPUT);
	play();
	
	
		
	
	
	return 0;
}

