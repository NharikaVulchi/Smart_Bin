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

# Flowchart

The flowchart and block diagram for the proposed solution are shown below:

![Untitled Workspace(4)](https://github.com/NharikaVulchi/Smart_Bin/assets/83216569/b7c2eba2-821c-4993-b802-55bfd7e133c6)

![Untitled Workspace(3)](https://github.com/NharikaVulchi/Smart_Bin/assets/83216569/205e1340-7cc1-4e82-b4a4-93d1a76bffff)



# C code

We propose to build this solution using a RISC-V ASIC. The corresponding C code is shown below:

```
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
		led_value_2 = LED_value * 16;
		asm(
		"or x30, x30,%0 \n\t"
		:"=r"(led_value_2));
		waste_detector(mois_sen,metal_sen,mm,mw,md);
		mm_2= mm * 32;
		mw_2 = mw * 64;
		md_2 = md *128;
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
		led_value_2 = LED_value * 16;
		asm(
		"or x30, x30,%0 \n\t"
		:"=r"(led_value_2));
	}
	
	
	
}
int main(){
    
    ir=0; //ir=digital_read(ir_pin_number) 
    asm(
    "addi %0 , x30, 0\n\t"
    :"=r"(ir));
    mois_sen=0; //mois_sen=digital_read(mois_sen_pin_number)
    asm(
    "addi %0 , x30, 0\n\t"
    :"=r"(mois_sen));
    metal_sen =1; //metal_sen=digital_read(metal_sen_pin_number)
    asm(
    "addi %0 , x30, 4\n\t"
    :"=r"(metal_sen));
    while(1){
        start(ir);
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

# Assembly code


we run the RISC-V GNU using:

```
/home/niharika/Downloads/riscv32-toolchain/bin/riscv32-unknown-elf-gcc -c -mabi=ilp32 -march=rv32im -ffreestanding -o smart_bin_n.o smart_bin.c
/home/niharika/Downloads/riscv32-toolchain/bin/riscv32-unknown-elf-objdump -d smart_bin_n.o > smart_bin_assembly_new.txt
```


```

smart_bin_n.o:     file format elf32-littleriscv


Disassembly of section .text:

00000000 <waste_detector>:
   0:	fd010113          	add	sp,sp,-48
   4:	02812623          	sw	s0,44(sp)
   8:	03010413          	add	s0,sp,48
   c:	fea42623          	sw	a0,-20(s0)
  10:	feb42423          	sw	a1,-24(s0)
  14:	fec42223          	sw	a2,-28(s0)
  18:	fed42023          	sw	a3,-32(s0)
  1c:	fce42e23          	sw	a4,-36(s0)
  20:	fec42783          	lw	a5,-20(s0)
  24:	02079063          	bnez	a5,44 <.L2>
  28:	fe842783          	lw	a5,-24(s0)
  2c:	00078c63          	beqz	a5,44 <.L2>
  30:	00100793          	li	a5,1
  34:	fef42223          	sw	a5,-28(s0)
  38:	fe042023          	sw	zero,-32(s0)
  3c:	fc042e23          	sw	zero,-36(s0)
  40:	03c0006f          	j	7c <.L3>

00000044 <.L2>:
  44:	fe842783          	lw	a5,-24(s0)
  48:	02079063          	bnez	a5,68 <.L4>
  4c:	fec42783          	lw	a5,-20(s0)
  50:	00078c63          	beqz	a5,68 <.L4>
  54:	00100793          	li	a5,1
  58:	fef42023          	sw	a5,-32(s0)
  5c:	fe042223          	sw	zero,-28(s0)
  60:	fc042e23          	sw	zero,-36(s0)
  64:	0180006f          	j	7c <.L3>

00000068 <.L4>:
  68:	00100793          	li	a5,1
  6c:	fcf42e23          	sw	a5,-36(s0)
  70:	fe042023          	sw	zero,-32(s0)
  74:	fe042223          	sw	zero,-28(s0)
  78:	00000013          	nop

0000007c <.L3>:
  7c:	00000013          	nop
  80:	02c12403          	lw	s0,44(sp)
  84:	03010113          	add	sp,sp,48
  88:	00008067          	ret

0000008c <start>:
  8c:	fc010113          	add	sp,sp,-64
  90:	02112e23          	sw	ra,60(sp)
  94:	02812c23          	sw	s0,56(sp)
  98:	04010413          	add	s0,sp,64
  9c:	fca42623          	sw	a0,-52(s0)
  a0:	fcc42783          	lw	a5,-52(s0)
  a4:	0a079a63          	bnez	a5,158 <.L6>
  a8:	000007b7          	lui	a5,0x0
  ac:	00078513          	mv	a0,a5
  b0:	00000097          	auipc	ra,0x0
  b4:	000080e7          	jalr	ra # b0 <start+0x24>
  b8:	000007b7          	lui	a5,0x0
  bc:	0007a023          	sw	zero,0(a5) # 0 <waste_detector>
  c0:	000007b7          	lui	a5,0x0
  c4:	0007a783          	lw	a5,0(a5) # 0 <waste_detector>
  c8:	00479793          	sll	a5,a5,0x4
  cc:	fef42423          	sw	a5,-24(s0)
  d0:	00ff6f33          	or	t5,t5,a5
  d4:	fef42423          	sw	a5,-24(s0)
  d8:	000007b7          	lui	a5,0x0
  dc:	0007a503          	lw	a0,0(a5) # 0 <waste_detector>
  e0:	000007b7          	lui	a5,0x0
  e4:	0007a583          	lw	a1,0(a5) # 0 <waste_detector>
  e8:	000007b7          	lui	a5,0x0
  ec:	0007a603          	lw	a2,0(a5) # 0 <waste_detector>
  f0:	000007b7          	lui	a5,0x0
  f4:	0007a683          	lw	a3,0(a5) # 0 <waste_detector>
  f8:	000007b7          	lui	a5,0x0
  fc:	0007a783          	lw	a5,0(a5) # 0 <waste_detector>
 100:	00078713          	mv	a4,a5
 104:	00000097          	auipc	ra,0x0
 108:	000080e7          	jalr	ra # 104 <start+0x78>
 10c:	000007b7          	lui	a5,0x0
 110:	0007a783          	lw	a5,0(a5) # 0 <waste_detector>
 114:	00579793          	sll	a5,a5,0x5
 118:	fef42223          	sw	a5,-28(s0)
 11c:	000007b7          	lui	a5,0x0
 120:	0007a783          	lw	a5,0(a5) # 0 <waste_detector>
 124:	00679793          	sll	a5,a5,0x6
 128:	fef42023          	sw	a5,-32(s0)
 12c:	000007b7          	lui	a5,0x0
 130:	0007a783          	lw	a5,0(a5) # 0 <waste_detector>
 134:	00779793          	sll	a5,a5,0x7
 138:	fcf42e23          	sw	a5,-36(s0)
 13c:	00df6f33          	or	t5,t5,a3
 140:	00ef6f33          	or	t5,t5,a4
 144:	00ff6f33          	or	t5,t5,a5
 148:	fed42223          	sw	a3,-28(s0)
 14c:	fee42023          	sw	a4,-32(s0)
 150:	fcf42e23          	sw	a5,-36(s0)
 154:	0280006f          	j	17c <.L8>

00000158 <.L6>:
 158:	000007b7          	lui	a5,0x0
 15c:	00100713          	li	a4,1
 160:	00e7a023          	sw	a4,0(a5) # 0 <waste_detector>
 164:	000007b7          	lui	a5,0x0
 168:	0007a783          	lw	a5,0(a5) # 0 <waste_detector>
 16c:	00479793          	sll	a5,a5,0x4
 170:	fef42623          	sw	a5,-20(s0)
 174:	00ff6f33          	or	t5,t5,a5
 178:	fef42623          	sw	a5,-20(s0)

0000017c <.L8>:
 17c:	00000013          	nop
 180:	03c12083          	lw	ra,60(sp)
 184:	03812403          	lw	s0,56(sp)
 188:	04010113          	add	sp,sp,64
 18c:	00008067          	ret

00000190 <main>:
 190:	ff010113          	add	sp,sp,-16
 194:	00112623          	sw	ra,12(sp)
 198:	00812423          	sw	s0,8(sp)
 19c:	01010413          	add	s0,sp,16
 1a0:	000007b7          	lui	a5,0x0
 1a4:	0007a023          	sw	zero,0(a5) # 0 <waste_detector>
 1a8:	000f7713          	and	a4,t5,0
 1ac:	000007b7          	lui	a5,0x0
 1b0:	00e7a023          	sw	a4,0(a5) # 0 <waste_detector>
 1b4:	000007b7          	lui	a5,0x0
 1b8:	0007a023          	sw	zero,0(a5) # 0 <waste_detector>
 1bc:	000f7713          	and	a4,t5,0
 1c0:	000007b7          	lui	a5,0x0
 1c4:	00e7a023          	sw	a4,0(a5) # 0 <waste_detector>
 1c8:	000007b7          	lui	a5,0x0
 1cc:	00100713          	li	a4,1
 1d0:	00e7a023          	sw	a4,0(a5) # 0 <waste_detector>
 1d4:	004f7713          	and	a4,t5,4
 1d8:	000007b7          	lui	a5,0x0
 1dc:	00e7a023          	sw	a4,0(a5) # 0 <waste_detector>

000001e0 <.L10>:
 1e0:	000007b7          	lui	a5,0x0
 1e4:	0007a783          	lw	a5,0(a5) # 0 <waste_detector>
 1e8:	00078513          	mv	a0,a5
 1ec:	00000097          	auipc	ra,0x0
 1f0:	000080e7          	jalr	ra # 1ec <.L10+0xc>
 1f4:	fedff06f          	j	1e0 <.L10>

```

**Number of unique instructions**

![image](https://github.com/NharikaVulchi/Smart_Bin/assets/83216569/f09bdd4f-b939-4fde-b093-f4a99ebe2c54)

# Acknowledgement

* Kunal Ghosh, VSD Corp. Pvt. Ltd.
* Mayank Kabra

# Reference

https://electronicslovers.com/
https://github.com/SakethGajawada/RISCV-GNU







