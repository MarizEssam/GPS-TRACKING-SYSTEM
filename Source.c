#include "Functions.h"

int main() {
	//Testing SegmentsDisplay , Expected to find (0x56 on Port B, 0x40 on Port A)
	int distance = 90;
	Init();
	
	

	//Test case #1: Testing 7 segments functions and LED_ON functions
	 while(!DestinationReached(distance)){
	 	distance++;
	 	SegmentsDisplay(distance);
	   LED_ON(distance);
	 	delay_1sec();
	 }

	//Test case #2: Testing 7 segments functions and Distance functions
	//distance=DistanceBetween2Points(30.064601,31.277308,30.064693,31.277582);
	//SegmentsDisplay(distance);
	while(1){}
}
