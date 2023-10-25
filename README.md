# Smart_Bin

**Problem Statement**


* Waste disposal is a major problem in today's world. The  method of removing the large amount of waste generated has a harmful effect on the environment. Unplanned landfilling by municipalities is a common waste disposal method. This method affects the health of people, plants and animals.
* When waste is separated into basic streams such as wet, dry and metal, the waste has greater potential for recovery and as a result is recycled and reused.
* The wet waste fraction  often becomes either  compost or methane gas, or both. Compost can replace the demand for chemical fertilizers and biogas can be used as an energy source.
* Scrap metal can be recycled or recycled.
* Although there are large-scale industrial waste sorting facilities, it is always much better to sort the waste itself at the source.
* The advantage is that  higher quality  material is left for recycling, which means more value is obtained from the waste. The occupational hazard of waste workers is reduced.
* Sorted waste could also be sent directly  to a recycling and processing plant instead of going to a sorting facility rather than a recycling plant.

**Proposed Solution**

* A smart waste segregator is implemented which sorts the waste into metal, dry and wet based on sensor values.
* Inductive proximity sensors are employed to identify metallic items, and moisture sensors to distinguish between wet and dry waste depending upon the threshold values set.
* Upon the corresponding sensor values, DC motors are operated to open the lids of concerned bins to segregate the waste
* Also, when the bin is full, none of the lids are opened and a LED is turned ON to indicate that garbage is full.

# Implementation

Step-1 : The waste is sensed by the inductive proximity sensor to detect if it is a metal or not.


Step-2:  If the waste is metal waste then M1 is turned on and M2 is turned off and the waste is pushed into the metal waste bin. 


Step-3:  If not a metallic waste, M1 is kept off when it comes in contact with the moisture sensor that decides whether the waste is a wet waste or dry waste by checking the moisture content of the waste.


Step-4:  If the waste has some humidity it is detected as wet waste and M1 is turned off and M2 is turned on and the waste is pushed into the wet waste bin.


Step-5:  If not a wet waste M1 is kept off and then the waste is dropped into the dry waste bin placed after turning on M3.


Step-6:  Finally the wastes are dropped into the respective bins and the segregation process is completed.

# Flowchart

The flowchart and block diagram for the proposed solution are shown below:

