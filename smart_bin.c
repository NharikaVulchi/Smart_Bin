int main()
{
    
   
	int ir; // output from IR sensor : 1 is for close proximity, 0
	int metal_sen ; // output from the metal detecting sensor : 1 is for metal detected, 1
	int mois_sen ; // output from the moisture detecting sensor : 1 is for moisture detected, 2
	int mm=0;
	int mw=0;
	int md=0; // gpio's for motors operating the open-close of metal,wet and dry lids respectively
	int LED_value=0;
 	int led_value_2 = LED_value * 16;  //4
	int mm_2= mm * 32; //5
	int mw_2 = mw * 64; //6
	int md_2 = md *128; //7
    while(1)
    {
	     ir=0; //ir=digital_read(ir_pin_number) 
	    asm volatile(
	    "andi %0 , x30, 0x01\n\t"
	    :"=r"(ir)
	    :
	    :
	    );
	    mois_sen=0; //mois_sen=digital_read(mois_sen_pin_number)
	    asm volatile(
	    "andi %0 , x30, 0x02\n\t"
	    :"=r"(mois_sen)
	    :
	    :
	    );
	    metal_sen =1; //metal_sen=digital_read(metal_sen_pin_number)
	    asm volatile(
	    "andi %0 , x30, 0x04\n\t"
	    :"=r"(metal_sen)
	    :
	    :
	    );       
    	if(!ir) //If the bin is not full, we manage the waste segregation
	{
		
		LED_value=0; 
		   if(!mois_sen && metal_sen)
		   {
   			mm=1;mw=0;md=0; 
   		   }
   		   else if(!metal_sen && mois_sen)
   		   {
   			mw=1;mm=0;md=0; 
                   }
   		   else if( !metal_sen && !mois_sen)
   		   {
   			md=1;mw=0;mm=0;
   		   }
   		   else
   		   {
   		   	md=0;mw=0;mm=0;
   		   }
   					
	}
	else // we turn on the LED and donot open the lids
	{
		LED_value=1; 
		md=0;
		mw=0;
		mm=0;

	}
	
		asm volatile(
		"or x30, x30,%0 \n\t"
		:
		:"r"(led_value_2)
		:"x30"
		);
		asm volatile(
		"or x30, x30,%0 \n\t"
		:
		:"r"(mm_2)
		:"x30"
		);
		asm volatile(
		"or x30, x30,%0 \n\t"
		:
		:"r"(mw_2)
		:"x30"
		);
		asm volatile(
		"or x30, x30,%0 \n\t"
		:
		:"r"(md_2)
		:"x30"
		);	
    return(0);	
	
   }
}

