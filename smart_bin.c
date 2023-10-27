
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
	int LED_mask, mm_mask, mw_mask, md_mask;

while(1)
{
	    asm volatile(
	    "andi %0,x30,1\n\t"
	    :"=r"(ir)
	    :
	    :
	    );

	    asm volatile(
	  //  "srli x10,x30,1\n\t"
	    "andi %0,x30,0x0002\n\t"
	    :"=r"(mois_sen)
	    :
	    :
	    );
	    
	    asm volatile(
	  //  "srli x10,x30,2\n\t"
	    "andi %0,x30,0x0004\n\t"
	    :"=r"(metal_sen)
	    :
	    :
	    );     
    	if(!ir) //If the bin is not full, we manage the waste segregation
	{
		
		LED_value=0; 
		   if(!mois_sen && metal_sen)
		   {
   			mm=1;mw=0;md=0;  //metal waste bin is open
   			
   		   }
   		   else if(!metal_sen && mois_sen)
   		   {
   			mw=1;mm=0;md=0;  //wet waste bin is open
   			
                   }
   		   else if( !metal_sen && !mois_sen)
   		   {
   			md=1;mw=0;mm=0; //dry waste bin is open
   			
   			
   		   }
   		   else
   		   {
   		   	md=0;mw=0;mm=0; //no waste detected, none of the bins are open
   		   	
   		   }
	LED_mask=0xFFFFFFF7; //x30[3]
	mm_mask=0xFFFFFFEF; //x30[4]
	mw_mask=0xFFFFFFDF; //x30[5]
	md_mask=0xFFFFFFBF; //x30[6]   		   
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
		
		
	}
	else // we turn on the LED and donot open the lids
	{
		LED_value=1; 
		
		md=0;
		mw=0;
		mm=0;
		led_value_2 = LED_value * 8;  //3 --> shifting 3 bits to the left
		mm_2= mm * 16; //4 --> shifting 4 bits to the left
		mw_2 = mw * 32; //5  --> shifting 5 bits to the left
	 	md_2 = md * 64; //6--> shifting 6 bits to the left
	LED_mask=0xFFFFFFF7; //x30[3]
	mm_mask=0xFFFFFFEF; //x30[4]
	mw_mask=0xFFFFFFDF; //x30[5]
	md_mask=0xFFFFFFBF; //x30[6]	 	
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
		
	}
  	
	
}
   return(0);
}
