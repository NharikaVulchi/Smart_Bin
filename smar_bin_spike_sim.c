#include <stdio.h>
int main()
{
    
   
	int ir; // output from IR sensor : 1 is for close proximity, 0
	int metal_sen ; // output from the metal detecting sensor : 1 is for metal detected, 2
	int mois_sen ; // output from the moisture detecting sensor : 1 is for moisture detected, 1
	int mm=0;
	int mw=0;
	int md=0; // gpio's for motors operating the open-close of metal,wet and dry lids respectively
	int LED_value=0;
 	int led_value_2 = LED_value * 8;  //3 --> shifting 3 bits to the left
	int mm_2= mm * 16; //4 --> shifting 4 bits to the left
	int mw_2 = mw * 32; //5  --> shifting 5 bits to the left
	int md_2 = md * 64; //6--> shifting 6 bits to the left
	int mois_input;
	int motor_status; //we will check the output bits using this code
	int LED_mask=0xFFFFFFF7; //x30[3]
	int mm_mask=0xFFFFFFEF; //x30[4]
	int mw_mask=0xFFFFFFDF; //x30[5]
	int md_mask=0xFFFFFFBF; //x30[6]
   for(int i=0;i<10;i++)
    {
    	    if(i<5)
	    {
	    	printf("wet waste detected");
	    	 mois_input = 0x00000002;//mois_sen=digital_read(mois_sen_pin_number)
	    }
	    else 
	    {
	    	printf("dry waste detected");
	    	 mois_input = 0x00000000;//mois_sen=digital_read(mois_sen_pin_number)
	    }

	     int ir_input=0x00000000; //ir=digital_read(ir_pin_number) 
	     int ir_mask= 0xFFFFFFFE; //this is making ir=0 x30[0]
	     
	    asm volatile(
	    "and x30, x30, %0\n\t"
	    "or x30,x30, %1 \n\t"
	    :
	    :"r"(ir_mask), "r"(ir_input)
	    :"x30"
	    );
	    asm volatile(
	    "andi %0,x30,1\n\t"
	    :"=r"(ir)
	    :
	    :
	    );

	     
	    int mois_mask = 0xFFFFFFFD; //this is making mois_sen=1 x30[1]
	    asm volatile(
	    "and x30, x30, %0\n\t"
	    "or x30,x30, %1 \n\t"
	    :
	    :"r"(mois_mask), "r"(mois_input)
	    :"x30"
	    );
	    asm volatile(
	    "srli x10,x30,1\n\t"
	    "andi %0,x10,1\n\t"
	    :"=r"(mois_sen)
	    :
	    :"x10"
	    );
	    
	     
	    int metal_input = 0x0000000; //metal_sen=digital_read(metal_sen_pin_number)
	    int metal_mask = 0xFFFFFFFB; //this is making metal_sen=0 x30[2]
	    asm volatile(
	    "and x30, x30, %0\n\t"
	    "or x30,x30, %1 \n\t"
	    :
	    :"r"(metal_mask), "r"(metal_input)
	    :"x30"
	    );
	    asm volatile(
	    "srli x10,x30,2\n\t"
	    "andi %0,x10,1\n\t"
	    :"=r"(metal_sen)
	    :
	    :"x10"
	    );     
    	if(!ir) //If the bin is not full, we manage the waste segregation
	{
		printf("Bin is empty\n");
		 
		LED_value=0; 
		   if(!mois_sen && metal_sen)
		   {
   			mm=1;mw=0;md=0; 
   			printf("Metal waste bin is open\n");
   		   }
   		   else if(!metal_sen && mois_sen)
   		   {
   			mw=1;mm=0;md=0; 
   			printf("Wet waste bin is open\n");
                   }
   		   else if( !metal_sen && !mois_sen)
   		   {
   			md=1;mw=0;mm=0;
   			printf("Dry waste bin is open\n");
   			
   		   }
   		   else
   		   {
   		   	md=0;mw=0;mm=0;
   		   	printf("No waste detected\n");
   		   }
   		   led_value_2 = LED_value * 8;  //3 --> shifting 3 bits to the left
	mm_2= mm * 16; //4 --> shifting 4 bits to the left
	 mw_2 = mw * 32; //5  --> shifting 5 bits to the left
	 md_2 = md * 64; //6--> shifting 6 bits to the left
   		asm volatile(
		"and x30,x30,%0 \n\t"
		"or x30, x30,%1 \n\t"
		:
		:"r"(LED_mask),"r"(led_value_2)
		:"x30"
		);
		asm volatile(
		"and x30,x30,%0 \n\t"
		"or x30, x30,%1 \n\t"
		:
		:"r"(mm_mask),"r"(mm_2)
		:"x30"
		);
		asm volatile(
		"and x30,x30,%0 \n\t"
		"or x30, x30,%1 \n\t"
		:
		:"r"(mw_mask),"r"(mw_2)
		:"x30"
		);
		asm volatile(
		"and x30,x30,%0 \n\t"
		"or x30, x30,%1 \n\t"
		:
		:"r"(md_mask),"r"(md_2)
		:"x30"
		);
		
		asm volatile(
		"srli x10,x30,3\n\t"
		"andi %0, x10, 0x0000000F\n\t"
		:"=r"(motor_status)
		:
		:"x10"
		);
		printf("The motor driver status is (dry /wet/ metal/ LED) is %d \n\n",motor_status);
   					
	}
	else // we turn on the LED and donot open the lids
	{
		LED_value=1; printf("Bin is full \n");
		
		md=0;
		mw=0;
		mm=0;
		led_value_2 = LED_value * 8;  //3 --> shifting 3 bits to the left
	mm_2= mm * 16; //4 --> shifting 4 bits to the left
	 mw_2 = mw * 32; //5  --> shifting 5 bits to the left
	 md_2 = md * 64; //6--> shifting 6 bits to the left
		asm volatile(
		"and x30,x30,%0 \n\t"
		"or x30, x30,%1 \n\t"
		:
		:"r"(LED_mask),"r"(led_value_2)
		:"x30"
		);
		asm volatile(
		"and x30,x30,%0 \n\t"
		"or x30, x30,%1 \n\t"
		:
		:"r"(mm_mask),"r"(mm_2)
		:"x30"
		);
		asm volatile(
		"and x30,x30,%0 \n\t"
		"or x30, x30,%1 \n\t"
		:
		:"r"(mw_mask),"r"(mw_2)
		:"x30"
		);
		asm volatile(
		"and x30,x30,%0 \n\t"
		"or x30, x30,%1 \n\t"
		:
		:"r"(md_mask),"r"(md_2)
		:"x30"
		);
		

		asm volatile(
		"srli x10,x30,3\n\t"
		"andi %0, x10, 0x0000000F\n\t"
		:"=r"(motor_status)
		:
		:"x10"
		);
		printf("The motor driver status is (dry /wet/ metal/ LED) is %d \n\n",motor_status);
	}
	

    	
	
   }
   return(0);
}
