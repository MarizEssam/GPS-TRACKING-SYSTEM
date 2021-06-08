#include "tm4c123gh6pm.h"
#include <inttypes.h>
#include <stdio.h>
#include <math.h> 
#include <stdbool.h>

#define M_PI 3.142857
//UART 
void UART_INIT(void);
char UART6_Receive(void);
// Ports
void Init(void);

//for 7 segment display
uint8_t FirstTwoDigits(int distance);
uint8_t ThirdDigit(int distance);
void SegmentsDisplay(int distance);

//for turning on LED
void LED_ON(int distance);
bool DestinationReached(int distance);

//for distance calculating
float Deg2Rad(float Deg);
int DistanceBetween2Points(float Latitude1,float Longitude1,float Latitude2,float Longitude2);


//Delay function
void delay_1sec(void);
