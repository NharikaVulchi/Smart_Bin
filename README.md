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
/home/niharika/Downloads/riscv32-toolchain/bin/riscv32-unknown-elf-gcc -mabi=ilp32 -march=rv32im -ffreestanding -nostdlib -o smart_bin_n.o smart_bin.c
/home/niharika/Downloads/riscv32-toolchain/bin/riscv32-unknown-elf-objdump -d -r smart_bin_n.o > smart_bin_assembly_2.txt
```


```

smart_bin_n.o:     file format elf32-littleriscv


Disassembly of section .text:

00010094 <main>:
   10094:	ff010113          	add	sp,sp,-16
   10098:	00112623          	sw	ra,12(sp)
   1009c:	00812423          	sw	s0,8(sp)
   100a0:	01010413          	add	s0,sp,16
   100a4:	000117b7          	lui	a5,0x11
   100a8:	2407a023          	sw	zero,576(a5) # 11240 <__DATA_BEGIN__>
   100ac:	000f0713          	mv	a4,t5
   100b0:	000117b7          	lui	a5,0x11
   100b4:	24e7a023          	sw	a4,576(a5) # 11240 <__DATA_BEGIN__>
   100b8:	8001a423          	sw	zero,-2040(gp) # 11248 <mois_sen>
   100bc:	000f0713          	mv	a4,t5
   100c0:	80e1a423          	sw	a4,-2040(gp) # 11248 <mois_sen>
   100c4:	000117b7          	lui	a5,0x11
   100c8:	00100713          	li	a4,1
   100cc:	24e7a223          	sw	a4,580(a5) # 11244 <metal_sen>
   100d0:	004f0713          	add	a4,t5,4
   100d4:	000117b7          	lui	a5,0x11
   100d8:	24e7a223          	sw	a4,580(a5) # 11244 <metal_sen>
   100dc:	000117b7          	lui	a5,0x11
   100e0:	2407a783          	lw	a5,576(a5) # 11240 <__DATA_BEGIN__>
   100e4:	00078513          	mv	a0,a5
   100e8:	094000ef          	jal	1017c <start>
   100ec:	ff1ff06f          	j	100dc <main+0x48>

000100f0 <waste_detector>:
   100f0:	fd010113          	add	sp,sp,-48
   100f4:	02812623          	sw	s0,44(sp)
   100f8:	03010413          	add	s0,sp,48
   100fc:	fea42623          	sw	a0,-20(s0)
   10100:	feb42423          	sw	a1,-24(s0)
   10104:	fec42223          	sw	a2,-28(s0)
   10108:	fed42023          	sw	a3,-32(s0)
   1010c:	fce42e23          	sw	a4,-36(s0)
   10110:	fec42783          	lw	a5,-20(s0)
   10114:	02079063          	bnez	a5,10134 <waste_detector+0x44>
   10118:	fe842783          	lw	a5,-24(s0)
   1011c:	00078c63          	beqz	a5,10134 <waste_detector+0x44>
   10120:	00100793          	li	a5,1
   10124:	fef42223          	sw	a5,-28(s0)
   10128:	fe042023          	sw	zero,-32(s0)
   1012c:	fc042e23          	sw	zero,-36(s0)
   10130:	03c0006f          	j	1016c <waste_detector+0x7c>
   10134:	fe842783          	lw	a5,-24(s0)
   10138:	02079063          	bnez	a5,10158 <waste_detector+0x68>
   1013c:	fec42783          	lw	a5,-20(s0)
   10140:	00078c63          	beqz	a5,10158 <waste_detector+0x68>
   10144:	00100793          	li	a5,1
   10148:	fef42023          	sw	a5,-32(s0)
   1014c:	fe042223          	sw	zero,-28(s0)
   10150:	fc042e23          	sw	zero,-36(s0)
   10154:	0180006f          	j	1016c <waste_detector+0x7c>
   10158:	00100793          	li	a5,1
   1015c:	fcf42e23          	sw	a5,-36(s0)
   10160:	fe042023          	sw	zero,-32(s0)
   10164:	fe042223          	sw	zero,-28(s0)
   10168:	00000013          	nop
   1016c:	00000013          	nop
   10170:	02c12403          	lw	s0,44(sp)
   10174:	03010113          	add	sp,sp,48
   10178:	00008067          	ret

