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
 
x30[4] --> output to LED

x30[5] --> output to motor driver 1 (bin connecting metal waste )

x30[6] --> output to motor driver 2 (bin connecting wet waste )

x30[7] --> output to motor driver 3 (bin connecting dry waste )

We propose to build this solution using a RISC-V ASIC. The corresponding C code is shown below:

```

int ir; // output from IR sensor : 1 is for close proximity
int metal_sen ; // output from the metal detecting sensor : 1 is for metal detected
int mois_sen ; // output from the moisture detecting sensor : 1 is for moisture detected
int mm,mw,md; // gpio's for motors operating the open-close of metal,wet and dry lids respectively
int LED_value;

void waste_detector();
void start(int);

int main(){
    
    ir=0; //ir=digital_read(ir_pin_number) 
    asm volatile(
    "addi %0 , x30, 0\n\t"
    :"=r"(ir)
    :
    :
    );
    mois_sen=0; //mois_sen=digital_read(mois_sen_pin_number)
    asm volatile(
    "addi %0 , x30, 0\n\t"
    :"=r"(mois_sen)
    :
    :
    );
    metal_sen =1; //metal_sen=digital_read(metal_sen_pin_number)
    asm volatile(
    "addi %0 , x30, 4\n\t"
    :"=r"(metal_sen)
    :
    :
    );
    while(1){
        start(ir);
    }
    return(0);
}


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
		//printf("Bin is full\n");
		LED_value=0; //digital_write(LED_pin_number,0)
		int led_value_2 = LED_value * 16;
		asm volatile(
		"or x30, x30,%0 \n\t"
		:
		:"r"(led_value_2)
		:"x30"
		);
		waste_detector(mois_sen,metal_sen,mm,mw,md);
		int mm_2= mm * 32;
		int mw_2 = mw * 64;
		int md_2 = md *128;
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
		// digital_write(mm_pin_num,mm);
		// digital_write(mw_pin_num,mw);
		// digital_write(md_pin_num,md);				
		

	}
	else // we turn on the LED and donot open the lids
	{
		LED_value=1; //digital_write(LED_pin_number,1)
		int led_value_3 = LED_value * 16;
		asm volatile(
		"or x30, x30,%0 \n\t"
		:
		:"r"(led_value_3)
		:"x30"
		);
	}
	
	
	
}


```


The above code is compiled using :

Move to the directory with the Code file :

```
gcc compile smart_bin.c
./a.out
```

# Assembly code


we run the RISC-V GNU using:

```
/home/niharika/Downloads/riscv64-unknown-elf-gcc -march=rv32i -mabi=ilp32 -ffreestanding -nostdlib -o smart_bin filename.c 
/home/niharika/Downloads/riscv64-unknown-elf-objdump -d -r smart_bin > smart_bin_assembly_2.txt
```


