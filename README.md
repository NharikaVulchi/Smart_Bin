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
	    "andi %0,x30,0x0002\n\t"
	    :"=r"(mois_sen)
	    :
	    :
	    );
	    
	    asm volatile(
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
   		   led_value_2 = LED_value * 8;  
		   mm_2= mm * 16; 
	 	   mw_2 = mw * 32; 
		   md_2 = md * 64; 
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
		led_value_2 = LED_value * 8;  
		mm_2= mm * 16; 
		mw_2 = mw * 32; 
	 	md_2 = md * 64; 
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

```





# functionality output using spike


commands used:

```
riscv32-unknown-elf-gcc -march=rv64i -mabi=lp64 -ffreestanding -o smart_bin smart_bin_new.c
spike pk smart_bin
```

**Observations:**

1. When the **mois_sen** value is 1 for the first 5 iterations, the wet bin is open and the corresponding motor driver should be high. The **motor driver status** in the below screenshot corresponds to the 4 output bits from the x30 register which are the **x30[6:3]** bits in the mentioned order i.e., dry/wet/metal/LED
2. So when wet waste is detected, the wet bin notor driver is high and the bits **x30[6:3]** is **0100** which is 4
3. Similarly, when **mois_sen** is 0, dry waste is detected , dry bin motor driver is high and **x30[6:3]** is **1000** which is 8
4. Also, since **ir** is given 0 as input, which says that bin is not full, we can see the message **"Bin is empty"**.

   
![spike_sim1](https://github.com/NharikaVulchi/Smart_Bin/assets/83216569/784e518b-40a2-42d1-bac7-bf8af6b0ca70)


![spike+sim2](https://github.com/NharikaVulchi/Smart_Bin/assets/83216569/cfbd8e39-0fa1-4dcb-b3de-a7056c08326a)


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
   10054:	fb010113          	addi	sp,sp,-80
   10058:	04812623          	sw	s0,76(sp)
   1005c:	05010413          	addi	s0,sp,80
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
   100a0:	001f7793          	andi	a5,t5,1
   100a4:	fcf42623          	sw	a5,-52(s0)
   100a8:	002f7793          	andi	a5,t5,2
   100ac:	fcf42423          	sw	a5,-56(s0)
   100b0:	004f7793          	andi	a5,t5,4
   100b4:	fcf42223          	sw	a5,-60(s0)
   100b8:	fcc42783          	lw	a5,-52(s0)
   100bc:	10079a63          	bnez	a5,101d0 <main+0x17c>
   100c0:	fe042023          	sw	zero,-32(s0)
   100c4:	fc842783          	lw	a5,-56(s0)
   100c8:	02079063          	bnez	a5,100e8 <main+0x94>
   100cc:	fc442783          	lw	a5,-60(s0)
   100d0:	00078c63          	beqz	a5,100e8 <main+0x94>
   100d4:	00100793          	li	a5,1
   100d8:	fef42623          	sw	a5,-20(s0)
   100dc:	fe042423          	sw	zero,-24(s0)
   100e0:	fe042223          	sw	zero,-28(s0)
   100e4:	0580006f          	j	1013c <main+0xe8>
   100e8:	fc442783          	lw	a5,-60(s0)
   100ec:	02079063          	bnez	a5,1010c <main+0xb8>
   100f0:	fc842783          	lw	a5,-56(s0)
   100f4:	00078c63          	beqz	a5,1010c <main+0xb8>
   100f8:	00100793          	li	a5,1
   100fc:	fef42423          	sw	a5,-24(s0)
   10100:	fe042623          	sw	zero,-20(s0)
   10104:	fe042223          	sw	zero,-28(s0)
   10108:	0340006f          	j	1013c <main+0xe8>
   1010c:	fc442783          	lw	a5,-60(s0)
   10110:	02079063          	bnez	a5,10130 <main+0xdc>
   10114:	fc842783          	lw	a5,-56(s0)
   10118:	00079c63          	bnez	a5,10130 <main+0xdc>
   1011c:	00100793          	li	a5,1
   10120:	fef42223          	sw	a5,-28(s0)
   10124:	fe042423          	sw	zero,-24(s0)
   10128:	fe042623          	sw	zero,-20(s0)
   1012c:	0100006f          	j	1013c <main+0xe8>
   10130:	fe042223          	sw	zero,-28(s0)
   10134:	fe042423          	sw	zero,-24(s0)
   10138:	fe042623          	sw	zero,-20(s0)
   1013c:	ff700793          	li	a5,-9
   10140:	fcf42023          	sw	a5,-64(s0)
   10144:	fef00793          	li	a5,-17
   10148:	faf42e23          	sw	a5,-68(s0)
   1014c:	fdf00793          	li	a5,-33
   10150:	faf42c23          	sw	a5,-72(s0)
   10154:	fbf00793          	li	a5,-65
   10158:	faf42a23          	sw	a5,-76(s0)
   1015c:	fe042783          	lw	a5,-32(s0)
   10160:	00379793          	slli	a5,a5,0x3
   10164:	fcf42e23          	sw	a5,-36(s0)
   10168:	fec42783          	lw	a5,-20(s0)
   1016c:	00479793          	slli	a5,a5,0x4
   10170:	fcf42c23          	sw	a5,-40(s0)
   10174:	fe842783          	lw	a5,-24(s0)
   10178:	00579793          	slli	a5,a5,0x5
   1017c:	fcf42a23          	sw	a5,-44(s0)
   10180:	fe442783          	lw	a5,-28(s0)
   10184:	00679793          	slli	a5,a5,0x6
   10188:	fcf42823          	sw	a5,-48(s0)
   1018c:	fc042783          	lw	a5,-64(s0)
   10190:	fdc42703          	lw	a4,-36(s0)
   10194:	00ff7f33          	and	t5,t5,a5
   10198:	00ef6f33          	or	t5,t5,a4
   1019c:	fbc42783          	lw	a5,-68(s0)
   101a0:	fd842703          	lw	a4,-40(s0)
   101a4:	00ff7f33          	and	t5,t5,a5
   101a8:	00ef6f33          	or	t5,t5,a4
   101ac:	fb842783          	lw	a5,-72(s0)
   101b0:	fd442703          	lw	a4,-44(s0)
   101b4:	00ff7f33          	and	t5,t5,a5
   101b8:	00ef6f33          	or	t5,t5,a4
   101bc:	fb442783          	lw	a5,-76(s0)
   101c0:	fd042703          	lw	a4,-48(s0)
   101c4:	00ff7f33          	and	t5,t5,a5
   101c8:	00ef6f33          	or	t5,t5,a4
   101cc:	ed5ff06f          	j	100a0 <main+0x4c>
   101d0:	00100793          	li	a5,1
   101d4:	fef42023          	sw	a5,-32(s0)
   101d8:	fe042223          	sw	zero,-28(s0)
   101dc:	fe042423          	sw	zero,-24(s0)
   101e0:	fe042623          	sw	zero,-20(s0)
   101e4:	fe042783          	lw	a5,-32(s0)
   101e8:	00379793          	slli	a5,a5,0x3
   101ec:	fcf42e23          	sw	a5,-36(s0)
   101f0:	fec42783          	lw	a5,-20(s0)
   101f4:	00479793          	slli	a5,a5,0x4
   101f8:	fcf42c23          	sw	a5,-40(s0)
   101fc:	fe842783          	lw	a5,-24(s0)
   10200:	00579793          	slli	a5,a5,0x5
   10204:	fcf42a23          	sw	a5,-44(s0)
   10208:	fe442783          	lw	a5,-28(s0)
   1020c:	00679793          	slli	a5,a5,0x6
   10210:	fcf42823          	sw	a5,-48(s0)
   10214:	ff700793          	li	a5,-9
   10218:	fcf42023          	sw	a5,-64(s0)
   1021c:	fef00793          	li	a5,-17
   10220:	faf42e23          	sw	a5,-68(s0)
   10224:	fdf00793          	li	a5,-33
   10228:	faf42c23          	sw	a5,-72(s0)
   1022c:	fbf00793          	li	a5,-65
   10230:	faf42a23          	sw	a5,-76(s0)
   10234:	fc042783          	lw	a5,-64(s0)
   10238:	fdc42703          	lw	a4,-36(s0)
   1023c:	00ff7f33          	and	t5,t5,a5
   10240:	00ef6f33          	or	t5,t5,a4
   10244:	fbc42783          	lw	a5,-68(s0)
   10248:	fd842703          	lw	a4,-40(s0)
   1024c:	00ff7f33          	and	t5,t5,a5
   10250:	00ef6f33          	or	t5,t5,a4
   10254:	fb842783          	lw	a5,-72(s0)
   10258:	fd442703          	lw	a4,-44(s0)
   1025c:	00ff7f33          	and	t5,t5,a5
   10260:	00ef6f33          	or	t5,t5,a4
   10264:	fb442783          	lw	a5,-76(s0)
   10268:	fd042703          	lw	a4,-48(s0)
   1026c:	00ff7f33          	and	t5,t5,a5
   10270:	00ef6f33          	or	t5,t5,a4
   10274:	e2dff06f          	j	100a0 <main+0x4c>
```

**Number of unique instructions**


Number of different instructions: 11


List of unique instructions:


beqz


li


and


lw


bnez

slli


andi


j


sw


addi


   

# Functional simulation

1. In the below image we can see that the contents of **ID_instructions** are incrementing in accoradance to that of assembly code, which resembles the increase in the PC or our execution.
2. We can see the flags **"$signal[31;0], top_gpio_pins[31:0]"**, which resembles the x30 register.

![image](https://github.com/NharikaVulchi/Smart_Bin/assets/83216569/d751fe04-2877-43f7-b474-3e85cb0284c0)


1. The code involves use of 3 input_gpio_pins reading the values from the IR,moisture and metal proximity sensor  and 4 output_gpio_pins writing the values to the LED and 3 output motor drivers
2. When the input_gpio_pins is given by **001** (LSB to the IR sensor output), indicating that output from **IR sensor is 1**, the output shows **0001** indicating that LED is ON and the bin is full.This is demonstrated in the below figure. 
3. The below image shows for another case of input **010** indicating mositure sensor output to be 1, hence the wet bin motor driver is open which is given by **0100**
4. When the input is **100**, indicating metal proximity sensor output is 1, hence the metal waste collecting bin is open , which resembles **0010** in the output.
5. Similarly, input is **000** , output is **1000**, dry waste collecting bin is open.


![image](https://github.com/NharikaVulchi/Smart_Bin/assets/83216569/af981d0c-9051-4af3-a1ef-856c4714892a)

![image](https://github.com/NharikaVulchi/Smart_Bin/assets/83216569/91205a61-310f-48bb-826d-9e28051f71ca)

![image](https://github.com/NharikaVulchi/Smart_Bin/assets/83216569/334e6aea-c477-4cbc-902f-ae9f5d2ebc55)

![image](https://github.com/NharikaVulchi/Smart_Bin/assets/83216569/afc68cd0-fa9e-4ab3-9360-777aa5b788db)

6. In the below figure, we can observe that the output is being dumped at the instruction **00ef6f33** for the two input cases, which we can see in the assembly text that this instruction corresponds to **or** instruction, using _t5_ register.

![image](https://github.com/NharikaVulchi/Smart_Bin/assets/83216569/9f420b92-934c-4593-8e49-0f58c97850c9)

![image](https://github.com/NharikaVulchi/Smart_Bin/assets/83216569/1c131485-1067-400c-b085-aec2c8bc3ae0)

![image](https://github.com/NharikaVulchi/Smart_Bin/assets/83216569/4c3fcb0f-a9b3-48d4-a900-9de3e9028d5d)

# GLS

1. We perform the Gate Level Simulation on the netlist file synthesised from **yosys**.
2.  This file basically maps the standard cells of **sky130** library to our design
3.  Performing the GLS on our design, validates the logic of our design that is generated.
4.  Following are the steps to convert our processor code to netlist:

```
read_liberty -lib sky130_fd_sc_hd__tt_025C_1v80_256.lib 
read_verilog processor.v
synth -top wrapper
dfflibmap -liberty sky130_fd_sc_hd__tt_025C_1v80_256.lib 
abc -liberty sky130_fd_sc_hd__tt_025C_1v80_256.lib
write_verilog syntheised__processor_test.v
```
5. To run the GLS simulation, follow the below commands:

```
iverilog -o test2 testbench.v syntheised__processor_test.v sky130_sram_1kbyte_1rw1r_32x256_8.v sky130_fd_sc_hd.v primitives.v 
./test2
gtkwave waveform.vcd
```

In the synthesis, we can see the instantiation of 2 SRAM cells from the sky130 lib

![image](https://github.com/NharikaVulchi/Smart_Bin/assets/83216569/73e421ba-75e2-49eb-847c-77338a0076eb)

The generated synthesised netlist for the wrapper module shows the instantiation of 2 SRAM cells.

![image](https://github.com/NharikaVulchi/Smart_Bin/assets/83216569/529646c4-4ac1-4a04-801a-b6842fdb4d59)

When we run the GLS for the synthesised netlist **synthesised__processor_test.v** we can see the use of sky130 cells in the gtkwave window and also the output that was matching with the functionality simulation for the input case **010**

![image](https://github.com/NharikaVulchi/Smart_Bin/assets/83216569/dd2d4a52-d080-469b-9cca-1228ffc78ee2)

![image](https://github.com/NharikaVulchi/Smart_Bin/assets/83216569/21af3368-3f02-42b8-9fb6-699f381ea727)

# PNR flow

OpenLane flow is implemented for the ASIC design "SMART_BIN" , the following are the steps followed in the entire flow :

```
./flow.tcl -interactive
package require openlane 0.9
prep -design smart_project
run_synthesis
run_floorplan
run_placement
run_cts
gen_pdn
run_routing
```
Each stage reports and output ,viewed in magic , is shown below:



**Synthesis**

![image](https://github.com/NharikaVulchi/Smart_Bin/assets/83216569/4b0aff5e-eb18-4035-9329-deb3e591b4d2)


**synthesis reports**

![image](https://github.com/NharikaVulchi/Smart_Bin/assets/83216569/c4b10d15-0ee9-4b85-a4c0-4a050e21d32d)

**area reports**

![image](https://github.com/NharikaVulchi/Smart_Bin/assets/83216569/cf7d89ac-205e-4f74-aa2d-0583302f4dec)

![image](https://github.com/NharikaVulchi/Smart_Bin/assets/83216569/9e0fd814-8385-4b5e-a91d-527f5ad14b68)

**CTS reports**

**power**
![image](https://github.com/NharikaVulchi/Smart_Bin/assets/83216569/be36c178-4d42-4d9f-93bf-4878ad2934b2)

**Timing**
![image](https://github.com/NharikaVulchi/Smart_Bin/assets/83216569/e5bd58d4-079a-492d-aabe-83acbf08b409)

**Area**

![image](https://github.com/NharikaVulchi/Smart_Bin/assets/83216569/b596eb4a-241d-4aa7-af8a-21745f09f415)


**Placement**

Before this step, make sure to give the appropriate values according to your design for the **FP_CORE_UTIL** and **PL_TARGET_DENSITY** in the config.json file


![image](https://github.com/NharikaVulchi/Smart_Bin/assets/83216569/227b1cbe-2192-4acb-9221-a595a0e55ebc)

**viewing the placement in magic**

```
magic -T /home/niharika/vsdstdcelldesign/libs/sky130A.tech lef read /home/niharika/OpenLane/designs/smart_project/runs/RUN_2023.11.13_16.37.51/tmp/merged.nom.lef def read /home/niharika/OpenLane/designs/smart_project/runs/RUN_2023.11.13_16.37.51/results/placement/wrapper.def &

````



![image](https://github.com/NharikaVulchi/Smart_Bin/assets/83216569/21661e7b-8e25-415b-b0df-3a48b5144cf2)



**Routing**



![image](https://github.com/NharikaVulchi/Smart_Bin/assets/83216569/c37cffcc-9a11-43f1-81cd-8fa7c693804f)


After routing is done, we view the post routing log reports and routing of our design layout in magic:

code
```
magic -T /home/niharika/vsdstdcelldesign/libs/sky130A.tech lef read /home/niharika/OpenLane/designs/smart_project/runs/RUN_2023.11.14_15.01.04/tmp/merged.nom.lef def read /home/niharika/OpenLane/designs/smart_project/runs/RUN_2023.11.14_15.01.04/results/routing/wrapper.def &

```


![Screenshot from 2023-11-14 21-52-50](https://github.com/NharikaVulchi/Smart_Bin/assets/83216569/a9bc221d-5df3-46a0-85b5-15b66fdfdcd7)

![image](https://github.com/NharikaVulchi/Smart_Bin/assets/83216569/d74c29f8-a6ea-41f5-86af-76be042602a3)

![image](https://github.com/NharikaVulchi/Smart_Bin/assets/83216569/81d034bb-4d18-4b6a-b5aa-40279180baae)

**post routing power report**

![image](https://github.com/NharikaVulchi/Smart_Bin/assets/83216569/bd2fc010-8fbe-4e75-8784-2ca81c657d55)

**post routing timing report**
![image](https://github.com/NharikaVulchi/Smart_Bin/assets/83216569/7eeb4b76-1d60-42c6-b95b-dd3b908b8fc5)

**post routing design area**
![image](https://github.com/NharikaVulchi/Smart_Bin/assets/83216569/6c53c923-56cf-4f64-baa0-2d28759b9c14)

**DRC violations**

![image](https://github.com/NharikaVulchi/Smart_Bin/assets/83216569/7d0a996f-56b3-4816-bd0f-77afcb271d76)

# files
**config.json** used:

```
{
    "DESIGN_NAME": "wrapper",
    "VERILOG_FILES": "dir::src/processor.v",
    "CLOCK_PORT": "clk",
    "CLOCK_NET": "clk",
    "GLB_RESIZER_TIMING_OPTIMIZATIONS": true,
    "CLOCK_PERIOD": 70 ,
    "FP_SIZING": "relative",
    "PL_TARGET_DENSITY": 0.3,
    "DIODE_PADDING" : 1, 
    "SYNTH_NO_FLAT" : 1, 
    "DESIGN_IS_CORE": 1,
    "SYNTH_STRATEGY" : "DELAY 1", 
    "STA_REPORT_POWER":1,
     "CTS_REPORT_TIMING":1,
     "GENERATE_FINAL_SUMMARY_REPORT":1,
    "GRT_MACRO_EXTENSION" : 0,
    "PL_MACRO_HALO" : "550 450", 
    "PL_MACRO_CHANNEL" : "100 100",
    "RUN_HEURISTIC_DIODE_INSERTION" : 5, 
    "MACRO_PLACEMENT_CFG": "dir::macro_placement.cfg",
    "FP_PDN_ENABLE_RAILS" : 1, 
    "GRT_OVERFLOW_ITERS" : 150, 
    "FP_PDN_CORE_RING" : 1 ,
    "VDD_NETS": ["vccd1", "VPWR", "VPB"],
    "GND_NETS": ["vssd1", "VGND", "VNB"],
    "EXTRA_LEFS": "dir::src/sky130_sram_1kbyte_1rw1r_32x256_8.lef",
    "EXTRA_GDS_FILES": "dir::src/sky130_sram_1kbyte_1rw1r_32x256_8.gds",
    "EXTRA_LIBS": "dir::src/sky130_sram_1kbyte_1rw1r_32x256_8_TT_1p8V_25C.lib",
    "pdk::sky130*": {
        "FP_CORE_UTIL": 20,
        "scl::sky130_fd_sc_hd": {
            "FP_CORE_UTIL": 20
        }
    },
    
    "LIB_SYNTH": "dir::src/sky130_fd_sc_hd__tt_025C_1v80.lib",
    "LIB_FASTEST": "dir::src/sky130_fd_sc_hd__ff_100C_1v65.lib",
    "LIB_SLOWEST": "dir::src/sky130_fd_sc_hd__ss_100C_1v60.lib",
    "LIB_TYPICAL": "dir::src/sky130_fd_sc_hd__tt_025C_1v80.lib"


}
```


   


# Acknowledgement

* Kunal Ghosh, VSD Corp. Pvt. Ltd.
* Mayank Kabra, Founder,Chipcron Pvt.Ltd.

# Reference

https://electronicslovers.com/


https://github.com/SakethGajawada/RISCV-GNU


https://github.com/kunalg123