0001017c <start>:
   1017c:	fc010113          	add	sp,sp,-64
   10180:	02112e23          	sw	ra,60(sp)
   10184:	02812c23          	sw	s0,56(sp)
   10188:	04010413          	add	s0,sp,64
   1018c:	fca42623          	sw	a0,-52(s0)
   10190:	fcc42783          	lw	a5,-52(s0)
   10194:	06079e63          	bnez	a5,10210 <start+0x94>
   10198:	8001ac23          	sw	zero,-2024(gp) # 11258 <LED_value>
   1019c:	8181a783          	lw	a5,-2024(gp) # 11258 <LED_value>
   101a0:	00479793          	sll	a5,a5,0x4
   101a4:	fef42423          	sw	a5,-24(s0)
   101a8:	fe842783          	lw	a5,-24(s0)
   101ac:	00ff6f33          	or	t5,t5,a5
   101b0:	8081a503          	lw	a0,-2040(gp) # 11248 <mois_sen>
   101b4:	000117b7          	lui	a5,0x11
   101b8:	2447a583          	lw	a1,580(a5) # 11244 <metal_sen>
   101bc:	80c1a603          	lw	a2,-2036(gp) # 1124c <mm>
   101c0:	8101a683          	lw	a3,-2032(gp) # 11250 <mw>
   101c4:	8141a783          	lw	a5,-2028(gp) # 11254 <md>
   101c8:	00078713          	mv	a4,a5
   101cc:	f25ff0ef          	jal	100f0 <waste_detector>
   101d0:	80c1a783          	lw	a5,-2036(gp) # 1124c <mm>
   101d4:	00579793          	sll	a5,a5,0x5
   101d8:	fef42223          	sw	a5,-28(s0)
   101dc:	8101a783          	lw	a5,-2032(gp) # 11250 <mw>
   101e0:	00679793          	sll	a5,a5,0x6
   101e4:	fef42023          	sw	a5,-32(s0)
   101e8:	8141a783          	lw	a5,-2028(gp) # 11254 <md>
   101ec:	00779793          	sll	a5,a5,0x7
   101f0:	fcf42e23          	sw	a5,-36(s0)
   101f4:	fe442783          	lw	a5,-28(s0)
   101f8:	00ff6f33          	or	t5,t5,a5
   101fc:	fe042783          	lw	a5,-32(s0)
   10200:	00ff6f33          	or	t5,t5,a5
   10204:	fdc42783          	lw	a5,-36(s0)
   10208:	00ff6f33          	or	t5,t5,a5
   1020c:	0200006f          	j	1022c <start+0xb0>
   10210:	00100713          	li	a4,1
   10214:	80e1ac23          	sw	a4,-2024(gp) # 11258 <LED_value>
   10218:	8181a783          	lw	a5,-2024(gp) # 11258 <LED_value>
   1021c:	00479793          	sll	a5,a5,0x4
   10220:	fef42623          	sw	a5,-20(s0)
   10224:	fec42783          	lw	a5,-20(s0)
   10228:	00ff6f33          	or	t5,t5,a5
   1022c:	00000013          	nop
   10230:	03c12083          	lw	ra,60(sp)
   10234:	03812403          	lw	s0,56(sp)
   10238:	04010113          	add	sp,sp,64
   1023c:	00008067          	ret


```

**Number of unique instructions**

Number of different instructions: 14


```
List of unique instructions:


add

ret

or

li

mv

sll

sw

beqz

nop

j

bnez

jal

lui

lw
```

# Functional Simulation Results

In the below image we can see that the contents of **ID_instructions** are incrementing similar to the assembly code, which resembles the increase in the PC or our execution.


![Screenshot from 2023-10-18 19-58-43](https://github.com/NharikaVulchi/Smart_Bin/assets/83216569/3b0d5697-bc32-4e55-b6b6-d3cc00885c33)


The code involves use of 3 input_gpio_pins reading the values from the IR,moisture and metal proximity sensor  and 4 output_gpio_pins writing the values to the LED and 3 output motor drivers


# Acknowledgement

* Kunal Ghosh, VSD Corp. Pvt. Ltd.
* Mayank Kabra

# Reference

https://electronicslovers.com/


https://github.com/SakethGajawada/RISCV-GNU