```


smart_bin :     file format elf32-littleriscv


Disassembly of section .text:

00010054 <main>:
   10054:	fc010113          	addi	sp,sp,-64
   10058:	02812e23          	sw	s0,60(sp)
   1005c:	04010413          	addi	s0,sp,64
   10060:	fe042623          	sw	zero,-20(s0)
   10064:	fe042423          	sw	zero,-24(s0)
   10068:	fe042223          	sw	zero,-28(s0)
   1006c:	fe042023          	sw	zero,-32(s0)
   10070:	fe042783          	lw	a5,-32(s0)
   10074:	00479793          	slli	a5,a5,0x4
   10078:	fcf42e23          	sw	a5,-36(s0)
   1007c:	fec42783          	lw	a5,-20(s0)
   10080:	00579793          	slli	a5,a5,0x5
   10084:	fcf42c23          	sw	a5,-40(s0)
   10088:	fe842783          	lw	a5,-24(s0)
   1008c:	00679793          	slli	a5,a5,0x6
   10090:	fcf42a23          	sw	a5,-44(s0)
   10094:	fe442783          	lw	a5,-28(s0)
   10098:	00779793          	slli	a5,a5,0x7
   1009c:	fcf42823          	sw	a5,-48(s0)
   100a0:	fc042623          	sw	zero,-52(s0)
   100a4:	001f7793          	andi	a5,t5,1
   100a8:	fcf42623          	sw	a5,-52(s0)
   100ac:	fc042423          	sw	zero,-56(s0)
   100b0:	002f7793          	andi	a5,t5,2
   100b4:	fcf42423          	sw	a5,-56(s0)
   100b8:	00100793          	li	a5,1
   100bc:	fcf42223          	sw	a5,-60(s0)
   100c0:	004f7793          	andi	a5,t5,4
   100c4:	fcf42223          	sw	a5,-60(s0)
   100c8:	fcc42783          	lw	a5,-52(s0)
   100cc:	08079263          	bnez	a5,10150 <main+0xfc>
   100d0:	fe042023          	sw	zero,-32(s0)
   100d4:	fc842783          	lw	a5,-56(s0)
   100d8:	02079063          	bnez	a5,100f8 <main+0xa4>
   100dc:	fc442783          	lw	a5,-60(s0)
   100e0:	00078c63          	beqz	a5,100f8 <main+0xa4>
   100e4:	00100793          	li	a5,1
   100e8:	fef42623          	sw	a5,-20(s0)
   100ec:	fe042423          	sw	zero,-24(s0)
   100f0:	fe042223          	sw	zero,-28(s0)
   100f4:	0700006f          	j	10164 <main+0x110>
   100f8:	fc442783          	lw	a5,-60(s0)
   100fc:	02079063          	bnez	a5,1011c <main+0xc8>
   10100:	fc842783          	lw	a5,-56(s0)
   10104:	00078c63          	beqz	a5,1011c <main+0xc8>
   10108:	00100793          	li	a5,1
   1010c:	fef42423          	sw	a5,-24(s0)
   10110:	fe042623          	sw	zero,-20(s0)
   10114:	fe042223          	sw	zero,-28(s0)
   10118:	04c0006f          	j	10164 <main+0x110>
   1011c:	fc442783          	lw	a5,-60(s0)
   10120:	02079063          	bnez	a5,10140 <main+0xec>
   10124:	fc842783          	lw	a5,-56(s0)
   10128:	00079c63          	bnez	a5,10140 <main+0xec>
   1012c:	00100793          	li	a5,1
   10130:	fef42223          	sw	a5,-28(s0)
   10134:	fe042423          	sw	zero,-24(s0)
   10138:	fe042623          	sw	zero,-20(s0)
   1013c:	0280006f          	j	10164 <main+0x110>
   10140:	fe042223          	sw	zero,-28(s0)
   10144:	fe042423          	sw	zero,-24(s0)
   10148:	fe042623          	sw	zero,-20(s0)
   1014c:	0180006f          	j	10164 <main+0x110>
   10150:	00100793          	li	a5,1
   10154:	fef42023          	sw	a5,-32(s0)
   10158:	fe042223          	sw	zero,-28(s0)
   1015c:	fe042423          	sw	zero,-24(s0)
   10160:	fe042623          	sw	zero,-20(s0)
   10164:	fdc42783          	lw	a5,-36(s0)
   10168:	00ff6f33          	or	t5,t5,a5
   1016c:	fd842783          	lw	a5,-40(s0)
   10170:	00ff6f33          	or	t5,t5,a5
   10174:	fd442783          	lw	a5,-44(s0)
   10178:	00ff6f33          	or	t5,t5,a5
   1017c:	fd042783          	lw	a5,-48(s0)
   10180:	00ff6f33          	or	t5,t5,a5
   10184:	00000793          	li	a5,0
   10188:	00078513          	mv	a0,a5
   1018c:	03c12403          	lw	s0,60(sp)
   10190:	04010113          	addi	sp,sp,64
   10194:	00008067          	ret
```

**Number of unique instructions**


Number of different instructions: 12


List of unique instructions:


beqz


sw


lw


li


j


andi


ret


slli


or


addi


bnez


mv

   

   


# Acknowledgement

* Kunal Ghosh, VSD Corp. Pvt. Ltd.
* Mayank Kabra

# Reference

https://electronicslovers.com/


https://github.com/SakethGajawada/RISCV-GNU







