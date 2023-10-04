void waste_detector();
void start();

#include<stdio.h>

int ir; // output from IR sensor : 1 is for close proximity
int metal_sen ; // output from the metal detecting sensor : 1 is for metal detected
int mois_sen ; // output from the moisture detecting sensor : 1 is for moisture detected
int mm,mw,md; // gpio's for motors operating the open-close of metal,wet and dry lids respectively
int LED_value;

void waste_detector(int mois_sen,int metal_sen,int mm,int mw,int md)
{

   if(!mois_sen && metal_sen){
   	mm=1;mw=0;md=0; }
   else if(!metal_sen && mois_sen){
   	mw=1;mm=0;md=0; 
   }
   else {
   	md=1;mw=0;mm=0;
   	}
}

void start(int ir)
{

    
    
	if(!ir) //If the bin is not full, we manage the waste segregation
	{
		printf("Bin is full\n");
		LED_value=0; //digital_write(LED_pin_number,0)
		int led_value_2 = LED_value * 16;
		asm(
		"or x30, x30,%0 \n\t"
		:"=r"(led_value_2));
		waste_detector(mois_sen,metal_sen,mm,mw,md);
		int mm_2= mm * 32;
		int mw_2 = mw * 64;
		int md_2 = md *128;
        	asm(
		"or x30, x30, %0\n\t"
		"or x30, x30, %1\n\t" 
		"or x30 , x30, %2\n\t"
		:"=r"(mm_2),"=r"(mw_2),"=r"(md_2));
		// digital_write(mm_pin_num,mm);
		// digital_write(mw_pin_num,mw);
		// digital_write(md_pin_num,md);				
		

	}
	else // we turn on the LED and donot open the lids
	{
		LED_value=1; //digital_write(LED_pin_number,1)
		int led_value_3 = LED_value * 16;
		asm(
		"or x30, x30, %0 \n\t"
		:"=r"(led_value_3));
	}
	
	
	
}
int main(){
    
    ir=0; //ir=digital_read(ir_pin_number) 
    asm(
    "andi %0 , x30, 0\n\t"
    :"=r"(ir));
    mois_sen=0; //mois_sen=digital_read(mois_sen_pin_number)
    asm(
    "andi %0 , x30, 0\n\t"
    :"=r"(mois_sen));
    metal_sen =1; //metal_sen=digital_read(metal_sen_pin_number)
    asm(
    "andi %0 , x30, 4\n\t"
    :"=r"(metal_sen));
    while(1){
        start(ir);
    }
    return(0);
}


