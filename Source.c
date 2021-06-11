#include "Functions.h"

#define TURNING_INDIC 7  //To be changed by Mario after practical trial

//Global Variables
float lon[TURNING_INDIC];
float lat[TURNING_INDIC];
float COG[TURNING_INDIC]; 
float total_distance =0;
float startingPoint[3];
float currentCog =0;
float cogRunningSum =0;
float cogRunningNum =0;
int initialCounter = TURNING_INDIC;

int main() {
	//Initialization
	Init();			//TO BE MODIFIED BY MARK
	UART_INIT();
	LCD_INIT();

	//Print Hello

    
    LCD_CMD(0X30);  //wake up
    msdelay(50);
    LCD_CMD(0X38);  //8-bit bus mode, 2 line display mode, 5x8 dots display mode
    msdelay(50);
    LCD_CMD(0X01);  //clear display
    msdelay(50);
    LCD_CMD(0X0F);  //turn on display
    msdelay(50);
    LCD_CMD(0X80);  //first row
    LCD_display("Hello User..");
    msdelay(700);
    LCD_CMD(0X01);				//Youssef <- Delete this
    msdelay(250);
    

    
    
}


	//Gps call
	GPSread();
	while(!fix){}
	GPIO_PORTF_DATA_R |= 0x02;

	while(GPIO_PORTF_DATA_R & 0x01){}	//To be checked by MARK whether it's negative logic or
	GPIO_PORTF_DATA_R &= ~(0x02);
	GPIO_PORTF_DATA_R |= 0x08;

	//Loop
	//Youssef <- Add First Distance Display here
        LCD_display("Distance=");
        msdelay(200);
		 PRINT_DISTANCE(distance);
		
		while(initialCounter--){
			//scanf("%f", &COG[TURNING_INDIC-initialCounter-1]); //cin longs and lats
			GPSread();
			lon[TURNING_INDIC-initialCounter-1] = longtitude();
			lat[TURNING_INDIC-initialCounter-1] = latitude();
			COG[TURNING_INDIC-initialCounter-1] = CourseLand();
			
			// cogRunningSum += COG[TURNING_INDIC-initialCounter-1]; //Remove
			// cogRunningNum++;
			if(initialCounter +1 ==TURNING_INDIC){
				startingPoint[0] = lat[0];
				startingPoint[1] = lon[0];
				startingPoint[2] = COG[0];
				
			}
 	   }
		currentCog = Average(COG);

		while(!DestinationReached){
			GPSread();
			 if(Outlier(currentCog, CourseLand() ) )
            	continue;

	        ShiftInsert(lon, longtitude() );
	        ShiftInsert(lat, latitude() );
	        ShiftInsert(COG, CourseLand() );

	        if(Turned(COG,currentCog)&&DegCheck(COG)){
				total_distance += DistanceBetween2Points(startingPoint[0], startingPoint[1],lat[0],lon[0]);	//Store point previous to it?
				startingPoint[0] = lat[0];
				startingPoint[1] = lon[0];
				startingPoint[2] = COG[0];
				//Youssef<- LCD Displays "TURNED" for a brief delay
				//Youssef <- Second Distance Display here
				 PRINT_DISTANCE(distance);
                LCD_CMD(0XC0);  //force cursor to 2nd row
				 msdelay(30);
				LCD_display("TURNED");
				msdelay(30);
				LCD_CMD(0XC0);   
				msdelay(30);
				LCD_display("      ");  //unsure if this will clear second row as there is no direct function to do so except clear the whole display
				                        

			}
		}
		total_distance += DistanceBetween2Points(startingPoint[0], startingPoint[1],lat[TURNING_INDIC-1],lon[TURNING_INDIC-1]]);
		//Youssef <- Third Distance Display here
		PRINT_DISTANCE(distance);


	//Test case #1: Testing 7 segments functions and LED_ON functions
	//  while(!DestinationReached(distance)){
	//  	distance++;
	//  	SegmentsDisplay(distance);
	//    LED_ON(distance);
	//  	delay_1sec();
	//  }

	//Test case #2: Testing 7 segments functions and Distance functions
	//distance=DistanceBetween2Points(30.064601,31.277308,30.064693,31.277582);
	//SegmentsDisplay(distance);
	while(1){}
}