![Untitled Workspace(4)](https://github.com/NharikaVulchi/Smart_Bin/assets/83216569/b7c2eba2-821c-4993-b802-55bfd7e133c6)

![Untitled Workspace(3)](https://github.com/NharikaVulchi/Smart_Bin/assets/83216569/205e1340-7cc1-4e82-b4a4-93d1a76bffff)



# C code

**x30 register**

x30[0] --> data read from IR sensor used as input

x30[1] --> data read from moisture sensor used as input

x30[2] --> data read from inductive proximity sensor used as input
 
x30[3] --> output to LED

x30[4] --> output to motor driver 1 (bin connecting metal waste )

x30[5] --> output to motor driver 2 (bin connecting wet waste )

x30[6] --> output to motor driver 3 (bin connecting dry waste )

We propose to build this solution using a RISC-V ASIC. The corresponding C code is shown below:

```

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
while(1)
{

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
		
	}
  	
	
}
   return(0);
}

```


The above code is compiled using :

Move to the directory with the Code file :

```
gcc compile smart_bin.c
./a.out
```

**output**

the input value of IR sensor is given as 0. we can see that the output shows, bin is empty

![image](https://github.com/NharikaVulchi/Smart_Bin/assets/83216569/2d8efe4b-eee5-4a0f-bcc8-cb5ac6883e8f)

# Spike simulation 


We change the C code , to test the functionality using spike.
5 of the input test cases run for **moisture_sensor** input to be 1 and other 5 the input value to be 0


```
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
```

# functionality output using spike


commands used:

```
riscv64-unknown-elf-gcc -march=rv64i -mabi=lp64 -ffreestanding -o smart_bin smart_bin_new.c
spike pk smart_bin
```

**Observations:**

1. When the **mois_sen** value is 1 for the first 5 iterations, the wet bin is open and the corresponding motor driver should be high. The **motor driver status** in the below screenshot corresponds to the 4 output bits from the x30 register which are the **x30[6:3]** bits in the mentioned order i.e., dry/wet/metal/LED
2. So when wet waste is detected, the wet bin notor driver is high and the bits **x30[6:3]** is **0100** which is 4
3. Similarly, when **mois_sen** is 0, dry waste is detected , dry bin motor driver is high and **x30[6:3]** is **1000** which is 8
4. Also, since **ir** is given 0 as input, which says that bin is not full, we can see the message **"Bin is empty"**.

   
![spike_sim1](https://github.com/NharikaVulchi/Smart_Bin/assets/83216569/784e518b-40a2-42d1-bac7-bf8af6b0ca70)


![spike+sim2](https://github.com/NharikaVulchi/Smart_Bin/assets/83216569/cfbd8e39-0fa1-4dcb-b3de-a7056c08326a)


# Assembly code


we run the RISC-V GNU using:

```
/home/niharika/Downloads/riscv64-unknown-elf-gcc -march=rv32i -mabi=ilp32 -ffreestanding -nostdlib -o smart_bin filename.c 
/home/niharika/Downloads/riscv64-unknown-elf-objdump -d -r smart_bin > smart_bin_assembly_2.txt
```


```

smart_bin:     file format elf32-littleriscv


Disassembly of section .text:

00010054 <main>:
   10054:	f9010113          	addi	sp,sp,-112
   10058:	06812623          	sw	s0,108(sp)
   1005c:	07010413          	addi	s0,sp,112
   10060:	fe042623          	sw	zero,-20(s0)
   10064:	fe042423          	sw	zero,-24(s0)
   10068:	fe042223          	sw	zero,-28(s0)
   1006c:	fe042023          	sw	zero,-32(s0)
   10070:	fe042783          	lw	a5,-32(s0)
   10074:	00379793          	slli	a5,a5,0x3
   10078:	fcf42e23          	sw	a5,-36(s0)
   1007c:	fec42783          	lw	a5,-20(s0)
   10080:	00479793          	slli	a5,a5,0x4
   10084:	fcf42c23          	sw	a5,-40(s0)
   10088:	fe842783          	lw	a5,-24(s0)
   1008c:	00579793          	slli	a5,a5,0x5
   10090:	fcf42a23          	sw	a5,-44(s0)
   10094:	fe442783          	lw	a5,-28(s0)
   10098:	00679793          	slli	a5,a5,0x6
   1009c:	fcf42823          	sw	a5,-48(s0)
   100a0:	ff700793          	li	a5,-9
   100a4:	fcf42623          	sw	a5,-52(s0)
   100a8:	fef00793          	li	a5,-17
   100ac:	fcf42423          	sw	a5,-56(s0)
   100b0:	fdf00793          	li	a5,-33
   100b4:	fcf42223          	sw	a5,-60(s0)
   100b8:	fbf00793          	li	a5,-65
   100bc:	fcf42023          	sw	a5,-64(s0)
   100c0:	fa042e23          	sw	zero,-68(s0)
   100c4:	ffe00793          	li	a5,-2
   100c8:	faf42c23          	sw	a5,-72(s0)
   100cc:	fb842783          	lw	a5,-72(s0)
   100d0:	fbc42703          	lw	a4,-68(s0)
   100d4:	00ff7f33          	and	t5,t5,a5
   100d8:	00ef6f33          	or	t5,t5,a4
   100dc:	001f7793          	andi	a5,t5,1
   100e0:	faf42a23          	sw	a5,-76(s0)
   100e4:	ffd00793          	li	a5,-3
   100e8:	faf42823          	sw	a5,-80(s0)
   100ec:	fb042783          	lw	a5,-80(s0)
   100f0:	fac42703          	lw	a4,-84(s0)
   100f4:	00ff7f33          	and	t5,t5,a5
   100f8:	00ef6f33          	or	t5,t5,a4
   100fc:	001f5513          	srli	a0,t5,0x1
   10100:	00157793          	andi	a5,a0,1
   10104:	faf42423          	sw	a5,-88(s0)
   10108:	fa042223          	sw	zero,-92(s0)
   1010c:	ffb00793          	li	a5,-5
   10110:	faf42023          	sw	a5,-96(s0)
   10114:	fa042783          	lw	a5,-96(s0)
   10118:	fa442703          	lw	a4,-92(s0)
   1011c:	00ff7f33          	and	t5,t5,a5
   10120:	00ef6f33          	or	t5,t5,a4
   10124:	002f5513          	srli	a0,t5,0x2
   10128:	00157793          	andi	a5,a0,1
   1012c:	f8f42e23          	sw	a5,-100(s0)
   10130:	fb442783          	lw	a5,-76(s0)
   10134:	10079063          	bnez	a5,10234 <main+0x1e0>
   10138:	fe042023          	sw	zero,-32(s0)
   1013c:	fa842783          	lw	a5,-88(s0)
   10140:	02079063          	bnez	a5,10160 <main+0x10c>
   10144:	f9c42783          	lw	a5,-100(s0)
   10148:	00078c63          	beqz	a5,10160 <main+0x10c>
   1014c:	00100793          	li	a5,1
   10150:	fef42623          	sw	a5,-20(s0)
   10154:	fe042423          	sw	zero,-24(s0)
   10158:	fe042223          	sw	zero,-28(s0)
   1015c:	0580006f          	j	101b4 <main+0x160>
   10160:	f9c42783          	lw	a5,-100(s0)
   10164:	02079063          	bnez	a5,10184 <main+0x130>
   10168:	fa842783          	lw	a5,-88(s0)
   1016c:	00078c63          	beqz	a5,10184 <main+0x130>
   10170:	00100793          	li	a5,1
   10174:	fef42423          	sw	a5,-24(s0)
   10178:	fe042623          	sw	zero,-20(s0)
   1017c:	fe042223          	sw	zero,-28(s0)
   10180:	0340006f          	j	101b4 <main+0x160>
   10184:	f9c42783          	lw	a5,-100(s0)
   10188:	02079063          	bnez	a5,101a8 <main+0x154>
   1018c:	fa842783          	lw	a5,-88(s0)
   10190:	00079c63          	bnez	a5,101a8 <main+0x154>
   10194:	00100793          	li	a5,1
   10198:	fef42223          	sw	a5,-28(s0)
   1019c:	fe042423          	sw	zero,-24(s0)
   101a0:	fe042623          	sw	zero,-20(s0)
   101a4:	0100006f          	j	101b4 <main+0x160>
   101a8:	fe042223          	sw	zero,-28(s0)
   101ac:	fe042423          	sw	zero,-24(s0)
   101b0:	fe042623          	sw	zero,-20(s0)
   101b4:	fe042783          	lw	a5,-32(s0)
   101b8:	00379793          	slli	a5,a5,0x3
   101bc:	fcf42e23          	sw	a5,-36(s0)
   101c0:	fec42783          	lw	a5,-20(s0)
   101c4:	00479793          	slli	a5,a5,0x4
   101c8:	fcf42c23          	sw	a5,-40(s0)
   101cc:	fe842783          	lw	a5,-24(s0)
   101d0:	00579793          	slli	a5,a5,0x5
   101d4:	fcf42a23          	sw	a5,-44(s0)
   101d8:	fe442783          	lw	a5,-28(s0)
   101dc:	00679793          	slli	a5,a5,0x6
   101e0:	fcf42823          	sw	a5,-48(s0)
   101e4:	fcc42783          	lw	a5,-52(s0)
   101e8:	fdc42703          	lw	a4,-36(s0)
   101ec:	00ff7f33          	and	t5,t5,a5
   101f0:	00ef6f33          	or	t5,t5,a4
   101f4:	fc842783          	lw	a5,-56(s0)
   101f8:	fd842703          	lw	a4,-40(s0)
   101fc:	00ff7f33          	and	t5,t5,a5
   10200:	00ef6f33          	or	t5,t5,a4
   10204:	fc442783          	lw	a5,-60(s0)
   10208:	fd442703          	lw	a4,-44(s0)
   1020c:	00ff7f33          	and	t5,t5,a5
   10210:	00ef6f33          	or	t5,t5,a4
   10214:	fc042783          	lw	a5,-64(s0)
   10218:	fd042703          	lw	a4,-48(s0)
   1021c:	00ff7f33          	and	t5,t5,a5
   10220:	00ef6f33          	or	t5,t5,a4
   10224:	003f5513          	srli	a0,t5,0x3
   10228:	00f57793          	andi	a5,a0,15
   1022c:	f8f42c23          	sw	a5,-104(s0)
   10230:	e91ff06f          	j	100c0 <main+0x6c>
   10234:	00100793          	li	a5,1
   10238:	fef42023          	sw	a5,-32(s0)
   1023c:	fe042223          	sw	zero,-28(s0)
   10240:	fe042423          	sw	zero,-24(s0)
   10244:	fe042623          	sw	zero,-20(s0)
   10248:	fe042783          	lw	a5,-32(s0)
   1024c:	00379793          	slli	a5,a5,0x3
   10250:	fcf42e23          	sw	a5,-36(s0)
   10254:	fec42783          	lw	a5,-20(s0)
   10258:	00479793          	slli	a5,a5,0x4
   1025c:	fcf42c23          	sw	a5,-40(s0)
   10260:	fe842783          	lw	a5,-24(s0)
   10264:	00579793          	slli	a5,a5,0x5
   10268:	fcf42a23          	sw	a5,-44(s0)
   1026c:	fe442783          	lw	a5,-28(s0)
   10270:	00679793          	slli	a5,a5,0x6
   10274:	fcf42823          	sw	a5,-48(s0)
   10278:	fcc42783          	lw	a5,-52(s0)
   1027c:	fdc42703          	lw	a4,-36(s0)
   10280:	00ff7f33          	and	t5,t5,a5
   10284:	00ef6f33          	or	t5,t5,a4
   10288:	fc842783          	lw	a5,-56(s0)
   1028c:	fd842703          	lw	a4,-40(s0)
   10290:	00ff7f33          	and	t5,t5,a5
   10294:	00ef6f33          	or	t5,t5,a4
   10298:	fc442783          	lw	a5,-60(s0)
   1029c:	fd442703          	lw	a4,-44(s0)
   102a0:	00ff7f33          	and	t5,t5,a5
   102a4:	00ef6f33          	or	t5,t5,a4
   102a8:	fc042783          	lw	a5,-64(s0)
   102ac:	fd042703          	lw	a4,-48(s0)
   102b0:	00ff7f33          	and	t5,t5,a5
   102b4:	00ef6f33          	or	t5,t5,a4
   102b8:	003f5513          	srli	a0,t5,0x3
   102bc:	00f57793          	andi	a5,a0,15
   102c0:	f8f42c23          	sw	a5,-104(s0)
   102c4:	dfdff06f          	j	100c0 <main+0x6c>
```

**Number of unique instructions**


Number of different instructions: 12


List of unique instructions:


beqz


li


and


srli


lw


bnez

slli


andi


j


sw


addi


   

   


# Acknowledgement

* Kunal Ghosh, VSD Corp. Pvt. Ltd.
* Mayank Kabra

# Reference

https://electronicslovers.com/


https://github.com/SakethGajawada/RISCV-GNU







