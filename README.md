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
		"or x30, x30,%1 \n\t"
		:"=r"(led_value_2));
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
riscv64-unknown-elf-gcc -c -mabi=ilp32 -march=rv32im -o smart_bin.o smart_bin.c
riscv64-unknown-elf-objdump -d smart_bin.o > smart_bin_assembly.txt 

```


```









```







