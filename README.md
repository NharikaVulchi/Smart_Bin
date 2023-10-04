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
		waste_detector(mois_sen,metal_sen,mm,mw,md);
		// digital_write(mm_pin_num,mm);
		// digital_write(mw_pin_num,mw);
		// digital_write(md_pin_num,md);				
		

	}
	else // we turn on the LED and donot open the lids
	{
		LED_value=1; //digital_write(LED_pin_number,1)
	}
	
	
	
}
int main(){
    
    ir=0; //ir=digital_read(ir_pin_number)
    mois_sen=0; //mois_sen=digital_read(mois_sen_pin_number)
    metal_sen =1; //metal_sen=digital_read(metal_sen_pin_number)
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
riscv64-unknown-elf-gcc -o smart_bin.o smart_bin.c 
riscv64-unknown-elf-objdump -d smart_bin.o > smart_bin_assembly.txt
```


```

smart_bin.o:     file format elf64-littleriscv


Disassembly of section .text:

00000000000100b0 <register_fini>:
   100b0:	ffff0797          	auipc	a5,0xffff0
   100b4:	f5078793          	addi	a5,a5,-176 # 0 <register_fini-0x100b0>
   100b8:	c791                	beqz	a5,100c4 <register_fini+0x14>
   100ba:	00000517          	auipc	a0,0x0
   100be:	1bc50513          	addi	a0,a0,444 # 10276 <__libc_fini_array>
   100c2:	a269                	j	1024c <atexit>
   100c4:	8082                	ret

00000000000100c6 <_start>:
   100c6:	00004197          	auipc	gp,0x4
   100ca:	f3a18193          	addi	gp,gp,-198 # 14000 <__global_pointer$>
   100ce:	76018513          	addi	a0,gp,1888 # 14760 <_edata>
   100d2:	00004617          	auipc	a2,0x4
   100d6:	72e60613          	addi	a2,a2,1838 # 14800 <__BSS_END__>
   100da:	8e09                	sub	a2,a2,a0
   100dc:	4581                	li	a1,0
   100de:	23a000ef          	jal	ra,10318 <memset>
   100e2:	00000517          	auipc	a0,0x0
   100e6:	19450513          	addi	a0,a0,404 # 10276 <__libc_fini_array>
   100ea:	162000ef          	jal	ra,1024c <atexit>
   100ee:	1c0000ef          	jal	ra,102ae <__libc_init_array>
   100f2:	4502                	lw	a0,0(sp)
   100f4:	002c                	addi	a1,sp,8
   100f6:	4601                	li	a2,0
   100f8:	130000ef          	jal	ra,10228 <main>
   100fc:	aaa9                	j	10256 <exit>

00000000000100fe <__do_global_dtors_aux>:
   100fe:	7801c783          	lbu	a5,1920(gp) # 14780 <completed.5470>
   10102:	eb95                	bnez	a5,10136 <__do_global_dtors_aux+0x38>
   10104:	ffff0797          	auipc	a5,0xffff0
   10108:	efc78793          	addi	a5,a5,-260 # 0 <register_fini-0x100b0>
   1010c:	c38d                	beqz	a5,1012e <__do_global_dtors_aux+0x30>
   1010e:	1141                	addi	sp,sp,-16
   10110:	00003517          	auipc	a0,0x3
   10114:	69850513          	addi	a0,a0,1688 # 137a8 <__FRAME_END__>
   10118:	e406                	sd	ra,8(sp)
   1011a:	00000097          	auipc	ra,0x0
   1011e:	000000e7          	jalr	zero # 0 <register_fini-0x100b0>
   10122:	60a2                	ld	ra,8(sp)
   10124:	4785                	li	a5,1
   10126:	78f18023          	sb	a5,1920(gp) # 14780 <completed.5470>
   1012a:	0141                	addi	sp,sp,16
   1012c:	8082                	ret
   1012e:	4785                	li	a5,1
   10130:	78f18023          	sb	a5,1920(gp) # 14780 <completed.5470>
   10134:	8082                	ret
   10136:	8082                	ret

0000000000010138 <frame_dummy>:
   10138:	ffff0797          	auipc	a5,0xffff0
   1013c:	ec878793          	addi	a5,a5,-312 # 0 <register_fini-0x100b0>
   10140:	cb99                	beqz	a5,10156 <frame_dummy+0x1e>
   10142:	78818593          	addi	a1,gp,1928 # 14788 <object.5475>
   10146:	00003517          	auipc	a0,0x3
   1014a:	66250513          	addi	a0,a0,1634 # 137a8 <__FRAME_END__>
   1014e:	00000317          	auipc	t1,0x0
   10152:	00000067          	jr	zero # 0 <register_fini-0x100b0>
   10156:	8082                	ret

0000000000010158 <waste_detector>:
   10158:	7179                	addi	sp,sp,-48
   1015a:	f422                	sd	s0,40(sp)
   1015c:	1800                	addi	s0,sp,48
   1015e:	87aa                	mv	a5,a0
   10160:	fef42623          	sw	a5,-20(s0)
   10164:	87ae                	mv	a5,a1
   10166:	fef42423          	sw	a5,-24(s0)
   1016a:	87b2                	mv	a5,a2
   1016c:	fef42223          	sw	a5,-28(s0)
   10170:	87b6                	mv	a5,a3
   10172:	fef42023          	sw	a5,-32(s0)
   10176:	87ba                	mv	a5,a4
   10178:	fcf42e23          	sw	a5,-36(s0)
   1017c:	fec42783          	lw	a5,-20(s0)
   10180:	2781                	sext.w	a5,a5
   10182:	ef89                	bnez	a5,1019c <waste_detector+0x44>
   10184:	fe842783          	lw	a5,-24(s0)
   10188:	2781                	sext.w	a5,a5
   1018a:	cb89                	beqz	a5,1019c <waste_detector+0x44>
   1018c:	4785                	li	a5,1
   1018e:	fef42223          	sw	a5,-28(s0)
   10192:	fe042023          	sw	zero,-32(s0)
   10196:	fc042e23          	sw	zero,-36(s0)
   1019a:	a805                	j	101ca <waste_detector+0x72>
   1019c:	fe842783          	lw	a5,-24(s0)
   101a0:	2781                	sext.w	a5,a5
   101a2:	ef89                	bnez	a5,101bc <waste_detector+0x64>
   101a4:	fec42783          	lw	a5,-20(s0)
   101a8:	2781                	sext.w	a5,a5
   101aa:	cb89                	beqz	a5,101bc <waste_detector+0x64>
   101ac:	4785                	li	a5,1
   101ae:	fef42023          	sw	a5,-32(s0)
   101b2:	fe042223          	sw	zero,-28(s0)
   101b6:	fc042e23          	sw	zero,-36(s0)
   101ba:	a801                	j	101ca <waste_detector+0x72>
   101bc:	4785                	li	a5,1
   101be:	fcf42e23          	sw	a5,-36(s0)
   101c2:	fe042023          	sw	zero,-32(s0)
   101c6:	fe042223          	sw	zero,-28(s0)
   101ca:	0001                	nop
   101cc:	7422                	ld	s0,40(sp)
   101ce:	6145                	addi	sp,sp,48
   101d0:	8082                	ret

00000000000101d2 <start>:
   101d2:	1101                	addi	sp,sp,-32
   101d4:	ec06                	sd	ra,24(sp)
   101d6:	e822                	sd	s0,16(sp)
   101d8:	1000                	addi	s0,sp,32
   101da:	87aa                	mv	a5,a0
   101dc:	fef42623          	sw	a5,-20(s0)
   101e0:	fec42783          	lw	a5,-20(s0)
   101e4:	2781                	sext.w	a5,a5
   101e6:	eb85                	bnez	a5,10216 <start+0x44>
   101e8:	67c9                	lui	a5,0x12
   101ea:	79078513          	addi	a0,a5,1936 # 12790 <__errno+0xa>
   101ee:	254000ef          	jal	ra,10442 <puts>
   101f2:	67d1                	lui	a5,0x14
   101f4:	7e07aa23          	sw	zero,2036(a5) # 147f4 <LED_value>
   101f8:	7ec1a503          	lw	a0,2028(gp) # 147ec <mois_sen>
   101fc:	67d1                	lui	a5,0x14
   101fe:	7f87a583          	lw	a1,2040(a5) # 147f8 <metal_sen>
   10202:	7e01a603          	lw	a2,2016(gp) # 147e0 <mm>
   10206:	7e41a683          	lw	a3,2020(gp) # 147e4 <mw>
   1020a:	7e81a783          	lw	a5,2024(gp) # 147e8 <md>
   1020e:	873e                	mv	a4,a5
   10210:	f49ff0ef          	jal	ra,10158 <waste_detector>
   10214:	a029                	j	1021e <start+0x4c>
   10216:	67d1                	lui	a5,0x14
   10218:	4705                	li	a4,1
   1021a:	7ee7aa23          	sw	a4,2036(a5) # 147f4 <LED_value>
   1021e:	0001                	nop
   10220:	60e2                	ld	ra,24(sp)
   10222:	6442                	ld	s0,16(sp)
   10224:	6105                	addi	sp,sp,32
   10226:	8082                	ret

0000000000010228 <main>:
   10228:	1141                	addi	sp,sp,-16
   1022a:	e406                	sd	ra,8(sp)
   1022c:	e022                	sd	s0,0(sp)
   1022e:	0800                	addi	s0,sp,16
   10230:	7e01a823          	sw	zero,2032(gp) # 147f0 <ir>
   10234:	7e01a623          	sw	zero,2028(gp) # 147ec <mois_sen>
   10238:	67d1                	lui	a5,0x14
   1023a:	4705                	li	a4,1
   1023c:	7ee7ac23          	sw	a4,2040(a5) # 147f8 <metal_sen>
   10240:	7f01a783          	lw	a5,2032(gp) # 147f0 <ir>
   10244:	853e                	mv	a0,a5
   10246:	f8dff0ef          	jal	ra,101d2 <start>
   1024a:	bfdd                	j	10240 <main+0x18>

000000000001024c <atexit>:
   1024c:	85aa                	mv	a1,a0
   1024e:	4681                	li	a3,0
   10250:	4601                	li	a2,0
   10252:	4501                	li	a0,0
   10254:	ac41                	j	104e4 <__register_exitproc>

0000000000010256 <exit>:
   10256:	1141                	addi	sp,sp,-16
   10258:	4581                	li	a1,0
   1025a:	e022                	sd	s0,0(sp)
   1025c:	e406                	sd	ra,8(sp)
   1025e:	842a                	mv	s0,a0
   10260:	2fc000ef          	jal	ra,1055c <__call_exitprocs>
   10264:	73818793          	addi	a5,gp,1848 # 14738 <_global_impure_ptr>
   10268:	6388                	ld	a0,0(a5)
   1026a:	6d3c                	ld	a5,88(a0)
   1026c:	c391                	beqz	a5,10270 <exit+0x1a>
   1026e:	9782                	jalr	a5
   10270:	8522                	mv	a0,s0
   10272:	320020ef          	jal	ra,12592 <_exit>

0000000000010276 <__libc_fini_array>:
   10276:	1101                	addi	sp,sp,-32
   10278:	e822                	sd	s0,16(sp)
   1027a:	00003797          	auipc	a5,0x3
   1027e:	54e78793          	addi	a5,a5,1358 # 137c8 <__fini_array_end>
   10282:	00003417          	auipc	s0,0x3
   10286:	53e40413          	addi	s0,s0,1342 # 137c0 <__init_array_end>
   1028a:	8f81                	sub	a5,a5,s0
   1028c:	e426                	sd	s1,8(sp)
   1028e:	ec06                	sd	ra,24(sp)
   10290:	4037d493          	srai	s1,a5,0x3
   10294:	c881                	beqz	s1,102a4 <__libc_fini_array+0x2e>
   10296:	17e1                	addi	a5,a5,-8
   10298:	943e                	add	s0,s0,a5
   1029a:	601c                	ld	a5,0(s0)
   1029c:	14fd                	addi	s1,s1,-1
   1029e:	1461                	addi	s0,s0,-8
   102a0:	9782                	jalr	a5
   102a2:	fce5                	bnez	s1,1029a <__libc_fini_array+0x24>
   102a4:	60e2                	ld	ra,24(sp)
   102a6:	6442                	ld	s0,16(sp)
   102a8:	64a2                	ld	s1,8(sp)
   102aa:	6105                	addi	sp,sp,32
   102ac:	8082                	ret

00000000000102ae <__libc_init_array>:
   102ae:	1101                	addi	sp,sp,-32
   102b0:	e822                	sd	s0,16(sp)
   102b2:	e04a                	sd	s2,0(sp)
   102b4:	00003417          	auipc	s0,0x3
   102b8:	4f840413          	addi	s0,s0,1272 # 137ac <__preinit_array_end>
   102bc:	00003917          	auipc	s2,0x3
   102c0:	4f090913          	addi	s2,s2,1264 # 137ac <__preinit_array_end>
   102c4:	40890933          	sub	s2,s2,s0
   102c8:	ec06                	sd	ra,24(sp)
   102ca:	e426                	sd	s1,8(sp)
   102cc:	40395913          	srai	s2,s2,0x3
   102d0:	00090963          	beqz	s2,102e2 <__libc_init_array+0x34>
   102d4:	4481                	li	s1,0
   102d6:	601c                	ld	a5,0(s0)
   102d8:	0485                	addi	s1,s1,1
   102da:	0421                	addi	s0,s0,8
   102dc:	9782                	jalr	a5
   102de:	fe991ce3          	bne	s2,s1,102d6 <__libc_init_array+0x28>
   102e2:	00003417          	auipc	s0,0x3
   102e6:	4ce40413          	addi	s0,s0,1230 # 137b0 <__init_array_start>
   102ea:	00003917          	auipc	s2,0x3
   102ee:	4d690913          	addi	s2,s2,1238 # 137c0 <__init_array_end>
   102f2:	40890933          	sub	s2,s2,s0
   102f6:	40395913          	srai	s2,s2,0x3
   102fa:	00090963          	beqz	s2,1030c <__libc_init_array+0x5e>
   102fe:	4481                	li	s1,0
   10300:	601c                	ld	a5,0(s0)
   10302:	0485                	addi	s1,s1,1
   10304:	0421                	addi	s0,s0,8
   10306:	9782                	jalr	a5
   10308:	fe991ce3          	bne	s2,s1,10300 <__libc_init_array+0x52>
   1030c:	60e2                	ld	ra,24(sp)
   1030e:	6442                	ld	s0,16(sp)
   10310:	64a2                	ld	s1,8(sp)
   10312:	6902                	ld	s2,0(sp)
   10314:	6105                	addi	sp,sp,32
   10316:	8082                	ret

0000000000010318 <memset>:
   10318:	433d                	li	t1,15
   1031a:	872a                	mv	a4,a0
   1031c:	02c37163          	bgeu	t1,a2,1033e <memset+0x26>
   10320:	00f77793          	andi	a5,a4,15
   10324:	e3c1                	bnez	a5,103a4 <memset+0x8c>
   10326:	e1bd                	bnez	a1,1038c <memset+0x74>
   10328:	ff067693          	andi	a3,a2,-16
   1032c:	8a3d                	andi	a2,a2,15
   1032e:	96ba                	add	a3,a3,a4
   10330:	e30c                	sd	a1,0(a4)
   10332:	e70c                	sd	a1,8(a4)
   10334:	0741                	addi	a4,a4,16
   10336:	fed76de3          	bltu	a4,a3,10330 <memset+0x18>
   1033a:	e211                	bnez	a2,1033e <memset+0x26>
   1033c:	8082                	ret
   1033e:	40c306b3          	sub	a3,t1,a2
   10342:	068a                	slli	a3,a3,0x2
   10344:	00000297          	auipc	t0,0x0
   10348:	9696                	add	a3,a3,t0
   1034a:	00a68067          	jr	10(a3)
   1034e:	00b70723          	sb	a1,14(a4)
   10352:	00b706a3          	sb	a1,13(a4)
   10356:	00b70623          	sb	a1,12(a4)
   1035a:	00b705a3          	sb	a1,11(a4)
   1035e:	00b70523          	sb	a1,10(a4)
   10362:	00b704a3          	sb	a1,9(a4)
   10366:	00b70423          	sb	a1,8(a4)
   1036a:	00b703a3          	sb	a1,7(a4)
   1036e:	00b70323          	sb	a1,6(a4)
   10372:	00b702a3          	sb	a1,5(a4)
   10376:	00b70223          	sb	a1,4(a4)
   1037a:	00b701a3          	sb	a1,3(a4)
   1037e:	00b70123          	sb	a1,2(a4)
   10382:	00b700a3          	sb	a1,1(a4)
   10386:	00b70023          	sb	a1,0(a4)
   1038a:	8082                	ret
   1038c:	0ff5f593          	andi	a1,a1,255
   10390:	00859693          	slli	a3,a1,0x8
   10394:	8dd5                	or	a1,a1,a3
   10396:	01059693          	slli	a3,a1,0x10
   1039a:	8dd5                	or	a1,a1,a3
   1039c:	02059693          	slli	a3,a1,0x20
   103a0:	8dd5                	or	a1,a1,a3
   103a2:	b759                	j	10328 <memset+0x10>
   103a4:	00279693          	slli	a3,a5,0x2
   103a8:	00000297          	auipc	t0,0x0
   103ac:	9696                	add	a3,a3,t0
   103ae:	8286                	mv	t0,ra
   103b0:	fa2680e7          	jalr	-94(a3)
   103b4:	8096                	mv	ra,t0
   103b6:	17c1                	addi	a5,a5,-16
   103b8:	8f1d                	sub	a4,a4,a5
   103ba:	963e                	add	a2,a2,a5
   103bc:	f8c371e3          	bgeu	t1,a2,1033e <memset+0x26>
   103c0:	b79d                	j	10326 <memset+0xe>

00000000000103c2 <_puts_r>:
   103c2:	7159                	addi	sp,sp,-112
   103c4:	f0a2                	sd	s0,96(sp)
   103c6:	842a                	mv	s0,a0
   103c8:	852e                	mv	a0,a1
   103ca:	eca6                	sd	s1,88(sp)
   103cc:	f486                	sd	ra,104(sp)
   103ce:	84ae                	mv	s1,a1
   103d0:	07c000ef          	jal	ra,1044c <strlen>
   103d4:	00150713          	addi	a4,a0,1
   103d8:	00002697          	auipc	a3,0x2
   103dc:	3c868693          	addi	a3,a3,968 # 127a0 <__errno+0x1a>
   103e0:	f43a                	sd	a4,40(sp)
   103e2:	483c                	lw	a5,80(s0)
   103e4:	1818                	addi	a4,sp,48
   103e6:	e0b6                	sd	a3,64(sp)
   103e8:	ec3a                	sd	a4,24(sp)
   103ea:	4685                	li	a3,1
   103ec:	4709                	li	a4,2
   103ee:	f826                	sd	s1,48(sp)
   103f0:	fc2a                	sd	a0,56(sp)
   103f2:	e4b6                	sd	a3,72(sp)
   103f4:	d03a                	sw	a4,32(sp)
   103f6:	680c                	ld	a1,16(s0)
   103f8:	cf8d                	beqz	a5,10432 <_puts_r+0x70>
   103fa:	01059783          	lh	a5,16(a1)
   103fe:	03279713          	slli	a4,a5,0x32
   10402:	00074d63          	bltz	a4,1041c <_puts_r+0x5a>
   10406:	0ac5a703          	lw	a4,172(a1)
   1040a:	6689                	lui	a3,0x2
   1040c:	8fd5                	or	a5,a5,a3
   1040e:	76f9                	lui	a3,0xffffe
   10410:	16fd                	addi	a3,a3,-1
   10412:	8f75                	and	a4,a4,a3
   10414:	00f59823          	sh	a5,16(a1)
   10418:	0ae5a623          	sw	a4,172(a1)
   1041c:	0830                	addi	a2,sp,24
   1041e:	8522                	mv	a0,s0
   10420:	47c000ef          	jal	ra,1089c <__sfvwrite_r>
   10424:	ed09                	bnez	a0,1043e <_puts_r+0x7c>
   10426:	4529                	li	a0,10
   10428:	70a6                	ld	ra,104(sp)
   1042a:	7406                	ld	s0,96(sp)
   1042c:	64e6                	ld	s1,88(sp)
   1042e:	6165                	addi	sp,sp,112
   10430:	8082                	ret
   10432:	8522                	mv	a0,s0
   10434:	e42e                	sd	a1,8(sp)
   10436:	436000ef          	jal	ra,1086c <__sinit>
   1043a:	65a2                	ld	a1,8(sp)
   1043c:	bf7d                	j	103fa <_puts_r+0x38>
   1043e:	557d                	li	a0,-1
   10440:	b7e5                	j	10428 <_puts_r+0x66>

0000000000010442 <puts>:
   10442:	74818793          	addi	a5,gp,1864 # 14748 <_impure_ptr>
   10446:	85aa                	mv	a1,a0
   10448:	6388                	ld	a0,0(a5)
   1044a:	bfa5                	j	103c2 <_puts_r>

000000000001044c <strlen>:
   1044c:	00757793          	andi	a5,a0,7
   10450:	872a                	mv	a4,a0
   10452:	efa9                	bnez	a5,104ac <strlen+0x60>
   10454:	00004797          	auipc	a5,0x4
   10458:	2cc78793          	addi	a5,a5,716 # 14720 <__SDATA_BEGIN__>
   1045c:	6394                	ld	a3,0(a5)
   1045e:	55fd                	li	a1,-1
   10460:	0721                	addi	a4,a4,8
   10462:	ff873603          	ld	a2,-8(a4)
   10466:	00d677b3          	and	a5,a2,a3
   1046a:	97b6                	add	a5,a5,a3
   1046c:	8fd1                	or	a5,a5,a2
   1046e:	8fd5                	or	a5,a5,a3
   10470:	feb788e3          	beq	a5,a1,10460 <strlen+0x14>
   10474:	ff874783          	lbu	a5,-8(a4)
   10478:	40a706b3          	sub	a3,a4,a0
   1047c:	c7a9                	beqz	a5,104c6 <strlen+0x7a>
   1047e:	ff974783          	lbu	a5,-7(a4)
   10482:	cf9d                	beqz	a5,104c0 <strlen+0x74>
   10484:	ffa74783          	lbu	a5,-6(a4)
   10488:	c7a9                	beqz	a5,104d2 <strlen+0x86>
   1048a:	ffb74783          	lbu	a5,-5(a4)
   1048e:	cf9d                	beqz	a5,104cc <strlen+0x80>
   10490:	ffc74603          	lbu	a2,-4(a4)
   10494:	ffd74583          	lbu	a1,-3(a4)
   10498:	ffe74783          	lbu	a5,-2(a4)
   1049c:	ce15                	beqz	a2,104d8 <strlen+0x8c>
   1049e:	c1a1                	beqz	a1,104de <strlen+0x92>
   104a0:	00f03533          	snez	a0,a5
   104a4:	9536                	add	a0,a0,a3
   104a6:	1579                	addi	a0,a0,-2
   104a8:	8082                	ret
   104aa:	d6cd                	beqz	a3,10454 <strlen+0x8>
   104ac:	00074783          	lbu	a5,0(a4)
   104b0:	0705                	addi	a4,a4,1
   104b2:	00777693          	andi	a3,a4,7
   104b6:	fbf5                	bnez	a5,104aa <strlen+0x5e>
   104b8:	8f09                	sub	a4,a4,a0
   104ba:	fff70513          	addi	a0,a4,-1
   104be:	8082                	ret
   104c0:	ff968513          	addi	a0,a3,-7 # ffffffffffffdff9 <__BSS_END__+0xfffffffffffe97f9>
   104c4:	8082                	ret
   104c6:	ff868513          	addi	a0,a3,-8
   104ca:	8082                	ret
   104cc:	ffb68513          	addi	a0,a3,-5
   104d0:	8082                	ret
   104d2:	ffa68513          	addi	a0,a3,-6
   104d6:	8082                	ret
   104d8:	ffc68513          	addi	a0,a3,-4
   104dc:	8082                	ret
   104de:	ffd68513          	addi	a0,a3,-3
   104e2:	8082                	ret

00000000000104e4 <__register_exitproc>:
   104e4:	73818793          	addi	a5,gp,1848 # 14738 <_global_impure_ptr>
   104e8:	6398                	ld	a4,0(a5)
   104ea:	1f873783          	ld	a5,504(a4)
   104ee:	c3b1                	beqz	a5,10532 <__register_exitproc+0x4e>
   104f0:	4798                	lw	a4,8(a5)
   104f2:	487d                	li	a6,31
   104f4:	06e84263          	blt	a6,a4,10558 <__register_exitproc+0x74>
   104f8:	c505                	beqz	a0,10520 <__register_exitproc+0x3c>
   104fa:	00371813          	slli	a6,a4,0x3
   104fe:	983e                	add	a6,a6,a5
   10500:	10c83823          	sd	a2,272(a6)
   10504:	3107a883          	lw	a7,784(a5)
   10508:	4605                	li	a2,1
   1050a:	00e6163b          	sllw	a2,a2,a4
   1050e:	00c8e8b3          	or	a7,a7,a2
   10512:	3117a823          	sw	a7,784(a5)
   10516:	20d83823          	sd	a3,528(a6)
   1051a:	4689                	li	a3,2
   1051c:	02d50063          	beq	a0,a3,1053c <__register_exitproc+0x58>
   10520:	00270693          	addi	a3,a4,2
   10524:	068e                	slli	a3,a3,0x3
   10526:	2705                	addiw	a4,a4,1
   10528:	c798                	sw	a4,8(a5)
   1052a:	97b6                	add	a5,a5,a3
   1052c:	e38c                	sd	a1,0(a5)
   1052e:	4501                	li	a0,0
   10530:	8082                	ret
   10532:	20070793          	addi	a5,a4,512
   10536:	1ef73c23          	sd	a5,504(a4)
   1053a:	bf5d                	j	104f0 <__register_exitproc+0xc>
   1053c:	3147a683          	lw	a3,788(a5)
   10540:	4501                	li	a0,0
   10542:	8e55                	or	a2,a2,a3
   10544:	00270693          	addi	a3,a4,2
   10548:	068e                	slli	a3,a3,0x3
   1054a:	2705                	addiw	a4,a4,1
   1054c:	30c7aa23          	sw	a2,788(a5)
   10550:	c798                	sw	a4,8(a5)
   10552:	97b6                	add	a5,a5,a3
   10554:	e38c                	sd	a1,0(a5)
   10556:	8082                	ret
   10558:	557d                	li	a0,-1
   1055a:	8082                	ret

000000000001055c <__call_exitprocs>:
   1055c:	715d                	addi	sp,sp,-80
   1055e:	73818793          	addi	a5,gp,1848 # 14738 <_global_impure_ptr>
   10562:	e062                	sd	s8,0(sp)
   10564:	0007bc03          	ld	s8,0(a5)
   10568:	f44e                	sd	s3,40(sp)
   1056a:	f052                	sd	s4,32(sp)
   1056c:	ec56                	sd	s5,24(sp)
   1056e:	e85a                	sd	s6,16(sp)
   10570:	e486                	sd	ra,72(sp)
   10572:	e0a2                	sd	s0,64(sp)
   10574:	fc26                	sd	s1,56(sp)
   10576:	f84a                	sd	s2,48(sp)
   10578:	e45e                	sd	s7,8(sp)
   1057a:	8aaa                	mv	s5,a0
   1057c:	8b2e                	mv	s6,a1
   1057e:	4a05                	li	s4,1
   10580:	59fd                	li	s3,-1
   10582:	1f8c3903          	ld	s2,504(s8)
   10586:	02090463          	beqz	s2,105ae <__call_exitprocs+0x52>
   1058a:	00892483          	lw	s1,8(s2)
   1058e:	fff4841b          	addiw	s0,s1,-1
   10592:	00044e63          	bltz	s0,105ae <__call_exitprocs+0x52>
   10596:	048e                	slli	s1,s1,0x3
   10598:	94ca                	add	s1,s1,s2
   1059a:	020b0663          	beqz	s6,105c6 <__call_exitprocs+0x6a>
   1059e:	2084b783          	ld	a5,520(s1)
   105a2:	03678263          	beq	a5,s6,105c6 <__call_exitprocs+0x6a>
   105a6:	347d                	addiw	s0,s0,-1
   105a8:	14e1                	addi	s1,s1,-8
   105aa:	ff3418e3          	bne	s0,s3,1059a <__call_exitprocs+0x3e>
   105ae:	60a6                	ld	ra,72(sp)
   105b0:	6406                	ld	s0,64(sp)
   105b2:	74e2                	ld	s1,56(sp)
   105b4:	7942                	ld	s2,48(sp)
   105b6:	79a2                	ld	s3,40(sp)
   105b8:	7a02                	ld	s4,32(sp)
   105ba:	6ae2                	ld	s5,24(sp)
   105bc:	6b42                	ld	s6,16(sp)
   105be:	6ba2                	ld	s7,8(sp)
   105c0:	6c02                	ld	s8,0(sp)
   105c2:	6161                	addi	sp,sp,80
   105c4:	8082                	ret
   105c6:	00892783          	lw	a5,8(s2)
   105ca:	6498                	ld	a4,8(s1)
   105cc:	37fd                	addiw	a5,a5,-1
   105ce:	04878263          	beq	a5,s0,10612 <__call_exitprocs+0xb6>
   105d2:	0004b423          	sd	zero,8(s1)
   105d6:	db61                	beqz	a4,105a6 <__call_exitprocs+0x4a>
   105d8:	31092783          	lw	a5,784(s2)
   105dc:	008a16bb          	sllw	a3,s4,s0
   105e0:	00892b83          	lw	s7,8(s2)
   105e4:	8ff5                	and	a5,a5,a3
   105e6:	2781                	sext.w	a5,a5
   105e8:	eb99                	bnez	a5,105fe <__call_exitprocs+0xa2>
   105ea:	9702                	jalr	a4
   105ec:	00892783          	lw	a5,8(s2)
   105f0:	f97799e3          	bne	a5,s7,10582 <__call_exitprocs+0x26>
   105f4:	1f8c3783          	ld	a5,504(s8)
   105f8:	fb2787e3          	beq	a5,s2,105a6 <__call_exitprocs+0x4a>
   105fc:	b759                	j	10582 <__call_exitprocs+0x26>
   105fe:	31492783          	lw	a5,788(s2)
   10602:	1084b583          	ld	a1,264(s1)
   10606:	8ff5                	and	a5,a5,a3
   10608:	2781                	sext.w	a5,a5
   1060a:	e799                	bnez	a5,10618 <__call_exitprocs+0xbc>
   1060c:	8556                	mv	a0,s5
   1060e:	9702                	jalr	a4
   10610:	bff1                	j	105ec <__call_exitprocs+0x90>
   10612:	00892423          	sw	s0,8(s2)
   10616:	b7c1                	j	105d6 <__call_exitprocs+0x7a>
   10618:	852e                	mv	a0,a1
   1061a:	9702                	jalr	a4
   1061c:	bfc1                	j	105ec <__call_exitprocs+0x90>

000000000001061e <__fp_lock>:
   1061e:	4501                	li	a0,0
   10620:	8082                	ret

0000000000010622 <_cleanup_r>:
   10622:	00001597          	auipc	a1,0x1
   10626:	66458593          	addi	a1,a1,1636 # 11c86 <_fclose_r>
   1062a:	a525                	j	10c52 <_fwalk_reent>

000000000001062c <__sinit.part.0>:
   1062c:	7139                	addi	sp,sp,-64
   1062e:	fc06                	sd	ra,56(sp)
   10630:	f822                	sd	s0,48(sp)
   10632:	f426                	sd	s1,40(sp)
   10634:	f04a                	sd	s2,32(sp)
   10636:	ec4e                	sd	s3,24(sp)
   10638:	e852                	sd	s4,16(sp)
   1063a:	e456                	sd	s5,8(sp)
   1063c:	e05a                	sd	s6,0(sp)
   1063e:	6500                	ld	s0,8(a0)
   10640:	00000717          	auipc	a4,0x0
   10644:	fe270713          	addi	a4,a4,-30 # 10622 <_cleanup_r>
   10648:	ed38                	sd	a4,88(a0)
   1064a:	53850793          	addi	a5,a0,1336
   1064e:	470d                	li	a4,3
   10650:	52e52423          	sw	a4,1320(a0)
   10654:	52f53823          	sd	a5,1328(a0)
   10658:	52053023          	sd	zero,1312(a0)
   1065c:	4791                	li	a5,4
   1065e:	892a                	mv	s2,a0
   10660:	c81c                	sw	a5,16(s0)
   10662:	4621                	li	a2,8
   10664:	4581                	li	a1,0
   10666:	0a042623          	sw	zero,172(s0)
   1066a:	00043023          	sd	zero,0(s0)
   1066e:	00043423          	sd	zero,8(s0)
   10672:	00043c23          	sd	zero,24(s0)
   10676:	02042023          	sw	zero,32(s0)
   1067a:	02042423          	sw	zero,40(s0)
   1067e:	0a440513          	addi	a0,s0,164
   10682:	c97ff0ef          	jal	ra,10318 <memset>
   10686:	01093483          	ld	s1,16(s2)
   1068a:	00001b17          	auipc	s6,0x1
   1068e:	3b8b0b13          	addi	s6,s6,952 # 11a42 <__sread>
   10692:	00001a97          	auipc	s5,0x1
   10696:	3eca8a93          	addi	s5,s5,1004 # 11a7e <__swrite>
   1069a:	00001a17          	auipc	s4,0x1
   1069e:	436a0a13          	addi	s4,s4,1078 # 11ad0 <__sseek>
   106a2:	00001997          	auipc	s3,0x1
   106a6:	47098993          	addi	s3,s3,1136 # 11b12 <__sclose>
   106aa:	67c1                	lui	a5,0x10
   106ac:	03643c23          	sd	s6,56(s0)
   106b0:	05543023          	sd	s5,64(s0)
   106b4:	05443423          	sd	s4,72(s0)
   106b8:	05343823          	sd	s3,80(s0)
   106bc:	f800                	sd	s0,48(s0)
   106be:	07a5                	addi	a5,a5,9
   106c0:	c89c                	sw	a5,16(s1)
   106c2:	4621                	li	a2,8
   106c4:	4581                	li	a1,0
   106c6:	0a04a623          	sw	zero,172(s1)
   106ca:	0004b023          	sd	zero,0(s1)
   106ce:	0004b423          	sd	zero,8(s1)
   106d2:	0004bc23          	sd	zero,24(s1)
   106d6:	0204a023          	sw	zero,32(s1)
   106da:	0204a423          	sw	zero,40(s1)
   106de:	0a448513          	addi	a0,s1,164
   106e2:	c37ff0ef          	jal	ra,10318 <memset>
   106e6:	01893403          	ld	s0,24(s2)
   106ea:	000207b7          	lui	a5,0x20
   106ee:	0364bc23          	sd	s6,56(s1)
   106f2:	0554b023          	sd	s5,64(s1)
   106f6:	0544b423          	sd	s4,72(s1)
   106fa:	0534b823          	sd	s3,80(s1)
   106fe:	f884                	sd	s1,48(s1)
   10700:	07c9                	addi	a5,a5,18
   10702:	c81c                	sw	a5,16(s0)
   10704:	0a042623          	sw	zero,172(s0)
   10708:	00043023          	sd	zero,0(s0)
   1070c:	00043423          	sd	zero,8(s0)
   10710:	00043c23          	sd	zero,24(s0)
   10714:	02042023          	sw	zero,32(s0)
   10718:	02042423          	sw	zero,40(s0)
   1071c:	0a440513          	addi	a0,s0,164
   10720:	4621                	li	a2,8
   10722:	4581                	li	a1,0
   10724:	bf5ff0ef          	jal	ra,10318 <memset>
   10728:	70e2                	ld	ra,56(sp)
   1072a:	03643c23          	sd	s6,56(s0)
   1072e:	05543023          	sd	s5,64(s0)
   10732:	05443423          	sd	s4,72(s0)
   10736:	05343823          	sd	s3,80(s0)
   1073a:	f800                	sd	s0,48(s0)
   1073c:	7442                	ld	s0,48(sp)
   1073e:	4785                	li	a5,1
   10740:	04f92823          	sw	a5,80(s2)
   10744:	74a2                	ld	s1,40(sp)
   10746:	7902                	ld	s2,32(sp)
   10748:	69e2                	ld	s3,24(sp)
   1074a:	6a42                	ld	s4,16(sp)
   1074c:	6aa2                	ld	s5,8(sp)
   1074e:	6b02                	ld	s6,0(sp)
   10750:	6121                	addi	sp,sp,64
   10752:	8082                	ret

0000000000010754 <__fp_unlock>:
   10754:	4501                	li	a0,0
   10756:	8082                	ret

0000000000010758 <__sfmoreglue>:
   10758:	1101                	addi	sp,sp,-32
   1075a:	e426                	sd	s1,8(sp)
   1075c:	0b000613          	li	a2,176
   10760:	fff5849b          	addiw	s1,a1,-1
   10764:	02c484b3          	mul	s1,s1,a2
   10768:	e04a                	sd	s2,0(sp)
   1076a:	892e                	mv	s2,a1
   1076c:	e822                	sd	s0,16(sp)
   1076e:	ec06                	sd	ra,24(sp)
   10770:	0c848593          	addi	a1,s1,200
   10774:	570000ef          	jal	ra,10ce4 <_malloc_r>
   10778:	842a                	mv	s0,a0
   1077a:	cd01                	beqz	a0,10792 <__sfmoreglue+0x3a>
   1077c:	0561                	addi	a0,a0,24
   1077e:	00043023          	sd	zero,0(s0)
   10782:	01242423          	sw	s2,8(s0)
   10786:	e808                	sd	a0,16(s0)
   10788:	0b048613          	addi	a2,s1,176
   1078c:	4581                	li	a1,0
   1078e:	b8bff0ef          	jal	ra,10318 <memset>
   10792:	8522                	mv	a0,s0
   10794:	60e2                	ld	ra,24(sp)
   10796:	6442                	ld	s0,16(sp)
   10798:	64a2                	ld	s1,8(sp)
   1079a:	6902                	ld	s2,0(sp)
   1079c:	6105                	addi	sp,sp,32
   1079e:	8082                	ret

00000000000107a0 <__sfp>:
   107a0:	7179                	addi	sp,sp,-48
   107a2:	73818793          	addi	a5,gp,1848 # 14738 <_global_impure_ptr>
   107a6:	ec26                	sd	s1,24(sp)
   107a8:	6384                	ld	s1,0(a5)
   107aa:	e44e                	sd	s3,8(sp)
   107ac:	f406                	sd	ra,40(sp)
   107ae:	48bc                	lw	a5,80(s1)
   107b0:	f022                	sd	s0,32(sp)
   107b2:	e84a                	sd	s2,16(sp)
   107b4:	89aa                	mv	s3,a0
   107b6:	c7c1                	beqz	a5,1083e <__sfp+0x9e>
   107b8:	52048493          	addi	s1,s1,1312
   107bc:	0b000913          	li	s2,176
   107c0:	449c                	lw	a5,8(s1)
   107c2:	6880                	ld	s0,16(s1)
   107c4:	02f05463          	blez	a5,107ec <__sfp+0x4c>
   107c8:	01041703          	lh	a4,16(s0)
   107cc:	c705                	beqz	a4,107f4 <__sfp+0x54>
   107ce:	37fd                	addiw	a5,a5,-1
   107d0:	1782                	slli	a5,a5,0x20
   107d2:	9381                	srli	a5,a5,0x20
   107d4:	0785                	addi	a5,a5,1
   107d6:	032787b3          	mul	a5,a5,s2
   107da:	97a2                	add	a5,a5,s0
   107dc:	a021                	j	107e4 <__sfp+0x44>
   107de:	01041703          	lh	a4,16(s0)
   107e2:	cb09                	beqz	a4,107f4 <__sfp+0x54>
   107e4:	0b040413          	addi	s0,s0,176
   107e8:	fef41be3          	bne	s0,a5,107de <__sfp+0x3e>
   107ec:	6080                	ld	s0,0(s1)
   107ee:	cc21                	beqz	s0,10846 <__sfp+0xa6>
   107f0:	84a2                	mv	s1,s0
   107f2:	b7f9                	j	107c0 <__sfp+0x20>
   107f4:	77c1                	lui	a5,0xffff0
   107f6:	0785                	addi	a5,a5,1
   107f8:	0a042623          	sw	zero,172(s0)
   107fc:	00043023          	sd	zero,0(s0)
   10800:	00043423          	sd	zero,8(s0)
   10804:	c81c                	sw	a5,16(s0)
   10806:	00043c23          	sd	zero,24(s0)
   1080a:	02042023          	sw	zero,32(s0)
   1080e:	02042423          	sw	zero,40(s0)
   10812:	4621                	li	a2,8
   10814:	4581                	li	a1,0
   10816:	0a440513          	addi	a0,s0,164
   1081a:	affff0ef          	jal	ra,10318 <memset>
   1081e:	04043c23          	sd	zero,88(s0)
   10822:	06042023          	sw	zero,96(s0)
   10826:	06043c23          	sd	zero,120(s0)
   1082a:	08042023          	sw	zero,128(s0)
   1082e:	8522                	mv	a0,s0
   10830:	70a2                	ld	ra,40(sp)
   10832:	7402                	ld	s0,32(sp)
   10834:	64e2                	ld	s1,24(sp)
   10836:	6942                	ld	s2,16(sp)
   10838:	69a2                	ld	s3,8(sp)
   1083a:	6145                	addi	sp,sp,48
   1083c:	8082                	ret
   1083e:	8526                	mv	a0,s1
   10840:	dedff0ef          	jal	ra,1062c <__sinit.part.0>
   10844:	bf95                	j	107b8 <__sfp+0x18>
   10846:	4591                	li	a1,4
   10848:	854e                	mv	a0,s3
   1084a:	f0fff0ef          	jal	ra,10758 <__sfmoreglue>
   1084e:	e088                	sd	a0,0(s1)
   10850:	842a                	mv	s0,a0
   10852:	fd59                	bnez	a0,107f0 <__sfp+0x50>
   10854:	47b1                	li	a5,12
   10856:	00f9a023          	sw	a5,0(s3)
   1085a:	bfd1                	j	1082e <__sfp+0x8e>

000000000001085c <_cleanup>:
   1085c:	73818793          	addi	a5,gp,1848 # 14738 <_global_impure_ptr>
   10860:	6388                	ld	a0,0(a5)
   10862:	00001597          	auipc	a1,0x1
   10866:	42458593          	addi	a1,a1,1060 # 11c86 <_fclose_r>
   1086a:	a6e5                	j	10c52 <_fwalk_reent>

000000000001086c <__sinit>:
   1086c:	493c                	lw	a5,80(a0)
   1086e:	c391                	beqz	a5,10872 <__sinit+0x6>
   10870:	8082                	ret
   10872:	bb6d                	j	1062c <__sinit.part.0>

0000000000010874 <__sfp_lock_acquire>:
   10874:	8082                	ret

0000000000010876 <__sfp_lock_release>:
   10876:	8082                	ret

0000000000010878 <__sinit_lock_acquire>:
   10878:	8082                	ret

000000000001087a <__sinit_lock_release>:
   1087a:	8082                	ret

000000000001087c <__fp_lock_all>:
   1087c:	74818793          	addi	a5,gp,1864 # 14748 <_impure_ptr>
   10880:	6388                	ld	a0,0(a5)
   10882:	00000597          	auipc	a1,0x0
   10886:	d9c58593          	addi	a1,a1,-612 # 1061e <__fp_lock>
   1088a:	ae3d                	j	10bc8 <_fwalk>

000000000001088c <__fp_unlock_all>:
   1088c:	74818793          	addi	a5,gp,1864 # 14748 <_impure_ptr>
   10890:	6388                	ld	a0,0(a5)
   10892:	00000597          	auipc	a1,0x0
   10896:	ec258593          	addi	a1,a1,-318 # 10754 <__fp_unlock>
   1089a:	a63d                	j	10bc8 <_fwalk>

000000000001089c <__sfvwrite_r>:
   1089c:	6a1c                	ld	a5,16(a2)
   1089e:	1a078e63          	beqz	a5,10a5a <__sfvwrite_r+0x1be>
   108a2:	0105d783          	lhu	a5,16(a1)
   108a6:	711d                	addi	sp,sp,-96
   108a8:	e8a2                	sd	s0,80(sp)
   108aa:	f852                	sd	s4,48(sp)
   108ac:	f456                	sd	s5,40(sp)
   108ae:	ec86                	sd	ra,88(sp)
   108b0:	e4a6                	sd	s1,72(sp)
   108b2:	e0ca                	sd	s2,64(sp)
   108b4:	fc4e                	sd	s3,56(sp)
   108b6:	f05a                	sd	s6,32(sp)
   108b8:	ec5e                	sd	s7,24(sp)
   108ba:	e862                	sd	s8,16(sp)
   108bc:	e466                	sd	s9,8(sp)
   108be:	e06a                	sd	s10,0(sp)
   108c0:	0087f713          	andi	a4,a5,8
   108c4:	842e                	mv	s0,a1
   108c6:	8aaa                	mv	s5,a0
   108c8:	8a32                	mv	s4,a2
   108ca:	c335                	beqz	a4,1092e <__sfvwrite_r+0x92>
   108cc:	6d98                	ld	a4,24(a1)
   108ce:	c325                	beqz	a4,1092e <__sfvwrite_r+0x92>
   108d0:	0027f713          	andi	a4,a5,2
   108d4:	000a3903          	ld	s2,0(s4)
   108d8:	cb25                	beqz	a4,10948 <__sfvwrite_r+0xac>
   108da:	6038                	ld	a4,64(s0)
   108dc:	781c                	ld	a5,48(s0)
   108de:	80000b37          	lui	s6,0x80000
   108e2:	4981                	li	s3,0
   108e4:	4481                	li	s1,0
   108e6:	c00b4b13          	xori	s6,s6,-1024
   108ea:	864e                	mv	a2,s3
   108ec:	85be                	mv	a1,a5
   108ee:	8556                	mv	a0,s5
   108f0:	c88d                	beqz	s1,10922 <__sfvwrite_r+0x86>
   108f2:	86a6                	mv	a3,s1
   108f4:	009b7363          	bgeu	s6,s1,108fa <__sfvwrite_r+0x5e>
   108f8:	86da                	mv	a3,s6
   108fa:	2681                	sext.w	a3,a3
   108fc:	9702                	jalr	a4
   108fe:	14a05663          	blez	a0,10a4a <__sfvwrite_r+0x1ae>
   10902:	010a3783          	ld	a5,16(s4)
   10906:	99aa                	add	s3,s3,a0
   10908:	8c89                	sub	s1,s1,a0
   1090a:	40a78533          	sub	a0,a5,a0
   1090e:	00aa3823          	sd	a0,16(s4)
   10912:	10050863          	beqz	a0,10a22 <__sfvwrite_r+0x186>
   10916:	781c                	ld	a5,48(s0)
   10918:	6038                	ld	a4,64(s0)
   1091a:	864e                	mv	a2,s3
   1091c:	85be                	mv	a1,a5
   1091e:	8556                	mv	a0,s5
   10920:	f8e9                	bnez	s1,108f2 <__sfvwrite_r+0x56>
   10922:	00093983          	ld	s3,0(s2)
   10926:	00893483          	ld	s1,8(s2)
   1092a:	0941                	addi	s2,s2,16
   1092c:	bf7d                	j	108ea <__sfvwrite_r+0x4e>
   1092e:	85a2                	mv	a1,s0
   10930:	8556                	mv	a0,s5
   10932:	226010ef          	jal	ra,11b58 <__swsetup_r>
   10936:	28051763          	bnez	a0,10bc4 <__sfvwrite_r+0x328>
   1093a:	01045783          	lhu	a5,16(s0)
   1093e:	000a3903          	ld	s2,0(s4)
   10942:	0027f713          	andi	a4,a5,2
   10946:	fb51                	bnez	a4,108da <__sfvwrite_r+0x3e>
   10948:	0017f713          	andi	a4,a5,1
   1094c:	eb35                	bnez	a4,109c0 <__sfvwrite_r+0x124>
   1094e:	4444                	lw	s1,12(s0)
   10950:	6008                	ld	a0,0(s0)
   10952:	80000b37          	lui	s6,0x80000
   10956:	ffeb4b93          	xori	s7,s6,-2
   1095a:	4c01                	li	s8,0
   1095c:	4981                	li	s3,0
   1095e:	fffb4b13          	not	s6,s6
   10962:	8ca6                	mv	s9,s1
   10964:	04098863          	beqz	s3,109b4 <__sfvwrite_r+0x118>
   10968:	2007f713          	andi	a4,a5,512
   1096c:	12070963          	beqz	a4,10a9e <__sfvwrite_r+0x202>
   10970:	8d26                	mv	s10,s1
   10972:	1899f663          	bgeu	s3,s1,10afe <__sfvwrite_r+0x262>
   10976:	8cce                	mv	s9,s3
   10978:	8d4e                	mv	s10,s3
   1097a:	866a                	mv	a2,s10
   1097c:	85e2                	mv	a1,s8
   1097e:	359000ef          	jal	ra,114d6 <memmove>
   10982:	445c                	lw	a5,12(s0)
   10984:	6010                	ld	a2,0(s0)
   10986:	84ce                	mv	s1,s3
   10988:	41978cbb          	subw	s9,a5,s9
   1098c:	966a                	add	a2,a2,s10
   1098e:	01942623          	sw	s9,12(s0)
   10992:	e010                	sd	a2,0(s0)
   10994:	4981                	li	s3,0
   10996:	010a3783          	ld	a5,16(s4)
   1099a:	9c26                	add	s8,s8,s1
   1099c:	409784b3          	sub	s1,a5,s1
   109a0:	009a3823          	sd	s1,16(s4)
   109a4:	ccbd                	beqz	s1,10a22 <__sfvwrite_r+0x186>
   109a6:	4444                	lw	s1,12(s0)
   109a8:	6008                	ld	a0,0(s0)
   109aa:	01045783          	lhu	a5,16(s0)
   109ae:	8ca6                	mv	s9,s1
   109b0:	fa099ce3          	bnez	s3,10968 <__sfvwrite_r+0xcc>
   109b4:	00093c03          	ld	s8,0(s2)
   109b8:	00893983          	ld	s3,8(s2)
   109bc:	0941                	addi	s2,s2,16
   109be:	b755                	j	10962 <__sfvwrite_r+0xc6>
   109c0:	4981                	li	s3,0
   109c2:	4501                	li	a0,0
   109c4:	4c81                	li	s9,0
   109c6:	4481                	li	s1,0
   109c8:	c8d9                	beqz	s1,10a5e <__sfvwrite_r+0x1c2>
   109ca:	c145                	beqz	a0,10a6a <__sfvwrite_r+0x1ce>
   109cc:	8c4e                	mv	s8,s3
   109ce:	0134f363          	bgeu	s1,s3,109d4 <__sfvwrite_r+0x138>
   109d2:	8c26                	mv	s8,s1
   109d4:	6008                	ld	a0,0(s0)
   109d6:	6c1c                	ld	a5,24(s0)
   109d8:	8b62                	mv	s6,s8
   109da:	5014                	lw	a3,32(s0)
   109dc:	00a7f763          	bgeu	a5,a0,109ea <__sfvwrite_r+0x14e>
   109e0:	4450                	lw	a2,12(s0)
   109e2:	00d60bbb          	addw	s7,a2,a3
   109e6:	098bcd63          	blt	s7,s8,10a80 <__sfvwrite_r+0x1e4>
   109ea:	18dc4463          	blt	s8,a3,10b72 <__sfvwrite_r+0x2d6>
   109ee:	603c                	ld	a5,64(s0)
   109f0:	780c                	ld	a1,48(s0)
   109f2:	8666                	mv	a2,s9
   109f4:	8556                	mv	a0,s5
   109f6:	9782                	jalr	a5
   109f8:	8b2a                	mv	s6,a0
   109fa:	04a05863          	blez	a0,10a4a <__sfvwrite_r+0x1ae>
   109fe:	0005061b          	sext.w	a2,a0
   10a02:	40c989bb          	subw	s3,s3,a2
   10a06:	4505                	li	a0,1
   10a08:	02098c63          	beqz	s3,10a40 <__sfvwrite_r+0x1a4>
   10a0c:	010a3783          	ld	a5,16(s4)
   10a10:	9cda                	add	s9,s9,s6
   10a12:	416484b3          	sub	s1,s1,s6
   10a16:	41678b33          	sub	s6,a5,s6
   10a1a:	016a3823          	sd	s6,16(s4)
   10a1e:	fa0b15e3          	bnez	s6,109c8 <__sfvwrite_r+0x12c>
   10a22:	4501                	li	a0,0
   10a24:	60e6                	ld	ra,88(sp)
   10a26:	6446                	ld	s0,80(sp)
   10a28:	64a6                	ld	s1,72(sp)
   10a2a:	6906                	ld	s2,64(sp)
   10a2c:	79e2                	ld	s3,56(sp)
   10a2e:	7a42                	ld	s4,48(sp)
   10a30:	7aa2                	ld	s5,40(sp)
   10a32:	7b02                	ld	s6,32(sp)
   10a34:	6be2                	ld	s7,24(sp)
   10a36:	6c42                	ld	s8,16(sp)
   10a38:	6ca2                	ld	s9,8(sp)
   10a3a:	6d02                	ld	s10,0(sp)
   10a3c:	6125                	addi	sp,sp,96
   10a3e:	8082                	ret
   10a40:	85a2                	mv	a1,s0
   10a42:	8556                	mv	a0,s5
   10a44:	490010ef          	jal	ra,11ed4 <_fflush_r>
   10a48:	d171                	beqz	a0,10a0c <__sfvwrite_r+0x170>
   10a4a:	01041783          	lh	a5,16(s0)
   10a4e:	0407e793          	ori	a5,a5,64
   10a52:	00f41823          	sh	a5,16(s0)
   10a56:	557d                	li	a0,-1
   10a58:	b7f1                	j	10a24 <__sfvwrite_r+0x188>
   10a5a:	4501                	li	a0,0
   10a5c:	8082                	ret
   10a5e:	00893483          	ld	s1,8(s2)
   10a62:	00093c83          	ld	s9,0(s2)
   10a66:	0941                	addi	s2,s2,16
   10a68:	d8fd                	beqz	s1,10a5e <__sfvwrite_r+0x1c2>
   10a6a:	8626                	mv	a2,s1
   10a6c:	45a9                	li	a1,10
   10a6e:	8566                	mv	a0,s9
   10a70:	0d5000ef          	jal	ra,11344 <memchr>
   10a74:	12050f63          	beqz	a0,10bb2 <__sfvwrite_r+0x316>
   10a78:	0505                	addi	a0,a0,1
   10a7a:	419509bb          	subw	s3,a0,s9
   10a7e:	b7b9                	j	109cc <__sfvwrite_r+0x130>
   10a80:	85e6                	mv	a1,s9
   10a82:	865e                	mv	a2,s7
   10a84:	253000ef          	jal	ra,114d6 <memmove>
   10a88:	601c                	ld	a5,0(s0)
   10a8a:	85a2                	mv	a1,s0
   10a8c:	8556                	mv	a0,s5
   10a8e:	97de                	add	a5,a5,s7
   10a90:	e01c                	sd	a5,0(s0)
   10a92:	442010ef          	jal	ra,11ed4 <_fflush_r>
   10a96:	f955                	bnez	a0,10a4a <__sfvwrite_r+0x1ae>
   10a98:	865e                	mv	a2,s7
   10a9a:	8b5e                	mv	s6,s7
   10a9c:	b79d                	j	10a02 <__sfvwrite_r+0x166>
   10a9e:	6c1c                	ld	a5,24(s0)
   10aa0:	02a7e863          	bltu	a5,a0,10ad0 <__sfvwrite_r+0x234>
   10aa4:	501c                	lw	a5,32(s0)
   10aa6:	02f9e563          	bltu	s3,a5,10ad0 <__sfvwrite_r+0x234>
   10aaa:	86ce                	mv	a3,s3
   10aac:	013bf363          	bgeu	s7,s3,10ab2 <__sfvwrite_r+0x216>
   10ab0:	86da                	mv	a3,s6
   10ab2:	02f6c6bb          	divw	a3,a3,a5
   10ab6:	6038                	ld	a4,64(s0)
   10ab8:	780c                	ld	a1,48(s0)
   10aba:	8662                	mv	a2,s8
   10abc:	8556                	mv	a0,s5
   10abe:	02f686bb          	mulw	a3,a3,a5
   10ac2:	9702                	jalr	a4
   10ac4:	f8a053e3          	blez	a0,10a4a <__sfvwrite_r+0x1ae>
   10ac8:	84aa                	mv	s1,a0
   10aca:	409989b3          	sub	s3,s3,s1
   10ace:	b5e1                	j	10996 <__sfvwrite_r+0xfa>
   10ad0:	0099f363          	bgeu	s3,s1,10ad6 <__sfvwrite_r+0x23a>
   10ad4:	84ce                	mv	s1,s3
   10ad6:	8626                	mv	a2,s1
   10ad8:	85e2                	mv	a1,s8
   10ada:	1fd000ef          	jal	ra,114d6 <memmove>
   10ade:	445c                	lw	a5,12(s0)
   10ae0:	6018                	ld	a4,0(s0)
   10ae2:	409786bb          	subw	a3,a5,s1
   10ae6:	9726                	add	a4,a4,s1
   10ae8:	c454                	sw	a3,12(s0)
   10aea:	e018                	sd	a4,0(s0)
   10aec:	fef9                	bnez	a3,10aca <__sfvwrite_r+0x22e>
   10aee:	85a2                	mv	a1,s0
   10af0:	8556                	mv	a0,s5
   10af2:	3e2010ef          	jal	ra,11ed4 <_fflush_r>
   10af6:	f931                	bnez	a0,10a4a <__sfvwrite_r+0x1ae>
   10af8:	409989b3          	sub	s3,s3,s1
   10afc:	bd69                	j	10996 <__sfvwrite_r+0xfa>
   10afe:	4807f713          	andi	a4,a5,1152
   10b02:	e6070ce3          	beqz	a4,1097a <__sfvwrite_r+0xde>
   10b06:	5014                	lw	a3,32(s0)
   10b08:	6c0c                	ld	a1,24(s0)
   10b0a:	00198713          	addi	a4,s3,1
   10b0e:	0016949b          	slliw	s1,a3,0x1
   10b12:	9ea5                	addw	a3,a3,s1
   10b14:	8d0d                	sub	a0,a0,a1
   10b16:	01f6d49b          	srliw	s1,a3,0x1f
   10b1a:	00050c9b          	sext.w	s9,a0
   10b1e:	9cb5                	addw	s1,s1,a3
   10b20:	4014d49b          	sraiw	s1,s1,0x1
   10b24:	9766                	add	a4,a4,s9
   10b26:	00e4f563          	bgeu	s1,a4,10b30 <__sfvwrite_r+0x294>
   10b2a:	0019849b          	addiw	s1,s3,1
   10b2e:	9ca9                	addw	s1,s1,a0
   10b30:	4007f793          	andi	a5,a5,1024
   10b34:	cfa9                	beqz	a5,10b8e <__sfvwrite_r+0x2f2>
   10b36:	85a6                	mv	a1,s1
   10b38:	8556                	mv	a0,s5
   10b3a:	1aa000ef          	jal	ra,10ce4 <_malloc_r>
   10b3e:	8d2a                	mv	s10,a0
   10b40:	cd25                	beqz	a0,10bb8 <__sfvwrite_r+0x31c>
   10b42:	6c0c                	ld	a1,24(s0)
   10b44:	8666                	mv	a2,s9
   10b46:	0af000ef          	jal	ra,113f4 <memcpy>
   10b4a:	01045783          	lhu	a5,16(s0)
   10b4e:	b7f7f793          	andi	a5,a5,-1153
   10b52:	0807e793          	ori	a5,a5,128
   10b56:	00f41823          	sh	a5,16(s0)
   10b5a:	019d0533          	add	a0,s10,s9
   10b5e:	419487bb          	subw	a5,s1,s9
   10b62:	01a43c23          	sd	s10,24(s0)
   10b66:	e008                	sd	a0,0(s0)
   10b68:	d004                	sw	s1,32(s0)
   10b6a:	8cce                	mv	s9,s3
   10b6c:	c45c                	sw	a5,12(s0)
   10b6e:	8d4e                	mv	s10,s3
   10b70:	b529                	j	1097a <__sfvwrite_r+0xde>
   10b72:	8662                	mv	a2,s8
   10b74:	85e6                	mv	a1,s9
   10b76:	161000ef          	jal	ra,114d6 <memmove>
   10b7a:	4458                	lw	a4,12(s0)
   10b7c:	601c                	ld	a5,0(s0)
   10b7e:	000c061b          	sext.w	a2,s8
   10b82:	9f11                	subw	a4,a4,a2
   10b84:	9c3e                	add	s8,s8,a5
   10b86:	c458                	sw	a4,12(s0)
   10b88:	01843023          	sd	s8,0(s0)
   10b8c:	bd9d                	j	10a02 <__sfvwrite_r+0x166>
   10b8e:	8626                	mv	a2,s1
   10b90:	8556                	mv	a0,s5
   10b92:	21f000ef          	jal	ra,115b0 <_realloc_r>
   10b96:	8d2a                	mv	s10,a0
   10b98:	f169                	bnez	a0,10b5a <__sfvwrite_r+0x2be>
   10b9a:	6c0c                	ld	a1,24(s0)
   10b9c:	8556                	mv	a0,s5
   10b9e:	456010ef          	jal	ra,11ff4 <_free_r>
   10ba2:	01041783          	lh	a5,16(s0)
   10ba6:	4731                	li	a4,12
   10ba8:	00eaa023          	sw	a4,0(s5)
   10bac:	f7f7f793          	andi	a5,a5,-129
   10bb0:	bd79                	j	10a4e <__sfvwrite_r+0x1b2>
   10bb2:	0014899b          	addiw	s3,s1,1
   10bb6:	bd19                	j	109cc <__sfvwrite_r+0x130>
   10bb8:	47b1                	li	a5,12
   10bba:	00faa023          	sw	a5,0(s5)
   10bbe:	01041783          	lh	a5,16(s0)
   10bc2:	b571                	j	10a4e <__sfvwrite_r+0x1b2>
   10bc4:	557d                	li	a0,-1
   10bc6:	bdb9                	j	10a24 <__sfvwrite_r+0x188>

0000000000010bc8 <_fwalk>:
   10bc8:	715d                	addi	sp,sp,-80
   10bca:	f84a                	sd	s2,48(sp)
   10bcc:	e486                	sd	ra,72(sp)
   10bce:	e0a2                	sd	s0,64(sp)
   10bd0:	fc26                	sd	s1,56(sp)
   10bd2:	f44e                	sd	s3,40(sp)
   10bd4:	f052                	sd	s4,32(sp)
   10bd6:	ec56                	sd	s5,24(sp)
   10bd8:	e85a                	sd	s6,16(sp)
   10bda:	e45e                	sd	s7,8(sp)
   10bdc:	52050913          	addi	s2,a0,1312
   10be0:	06090763          	beqz	s2,10c4e <_fwalk+0x86>
   10be4:	8a2e                	mv	s4,a1
   10be6:	4b01                	li	s6,0
   10be8:	0b000a93          	li	s5,176
   10bec:	4b85                	li	s7,1
   10bee:	59fd                	li	s3,-1
   10bf0:	00892783          	lw	a5,8(s2)
   10bf4:	01093403          	ld	s0,16(s2)
   10bf8:	02f05b63          	blez	a5,10c2e <_fwalk+0x66>
   10bfc:	fff7849b          	addiw	s1,a5,-1
   10c00:	1482                	slli	s1,s1,0x20
   10c02:	9081                	srli	s1,s1,0x20
   10c04:	0485                	addi	s1,s1,1
   10c06:	035484b3          	mul	s1,s1,s5
   10c0a:	94a2                	add	s1,s1,s0
   10c0c:	01045783          	lhu	a5,16(s0)
   10c10:	00fbfb63          	bgeu	s7,a5,10c26 <_fwalk+0x5e>
   10c14:	01241783          	lh	a5,18(s0)
   10c18:	8522                	mv	a0,s0
   10c1a:	01378663          	beq	a5,s3,10c26 <_fwalk+0x5e>
   10c1e:	9a02                	jalr	s4
   10c20:	01656b33          	or	s6,a0,s6
   10c24:	2b01                	sext.w	s6,s6
   10c26:	0b040413          	addi	s0,s0,176
   10c2a:	fe9411e3          	bne	s0,s1,10c0c <_fwalk+0x44>
   10c2e:	00093903          	ld	s2,0(s2)
   10c32:	fa091fe3          	bnez	s2,10bf0 <_fwalk+0x28>
   10c36:	60a6                	ld	ra,72(sp)
   10c38:	6406                	ld	s0,64(sp)
   10c3a:	855a                	mv	a0,s6
   10c3c:	74e2                	ld	s1,56(sp)
   10c3e:	7942                	ld	s2,48(sp)
   10c40:	79a2                	ld	s3,40(sp)
   10c42:	7a02                	ld	s4,32(sp)
   10c44:	6ae2                	ld	s5,24(sp)
   10c46:	6b42                	ld	s6,16(sp)
   10c48:	6ba2                	ld	s7,8(sp)
   10c4a:	6161                	addi	sp,sp,80
   10c4c:	8082                	ret
   10c4e:	4b01                	li	s6,0
   10c50:	b7dd                	j	10c36 <_fwalk+0x6e>

0000000000010c52 <_fwalk_reent>:
   10c52:	715d                	addi	sp,sp,-80
   10c54:	f84a                	sd	s2,48(sp)
   10c56:	e486                	sd	ra,72(sp)
   10c58:	e0a2                	sd	s0,64(sp)
   10c5a:	fc26                	sd	s1,56(sp)
   10c5c:	f44e                	sd	s3,40(sp)
   10c5e:	f052                	sd	s4,32(sp)
   10c60:	ec56                	sd	s5,24(sp)
   10c62:	e85a                	sd	s6,16(sp)
   10c64:	e45e                	sd	s7,8(sp)
   10c66:	e062                	sd	s8,0(sp)
   10c68:	52050913          	addi	s2,a0,1312
   10c6c:	06090a63          	beqz	s2,10ce0 <_fwalk_reent+0x8e>
   10c70:	8aae                	mv	s5,a1
   10c72:	89aa                	mv	s3,a0
   10c74:	4b81                	li	s7,0
   10c76:	0b000b13          	li	s6,176
   10c7a:	4c05                	li	s8,1
   10c7c:	5a7d                	li	s4,-1
   10c7e:	00892783          	lw	a5,8(s2)
   10c82:	01093403          	ld	s0,16(s2)
   10c86:	02f05c63          	blez	a5,10cbe <_fwalk_reent+0x6c>
   10c8a:	fff7849b          	addiw	s1,a5,-1
   10c8e:	1482                	slli	s1,s1,0x20
   10c90:	9081                	srli	s1,s1,0x20
   10c92:	0485                	addi	s1,s1,1
   10c94:	036484b3          	mul	s1,s1,s6
   10c98:	94a2                	add	s1,s1,s0
   10c9a:	01045783          	lhu	a5,16(s0)
   10c9e:	00fc7c63          	bgeu	s8,a5,10cb6 <_fwalk_reent+0x64>
   10ca2:	01241783          	lh	a5,18(s0)
   10ca6:	85a2                	mv	a1,s0
   10ca8:	854e                	mv	a0,s3
   10caa:	01478663          	beq	a5,s4,10cb6 <_fwalk_reent+0x64>
   10cae:	9a82                	jalr	s5
   10cb0:	01756bb3          	or	s7,a0,s7
   10cb4:	2b81                	sext.w	s7,s7
   10cb6:	0b040413          	addi	s0,s0,176
   10cba:	fe9410e3          	bne	s0,s1,10c9a <_fwalk_reent+0x48>
   10cbe:	00093903          	ld	s2,0(s2)
   10cc2:	fa091ee3          	bnez	s2,10c7e <_fwalk_reent+0x2c>
   10cc6:	60a6                	ld	ra,72(sp)
   10cc8:	6406                	ld	s0,64(sp)
   10cca:	855e                	mv	a0,s7
   10ccc:	74e2                	ld	s1,56(sp)
   10cce:	7942                	ld	s2,48(sp)
   10cd0:	79a2                	ld	s3,40(sp)
   10cd2:	7a02                	ld	s4,32(sp)
   10cd4:	6ae2                	ld	s5,24(sp)
   10cd6:	6b42                	ld	s6,16(sp)
   10cd8:	6ba2                	ld	s7,8(sp)
   10cda:	6c02                	ld	s8,0(sp)
   10cdc:	6161                	addi	sp,sp,80
   10cde:	8082                	ret
   10ce0:	4b81                	li	s7,0
   10ce2:	b7d5                	j	10cc6 <_fwalk_reent+0x74>

0000000000010ce4 <_malloc_r>:
   10ce4:	711d                	addi	sp,sp,-96
   10ce6:	e4a6                	sd	s1,72(sp)
   10ce8:	e0ca                	sd	s2,64(sp)
   10cea:	ec86                	sd	ra,88(sp)
   10cec:	e8a2                	sd	s0,80(sp)
   10cee:	fc4e                	sd	s3,56(sp)
   10cf0:	f852                	sd	s4,48(sp)
   10cf2:	f456                	sd	s5,40(sp)
   10cf4:	f05a                	sd	s6,32(sp)
   10cf6:	ec5e                	sd	s7,24(sp)
   10cf8:	e862                	sd	s8,16(sp)
   10cfa:	e466                	sd	s9,8(sp)
   10cfc:	01758493          	addi	s1,a1,23
   10d00:	02e00793          	li	a5,46
   10d04:	892a                	mv	s2,a0
   10d06:	0697e963          	bltu	a5,s1,10d78 <_malloc_r+0x94>
   10d0a:	02000793          	li	a5,32
   10d0e:	04b7e463          	bltu	a5,a1,10d56 <_malloc_r+0x72>
   10d12:	09b000ef          	jal	ra,115ac <__malloc_lock>
   10d16:	02000493          	li	s1,32
   10d1a:	05000793          	li	a5,80
   10d1e:	4611                	li	a2,4
   10d20:	00003997          	auipc	s3,0x3
   10d24:	1f098993          	addi	s3,s3,496 # 13f10 <__malloc_av_>
   10d28:	97ce                	add	a5,a5,s3
   10d2a:	6780                	ld	s0,8(a5)
   10d2c:	ff078713          	addi	a4,a5,-16 # fffffffffffefff0 <__BSS_END__+0xfffffffffffdb7f0>
   10d30:	20e40463          	beq	s0,a4,10f38 <_malloc_r+0x254>
   10d34:	641c                	ld	a5,8(s0)
   10d36:	6c14                	ld	a3,24(s0)
   10d38:	6810                	ld	a2,16(s0)
   10d3a:	9bf1                	andi	a5,a5,-4
   10d3c:	97a2                	add	a5,a5,s0
   10d3e:	6798                	ld	a4,8(a5)
   10d40:	ee14                	sd	a3,24(a2)
   10d42:	ea90                	sd	a2,16(a3)
   10d44:	00176713          	ori	a4,a4,1
   10d48:	854a                	mv	a0,s2
   10d4a:	e798                	sd	a4,8(a5)
   10d4c:	063000ef          	jal	ra,115ae <__malloc_unlock>
   10d50:	01040513          	addi	a0,s0,16
   10d54:	a029                	j	10d5e <_malloc_r+0x7a>
   10d56:	47b1                	li	a5,12
   10d58:	00f92023          	sw	a5,0(s2)
   10d5c:	4501                	li	a0,0
   10d5e:	60e6                	ld	ra,88(sp)
   10d60:	6446                	ld	s0,80(sp)
   10d62:	64a6                	ld	s1,72(sp)
   10d64:	6906                	ld	s2,64(sp)
   10d66:	79e2                	ld	s3,56(sp)
   10d68:	7a42                	ld	s4,48(sp)
   10d6a:	7aa2                	ld	s5,40(sp)
   10d6c:	7b02                	ld	s6,32(sp)
   10d6e:	6be2                	ld	s7,24(sp)
   10d70:	6c42                	ld	s8,16(sp)
   10d72:	6ca2                	ld	s9,8(sp)
   10d74:	6125                	addi	sp,sp,96
   10d76:	8082                	ret
   10d78:	800007b7          	lui	a5,0x80000
   10d7c:	98c1                	andi	s1,s1,-16
   10d7e:	fff7c793          	not	a5,a5
   10d82:	fc97eae3          	bltu	a5,s1,10d56 <_malloc_r+0x72>
   10d86:	fcb4e8e3          	bltu	s1,a1,10d56 <_malloc_r+0x72>
   10d8a:	023000ef          	jal	ra,115ac <__malloc_lock>
   10d8e:	1f700793          	li	a5,503
   10d92:	3a97f263          	bgeu	a5,s1,11136 <_malloc_r+0x452>
   10d96:	0094d793          	srli	a5,s1,0x9
   10d9a:	2a078863          	beqz	a5,1104a <_malloc_r+0x366>
   10d9e:	4711                	li	a4,4
   10da0:	32f76f63          	bltu	a4,a5,110de <_malloc_r+0x3fa>
   10da4:	0064d513          	srli	a0,s1,0x6
   10da8:	2501                	sext.w	a0,a0
   10daa:	0395061b          	addiw	a2,a0,57
   10dae:	0016169b          	slliw	a3,a2,0x1
   10db2:	0385051b          	addiw	a0,a0,56
   10db6:	068e                	slli	a3,a3,0x3
   10db8:	00003997          	auipc	s3,0x3
   10dbc:	15898993          	addi	s3,s3,344 # 13f10 <__malloc_av_>
   10dc0:	96ce                	add	a3,a3,s3
   10dc2:	6680                	ld	s0,8(a3)
   10dc4:	16c1                	addi	a3,a3,-16
   10dc6:	16868d63          	beq	a3,s0,10f40 <_malloc_r+0x25c>
   10dca:	641c                	ld	a5,8(s0)
   10dcc:	45fd                	li	a1,31
   10dce:	9bf1                	andi	a5,a5,-4
   10dd0:	40978733          	sub	a4,a5,s1
   10dd4:	00e5cd63          	blt	a1,a4,10dee <_malloc_r+0x10a>
   10dd8:	2a075c63          	bgez	a4,11090 <_malloc_r+0x3ac>
   10ddc:	6c00                	ld	s0,24(s0)
   10dde:	16868163          	beq	a3,s0,10f40 <_malloc_r+0x25c>
   10de2:	641c                	ld	a5,8(s0)
   10de4:	9bf1                	andi	a5,a5,-4
   10de6:	40978733          	sub	a4,a5,s1
   10dea:	fee5d7e3          	bge	a1,a4,10dd8 <_malloc_r+0xf4>
   10dee:	0209b403          	ld	s0,32(s3)
   10df2:	00003817          	auipc	a6,0x3
   10df6:	12e80813          	addi	a6,a6,302 # 13f20 <__malloc_av_+0x10>
   10dfa:	862a                	mv	a2,a0
   10dfc:	15041a63          	bne	s0,a6,10f50 <_malloc_r+0x26c>
   10e00:	0089b783          	ld	a5,8(s3)
   10e04:	4026571b          	sraiw	a4,a2,0x2
   10e08:	4685                	li	a3,1
   10e0a:	00e696b3          	sll	a3,a3,a4
   10e0e:	1ad7f863          	bgeu	a5,a3,10fbe <_malloc_r+0x2da>
   10e12:	0109b403          	ld	s0,16(s3)
   10e16:	00843a03          	ld	s4,8(s0)
   10e1a:	ffca7a93          	andi	s5,s4,-4
   10e1e:	009ae763          	bltu	s5,s1,10e2c <_malloc_r+0x148>
   10e22:	409a87b3          	sub	a5,s5,s1
   10e26:	477d                	li	a4,31
   10e28:	24f74363          	blt	a4,a5,1106e <_malloc_r+0x38a>
   10e2c:	77018793          	addi	a5,gp,1904 # 14770 <__malloc_top_pad>
   10e30:	75018c13          	addi	s8,gp,1872 # 14750 <__malloc_sbrk_base>
   10e34:	0007ba03          	ld	s4,0(a5) # ffffffff80000000 <__BSS_END__+0xffffffff7ffeb800>
   10e38:	000c3703          	ld	a4,0(s8)
   10e3c:	57fd                	li	a5,-1
   10e3e:	01540bb3          	add	s7,s0,s5
   10e42:	9a26                	add	s4,s4,s1
   10e44:	38f70b63          	beq	a4,a5,111da <_malloc_r+0x4f6>
   10e48:	6785                	lui	a5,0x1
   10e4a:	07fd                	addi	a5,a5,31
   10e4c:	9a3e                	add	s4,s4,a5
   10e4e:	77fd                	lui	a5,0xfffff
   10e50:	00fa7a33          	and	s4,s4,a5
   10e54:	85d2                	mv	a1,s4
   10e56:	854a                	mv	a0,s2
   10e58:	3b1000ef          	jal	ra,11a08 <_sbrk_r>
   10e5c:	57fd                	li	a5,-1
   10e5e:	8b2a                	mv	s6,a0
   10e60:	30f50163          	beq	a0,a5,11162 <_malloc_r+0x47e>
   10e64:	2f756d63          	bltu	a0,s7,1115e <_malloc_r+0x47a>
   10e68:	7b818c93          	addi	s9,gp,1976 # 147b8 <__malloc_current_mallinfo>
   10e6c:	000ca703          	lw	a4,0(s9)
   10e70:	014707bb          	addw	a5,a4,s4
   10e74:	7af1ac23          	sw	a5,1976(gp) # 147b8 <__malloc_current_mallinfo>
   10e78:	86be                	mv	a3,a5
   10e7a:	40ab8163          	beq	s7,a0,1127c <_malloc_r+0x598>
   10e7e:	000c3703          	ld	a4,0(s8)
   10e82:	57fd                	li	a5,-1
   10e84:	40f70863          	beq	a4,a5,11294 <_malloc_r+0x5b0>
   10e88:	417b07b3          	sub	a5,s6,s7
   10e8c:	9fb5                	addw	a5,a5,a3
   10e8e:	7af1ac23          	sw	a5,1976(gp) # 147b8 <__malloc_current_mallinfo>
   10e92:	00fb7b93          	andi	s7,s6,15
   10e96:	360b8263          	beqz	s7,111fa <_malloc_r+0x516>
   10e9a:	417b0b33          	sub	s6,s6,s7
   10e9e:	6785                	lui	a5,0x1
   10ea0:	0b41                	addi	s6,s6,16
   10ea2:	fff78713          	addi	a4,a5,-1 # fff <register_fini-0xf0b1>
   10ea6:	014b0c33          	add	s8,s6,s4
   10eaa:	07c1                	addi	a5,a5,16
   10eac:	41778a33          	sub	s4,a5,s7
   10eb0:	00ec77b3          	and	a5,s8,a4
   10eb4:	40fa0a33          	sub	s4,s4,a5
   10eb8:	00ea7a33          	and	s4,s4,a4
   10ebc:	85d2                	mv	a1,s4
   10ebe:	854a                	mv	a0,s2
   10ec0:	349000ef          	jal	ra,11a08 <_sbrk_r>
   10ec4:	57fd                	li	a5,-1
   10ec6:	40f50e63          	beq	a0,a5,112e2 <_malloc_r+0x5fe>
   10eca:	41650533          	sub	a0,a0,s6
   10ece:	000a071b          	sext.w	a4,s4
   10ed2:	9a2a                	add	s4,s4,a0
   10ed4:	000ca783          	lw	a5,0(s9)
   10ed8:	00003697          	auipc	a3,0x3
   10edc:	0566b423          	sd	s6,72(a3) # 13f20 <__malloc_av_+0x10>
   10ee0:	001a6a13          	ori	s4,s4,1
   10ee4:	9fb9                	addw	a5,a5,a4
   10ee6:	7af1ac23          	sw	a5,1976(gp) # 147b8 <__malloc_current_mallinfo>
   10eea:	014b3423          	sd	s4,8(s6) # ffffffff80000008 <__BSS_END__+0xffffffff7ffeb808>
   10eee:	3b340663          	beq	s0,s3,1129a <_malloc_r+0x5b6>
   10ef2:	467d                	li	a2,31
   10ef4:	3b567563          	bgeu	a2,s5,1129e <_malloc_r+0x5ba>
   10ef8:	6414                	ld	a3,8(s0)
   10efa:	fe8a8713          	addi	a4,s5,-24
   10efe:	9b41                	andi	a4,a4,-16
   10f00:	8a85                	andi	a3,a3,1
   10f02:	8ed9                	or	a3,a3,a4
   10f04:	e414                	sd	a3,8(s0)
   10f06:	45a5                	li	a1,9
   10f08:	00e406b3          	add	a3,s0,a4
   10f0c:	e68c                	sd	a1,8(a3)
   10f0e:	ea8c                	sd	a1,16(a3)
   10f10:	3ee66063          	bltu	a2,a4,112f0 <_malloc_r+0x60c>
   10f14:	008b3a03          	ld	s4,8(s6)
   10f18:	845a                	mv	s0,s6
   10f1a:	76818713          	addi	a4,gp,1896 # 14768 <__malloc_max_sbrked_mem>
   10f1e:	6318                	ld	a4,0(a4)
   10f20:	00f77463          	bgeu	a4,a5,10f28 <_malloc_r+0x244>
   10f24:	76f1b423          	sd	a5,1896(gp) # 14768 <__malloc_max_sbrked_mem>
   10f28:	76018713          	addi	a4,gp,1888 # 14760 <_edata>
   10f2c:	6318                	ld	a4,0(a4)
   10f2e:	22f77e63          	bgeu	a4,a5,1116a <_malloc_r+0x486>
   10f32:	76f1b023          	sd	a5,1888(gp) # 14760 <_edata>
   10f36:	ac15                	j	1116a <_malloc_r+0x486>
   10f38:	6f80                	ld	s0,24(a5)
   10f3a:	2609                	addiw	a2,a2,2
   10f3c:	de879ce3          	bne	a5,s0,10d34 <_malloc_r+0x50>
   10f40:	0209b403          	ld	s0,32(s3)
   10f44:	00003817          	auipc	a6,0x3
   10f48:	fdc80813          	addi	a6,a6,-36 # 13f20 <__malloc_av_+0x10>
   10f4c:	eb040ae3          	beq	s0,a6,10e00 <_malloc_r+0x11c>
   10f50:	641c                	ld	a5,8(s0)
   10f52:	46fd                	li	a3,31
   10f54:	9bf1                	andi	a5,a5,-4
   10f56:	40978733          	sub	a4,a5,s1
   10f5a:	1ce6ca63          	blt	a3,a4,1112e <_malloc_r+0x44a>
   10f5e:	00003697          	auipc	a3,0x3
   10f62:	fd06bd23          	sd	a6,-38(a3) # 13f38 <__malloc_av_+0x28>
   10f66:	00003697          	auipc	a3,0x3
   10f6a:	fd06b523          	sd	a6,-54(a3) # 13f30 <__malloc_av_+0x20>
   10f6e:	0e075563          	bgez	a4,11058 <_malloc_r+0x374>
   10f72:	1ff00713          	li	a4,511
   10f76:	12f76063          	bltu	a4,a5,11096 <_malloc_r+0x3b2>
   10f7a:	838d                	srli	a5,a5,0x3
   10f7c:	2781                	sext.w	a5,a5
   10f7e:	0017871b          	addiw	a4,a5,1
   10f82:	0017171b          	slliw	a4,a4,0x1
   10f86:	070e                	slli	a4,a4,0x3
   10f88:	0089b503          	ld	a0,8(s3)
   10f8c:	974e                	add	a4,a4,s3
   10f8e:	630c                	ld	a1,0(a4)
   10f90:	4027d69b          	sraiw	a3,a5,0x2
   10f94:	4785                	li	a5,1
   10f96:	00d797b3          	sll	a5,a5,a3
   10f9a:	8fc9                	or	a5,a5,a0
   10f9c:	ff070693          	addi	a3,a4,-16
   10fa0:	ec14                	sd	a3,24(s0)
   10fa2:	e80c                	sd	a1,16(s0)
   10fa4:	00003697          	auipc	a3,0x3
   10fa8:	f6f6ba23          	sd	a5,-140(a3) # 13f18 <__malloc_av_+0x8>
   10fac:	e300                	sd	s0,0(a4)
   10fae:	ed80                	sd	s0,24(a1)
   10fb0:	4026571b          	sraiw	a4,a2,0x2
   10fb4:	4685                	li	a3,1
   10fb6:	00e696b3          	sll	a3,a3,a4
   10fba:	e4d7ece3          	bltu	a5,a3,10e12 <_malloc_r+0x12e>
   10fbe:	00f6f733          	and	a4,a3,a5
   10fc2:	ef01                	bnez	a4,10fda <_malloc_r+0x2f6>
   10fc4:	0686                	slli	a3,a3,0x1
   10fc6:	9a71                	andi	a2,a2,-4
   10fc8:	00f6f733          	and	a4,a3,a5
   10fcc:	2611                	addiw	a2,a2,4
   10fce:	e711                	bnez	a4,10fda <_malloc_r+0x2f6>
   10fd0:	0686                	slli	a3,a3,0x1
   10fd2:	00f6f733          	and	a4,a3,a5
   10fd6:	2611                	addiw	a2,a2,4
   10fd8:	df65                	beqz	a4,10fd0 <_malloc_r+0x2ec>
   10fda:	457d                	li	a0,31
   10fdc:	0016089b          	addiw	a7,a2,1
   10fe0:	0018989b          	slliw	a7,a7,0x1
   10fe4:	088e                	slli	a7,a7,0x3
   10fe6:	18c1                	addi	a7,a7,-16
   10fe8:	98ce                	add	a7,a7,s3
   10fea:	85c6                	mv	a1,a7
   10fec:	8332                	mv	t1,a2
   10fee:	6d80                	ld	s0,24(a1)
   10ff0:	00859863          	bne	a1,s0,11000 <_malloc_r+0x31c>
   10ff4:	a239                	j	11102 <_malloc_r+0x41e>
   10ff6:	10075d63          	bgez	a4,11110 <_malloc_r+0x42c>
   10ffa:	6c00                	ld	s0,24(s0)
   10ffc:	10858363          	beq	a1,s0,11102 <_malloc_r+0x41e>
   11000:	641c                	ld	a5,8(s0)
   11002:	9bf1                	andi	a5,a5,-4
   11004:	40978733          	sub	a4,a5,s1
   11008:	fee557e3          	bge	a0,a4,10ff6 <_malloc_r+0x312>
   1100c:	6c14                	ld	a3,24(s0)
   1100e:	6810                	ld	a2,16(s0)
   11010:	0014e593          	ori	a1,s1,1
   11014:	e40c                	sd	a1,8(s0)
   11016:	ee14                	sd	a3,24(a2)
   11018:	ea90                	sd	a2,16(a3)
   1101a:	94a2                	add	s1,s1,s0
   1101c:	00003697          	auipc	a3,0x3
   11020:	f096be23          	sd	s1,-228(a3) # 13f38 <__malloc_av_+0x28>
   11024:	00003697          	auipc	a3,0x3
   11028:	f096b623          	sd	s1,-244(a3) # 13f30 <__malloc_av_+0x20>
   1102c:	00176693          	ori	a3,a4,1
   11030:	0104bc23          	sd	a6,24(s1)
   11034:	0104b823          	sd	a6,16(s1)
   11038:	e494                	sd	a3,8(s1)
   1103a:	97a2                	add	a5,a5,s0
   1103c:	854a                	mv	a0,s2
   1103e:	e398                	sd	a4,0(a5)
   11040:	56e000ef          	jal	ra,115ae <__malloc_unlock>
   11044:	01040513          	addi	a0,s0,16
   11048:	bb19                	j	10d5e <_malloc_r+0x7a>
   1104a:	40000693          	li	a3,1024
   1104e:	04000613          	li	a2,64
   11052:	03f00513          	li	a0,63
   11056:	b38d                	j	10db8 <_malloc_r+0xd4>
   11058:	97a2                	add	a5,a5,s0
   1105a:	6798                	ld	a4,8(a5)
   1105c:	854a                	mv	a0,s2
   1105e:	00176713          	ori	a4,a4,1
   11062:	e798                	sd	a4,8(a5)
   11064:	54a000ef          	jal	ra,115ae <__malloc_unlock>
   11068:	01040513          	addi	a0,s0,16
   1106c:	b9cd                	j	10d5e <_malloc_r+0x7a>
   1106e:	0014e713          	ori	a4,s1,1
   11072:	e418                	sd	a4,8(s0)
   11074:	94a2                	add	s1,s1,s0
   11076:	00003717          	auipc	a4,0x3
   1107a:	ea973523          	sd	s1,-342(a4) # 13f20 <__malloc_av_+0x10>
   1107e:	0017e793          	ori	a5,a5,1
   11082:	854a                	mv	a0,s2
   11084:	e49c                	sd	a5,8(s1)
   11086:	528000ef          	jal	ra,115ae <__malloc_unlock>
   1108a:	01040513          	addi	a0,s0,16
   1108e:	b9c1                	j	10d5e <_malloc_r+0x7a>
   11090:	6c14                	ld	a3,24(s0)
   11092:	6810                	ld	a2,16(s0)
   11094:	b165                	j	10d3c <_malloc_r+0x58>
   11096:	0097d713          	srli	a4,a5,0x9
   1109a:	4691                	li	a3,4
   1109c:	0ae6f663          	bgeu	a3,a4,11148 <_malloc_r+0x464>
   110a0:	46d1                	li	a3,20
   110a2:	18e6e663          	bltu	a3,a4,1122e <_malloc_r+0x54a>
   110a6:	2701                	sext.w	a4,a4
   110a8:	05c7059b          	addiw	a1,a4,92
   110ac:	0015959b          	slliw	a1,a1,0x1
   110b0:	05b7069b          	addiw	a3,a4,91
   110b4:	058e                	slli	a1,a1,0x3
   110b6:	95ce                	add	a1,a1,s3
   110b8:	6198                	ld	a4,0(a1)
   110ba:	15c1                	addi	a1,a1,-16
   110bc:	12e58263          	beq	a1,a4,111e0 <_malloc_r+0x4fc>
   110c0:	6714                	ld	a3,8(a4)
   110c2:	9af1                	andi	a3,a3,-4
   110c4:	00d7f563          	bgeu	a5,a3,110ce <_malloc_r+0x3ea>
   110c8:	6b18                	ld	a4,16(a4)
   110ca:	fee59be3          	bne	a1,a4,110c0 <_malloc_r+0x3dc>
   110ce:	6f0c                	ld	a1,24(a4)
   110d0:	0089b783          	ld	a5,8(s3)
   110d4:	ec0c                	sd	a1,24(s0)
   110d6:	e818                	sd	a4,16(s0)
   110d8:	e980                	sd	s0,16(a1)
   110da:	ef00                	sd	s0,24(a4)
   110dc:	bdd1                	j	10fb0 <_malloc_r+0x2cc>
   110de:	4751                	li	a4,20
   110e0:	0af77363          	bgeu	a4,a5,11186 <_malloc_r+0x4a2>
   110e4:	05400713          	li	a4,84
   110e8:	16f76263          	bltu	a4,a5,1124c <_malloc_r+0x568>
   110ec:	00c4d513          	srli	a0,s1,0xc
   110f0:	2501                	sext.w	a0,a0
   110f2:	06f5061b          	addiw	a2,a0,111
   110f6:	0016169b          	slliw	a3,a2,0x1
   110fa:	06e5051b          	addiw	a0,a0,110
   110fe:	068e                	slli	a3,a3,0x3
   11100:	b965                	j	10db8 <_malloc_r+0xd4>
   11102:	2305                	addiw	t1,t1,1
   11104:	00337793          	andi	a5,t1,3
   11108:	05c1                	addi	a1,a1,16
   1110a:	ee0792e3          	bnez	a5,10fee <_malloc_r+0x30a>
   1110e:	a851                	j	111a2 <_malloc_r+0x4be>
   11110:	97a2                	add	a5,a5,s0
   11112:	6798                	ld	a4,8(a5)
   11114:	6c14                	ld	a3,24(s0)
   11116:	6810                	ld	a2,16(s0)
   11118:	00176713          	ori	a4,a4,1
   1111c:	e798                	sd	a4,8(a5)
   1111e:	ee14                	sd	a3,24(a2)
   11120:	854a                	mv	a0,s2
   11122:	ea90                	sd	a2,16(a3)
   11124:	48a000ef          	jal	ra,115ae <__malloc_unlock>
   11128:	01040513          	addi	a0,s0,16
   1112c:	b90d                	j	10d5e <_malloc_r+0x7a>
   1112e:	0014e693          	ori	a3,s1,1
   11132:	e414                	sd	a3,8(s0)
   11134:	b5dd                	j	1101a <_malloc_r+0x336>
   11136:	0034d613          	srli	a2,s1,0x3
   1113a:	2601                	sext.w	a2,a2
   1113c:	0016079b          	addiw	a5,a2,1
   11140:	0017979b          	slliw	a5,a5,0x1
   11144:	078e                	slli	a5,a5,0x3
   11146:	bee9                	j	10d20 <_malloc_r+0x3c>
   11148:	0067d713          	srli	a4,a5,0x6
   1114c:	2701                	sext.w	a4,a4
   1114e:	0397059b          	addiw	a1,a4,57
   11152:	0015959b          	slliw	a1,a1,0x1
   11156:	0387069b          	addiw	a3,a4,56
   1115a:	058e                	slli	a1,a1,0x3
   1115c:	bfa9                	j	110b6 <_malloc_r+0x3d2>
   1115e:	11340663          	beq	s0,s3,1126a <_malloc_r+0x586>
   11162:	0109b403          	ld	s0,16(s3)
   11166:	00843a03          	ld	s4,8(s0)
   1116a:	ffca7a13          	andi	s4,s4,-4
   1116e:	409a07b3          	sub	a5,s4,s1
   11172:	009a6563          	bltu	s4,s1,1117c <_malloc_r+0x498>
   11176:	477d                	li	a4,31
   11178:	eef74be3          	blt	a4,a5,1106e <_malloc_r+0x38a>
   1117c:	854a                	mv	a0,s2
   1117e:	430000ef          	jal	ra,115ae <__malloc_unlock>
   11182:	4501                	li	a0,0
   11184:	bee9                	j	10d5e <_malloc_r+0x7a>
   11186:	2781                	sext.w	a5,a5
   11188:	05c7861b          	addiw	a2,a5,92
   1118c:	0016169b          	slliw	a3,a2,0x1
   11190:	05b7851b          	addiw	a0,a5,91
   11194:	068e                	slli	a3,a3,0x3
   11196:	b10d                	j	10db8 <_malloc_r+0xd4>
   11198:	0108b783          	ld	a5,16(a7)
   1119c:	367d                	addiw	a2,a2,-1
   1119e:	1b179063          	bne	a5,a7,1133e <_malloc_r+0x65a>
   111a2:	00367793          	andi	a5,a2,3
   111a6:	18c1                	addi	a7,a7,-16
   111a8:	fbe5                	bnez	a5,11198 <_malloc_r+0x4b4>
   111aa:	0089b703          	ld	a4,8(s3)
   111ae:	fff6c793          	not	a5,a3
   111b2:	8ff9                	and	a5,a5,a4
   111b4:	00003717          	auipc	a4,0x3
   111b8:	d6f73223          	sd	a5,-668(a4) # 13f18 <__malloc_av_+0x8>
   111bc:	0686                	slli	a3,a3,0x1
   111be:	c4d7eae3          	bltu	a5,a3,10e12 <_malloc_r+0x12e>
   111c2:	c40688e3          	beqz	a3,10e12 <_malloc_r+0x12e>
   111c6:	00f6f733          	and	a4,a3,a5
   111ca:	e711                	bnez	a4,111d6 <_malloc_r+0x4f2>
   111cc:	0686                	slli	a3,a3,0x1
   111ce:	00f6f733          	and	a4,a3,a5
   111d2:	2311                	addiw	t1,t1,4
   111d4:	df65                	beqz	a4,111cc <_malloc_r+0x4e8>
   111d6:	861a                	mv	a2,t1
   111d8:	b511                	j	10fdc <_malloc_r+0x2f8>
   111da:	020a0a13          	addi	s4,s4,32
   111de:	b99d                	j	10e54 <_malloc_r+0x170>
   111e0:	0089b503          	ld	a0,8(s3)
   111e4:	4026d69b          	sraiw	a3,a3,0x2
   111e8:	4785                	li	a5,1
   111ea:	00d797b3          	sll	a5,a5,a3
   111ee:	8fc9                	or	a5,a5,a0
   111f0:	00003697          	auipc	a3,0x3
   111f4:	d2f6b423          	sd	a5,-728(a3) # 13f18 <__malloc_av_+0x8>
   111f8:	bdf1                	j	110d4 <_malloc_r+0x3f0>
   111fa:	6785                	lui	a5,0x1
   111fc:	fff78713          	addi	a4,a5,-1 # fff <register_fini-0xf0b1>
   11200:	014b0bb3          	add	s7,s6,s4
   11204:	00ebfbb3          	and	s7,s7,a4
   11208:	417787b3          	sub	a5,a5,s7
   1120c:	00e7fbb3          	and	s7,a5,a4
   11210:	85de                	mv	a1,s7
   11212:	854a                	mv	a0,s2
   11214:	7f4000ef          	jal	ra,11a08 <_sbrk_r>
   11218:	57fd                	li	a5,-1
   1121a:	4701                	li	a4,0
   1121c:	caf50ce3          	beq	a0,a5,10ed4 <_malloc_r+0x1f0>
   11220:	41650533          	sub	a0,a0,s6
   11224:	000b871b          	sext.w	a4,s7
   11228:	01750a33          	add	s4,a0,s7
   1122c:	b165                	j	10ed4 <_malloc_r+0x1f0>
   1122e:	05400693          	li	a3,84
   11232:	06e6ea63          	bltu	a3,a4,112a6 <_malloc_r+0x5c2>
   11236:	00c7d713          	srli	a4,a5,0xc
   1123a:	2701                	sext.w	a4,a4
   1123c:	06f7059b          	addiw	a1,a4,111
   11240:	0015959b          	slliw	a1,a1,0x1
   11244:	06e7069b          	addiw	a3,a4,110
   11248:	058e                	slli	a1,a1,0x3
   1124a:	b5b5                	j	110b6 <_malloc_r+0x3d2>
   1124c:	15400713          	li	a4,340
   11250:	06f76a63          	bltu	a4,a5,112c4 <_malloc_r+0x5e0>
   11254:	00f4d513          	srli	a0,s1,0xf
   11258:	2501                	sext.w	a0,a0
   1125a:	0785061b          	addiw	a2,a0,120
   1125e:	0016169b          	slliw	a3,a2,0x1
   11262:	0775051b          	addiw	a0,a0,119
   11266:	068e                	slli	a3,a3,0x3
   11268:	be81                	j	10db8 <_malloc_r+0xd4>
   1126a:	7b818c93          	addi	s9,gp,1976 # 147b8 <__malloc_current_mallinfo>
   1126e:	000ca783          	lw	a5,0(s9)
   11272:	014786bb          	addw	a3,a5,s4
   11276:	7ad1ac23          	sw	a3,1976(gp) # 147b8 <__malloc_current_mallinfo>
   1127a:	b111                	j	10e7e <_malloc_r+0x19a>
   1127c:	034b9713          	slli	a4,s7,0x34
   11280:	be071fe3          	bnez	a4,10e7e <_malloc_r+0x19a>
   11284:	0109b403          	ld	s0,16(s3)
   11288:	9a56                	add	s4,s4,s5
   1128a:	001a6a13          	ori	s4,s4,1
   1128e:	01443423          	sd	s4,8(s0)
   11292:	b161                	j	10f1a <_malloc_r+0x236>
   11294:	7561b823          	sd	s6,1872(gp) # 14750 <__malloc_sbrk_base>
   11298:	beed                	j	10e92 <_malloc_r+0x1ae>
   1129a:	845a                	mv	s0,s6
   1129c:	b9bd                	j	10f1a <_malloc_r+0x236>
   1129e:	4785                	li	a5,1
   112a0:	00fb3423          	sd	a5,8(s6)
   112a4:	bde1                	j	1117c <_malloc_r+0x498>
   112a6:	15400693          	li	a3,340
   112aa:	04e6ef63          	bltu	a3,a4,11308 <_malloc_r+0x624>
   112ae:	00f7d713          	srli	a4,a5,0xf
   112b2:	2701                	sext.w	a4,a4
   112b4:	0787059b          	addiw	a1,a4,120
   112b8:	0015959b          	slliw	a1,a1,0x1
   112bc:	0777069b          	addiw	a3,a4,119
   112c0:	058e                	slli	a1,a1,0x3
   112c2:	bbd5                	j	110b6 <_malloc_r+0x3d2>
   112c4:	55400713          	li	a4,1364
   112c8:	04f76f63          	bltu	a4,a5,11326 <_malloc_r+0x642>
   112cc:	0124d513          	srli	a0,s1,0x12
   112d0:	2501                	sext.w	a0,a0
   112d2:	07d5061b          	addiw	a2,a0,125
   112d6:	0016169b          	slliw	a3,a2,0x1
   112da:	07c5051b          	addiw	a0,a0,124
   112de:	068e                	slli	a3,a3,0x3
   112e0:	bce1                	j	10db8 <_malloc_r+0xd4>
   112e2:	1bc1                	addi	s7,s7,-16
   112e4:	017c0a33          	add	s4,s8,s7
   112e8:	416a0a33          	sub	s4,s4,s6
   112ec:	4701                	li	a4,0
   112ee:	b6dd                	j	10ed4 <_malloc_r+0x1f0>
   112f0:	01040593          	addi	a1,s0,16
   112f4:	854a                	mv	a0,s2
   112f6:	4ff000ef          	jal	ra,11ff4 <_free_r>
   112fa:	0109b403          	ld	s0,16(s3)
   112fe:	000ca783          	lw	a5,0(s9)
   11302:	00843a03          	ld	s4,8(s0)
   11306:	b911                	j	10f1a <_malloc_r+0x236>
   11308:	55400693          	li	a3,1364
   1130c:	02e6e463          	bltu	a3,a4,11334 <_malloc_r+0x650>
   11310:	0127d713          	srli	a4,a5,0x12
   11314:	2701                	sext.w	a4,a4
   11316:	07d7059b          	addiw	a1,a4,125
   1131a:	0015959b          	slliw	a1,a1,0x1
   1131e:	07c7069b          	addiw	a3,a4,124
   11322:	058e                	slli	a1,a1,0x3
   11324:	bb49                	j	110b6 <_malloc_r+0x3d2>
   11326:	7f000693          	li	a3,2032
   1132a:	07f00613          	li	a2,127
   1132e:	07e00513          	li	a0,126
   11332:	b459                	j	10db8 <_malloc_r+0xd4>
   11334:	7f000593          	li	a1,2032
   11338:	07e00693          	li	a3,126
   1133c:	bbad                	j	110b6 <_malloc_r+0x3d2>
   1133e:	0089b783          	ld	a5,8(s3)
   11342:	bdad                	j	111bc <_malloc_r+0x4d8>

0000000000011344 <memchr>:
   11344:	00757793          	andi	a5,a0,7
   11348:	0ff5f813          	andi	a6,a1,255
   1134c:	c3d5                	beqz	a5,113f0 <memchr+0xac>
   1134e:	fff60793          	addi	a5,a2,-1
   11352:	c239                	beqz	a2,11398 <memchr+0x54>
   11354:	00054703          	lbu	a4,0(a0)
   11358:	05070163          	beq	a4,a6,1139a <memchr+0x56>
   1135c:	56fd                	li	a3,-1
   1135e:	a801                	j	1136e <memchr+0x2a>
   11360:	17fd                	addi	a5,a5,-1
   11362:	02d78b63          	beq	a5,a3,11398 <memchr+0x54>
   11366:	00054703          	lbu	a4,0(a0)
   1136a:	03070863          	beq	a4,a6,1139a <memchr+0x56>
   1136e:	0505                	addi	a0,a0,1
   11370:	00757713          	andi	a4,a0,7
   11374:	f775                	bnez	a4,11360 <memchr+0x1c>
   11376:	471d                	li	a4,7
   11378:	02f76263          	bltu	a4,a5,1139c <memchr+0x58>
   1137c:	cf91                	beqz	a5,11398 <memchr+0x54>
   1137e:	00054703          	lbu	a4,0(a0)
   11382:	01070c63          	beq	a4,a6,1139a <memchr+0x56>
   11386:	97aa                	add	a5,a5,a0
   11388:	a029                	j	11392 <memchr+0x4e>
   1138a:	00054703          	lbu	a4,0(a0)
   1138e:	01070663          	beq	a4,a6,1139a <memchr+0x56>
   11392:	0505                	addi	a0,a0,1
   11394:	fea79be3          	bne	a5,a0,1138a <memchr+0x46>
   11398:	4501                	li	a0,0
   1139a:	8082                	ret
   1139c:	66c1                	lui	a3,0x10
   1139e:	0085971b          	slliw	a4,a1,0x8
   113a2:	16fd                	addi	a3,a3,-1
   113a4:	8f75                	and	a4,a4,a3
   113a6:	0ff5f593          	andi	a1,a1,255
   113aa:	8dd9                	or	a1,a1,a4
   113ac:	2581                	sext.w	a1,a1
   113ae:	00003697          	auipc	a3,0x3
   113b2:	37a68693          	addi	a3,a3,890 # 14728 <__SDATA_BEGIN__+0x8>
   113b6:	01059613          	slli	a2,a1,0x10
   113ba:	0006b883          	ld	a7,0(a3)
   113be:	00003697          	auipc	a3,0x3
   113c2:	37268693          	addi	a3,a3,882 # 14730 <__SDATA_BEGIN__+0x10>
   113c6:	00b66733          	or	a4,a2,a1
   113ca:	628c                	ld	a1,0(a3)
   113cc:	02071613          	slli	a2,a4,0x20
   113d0:	8e59                	or	a2,a2,a4
   113d2:	431d                	li	t1,7
   113d4:	6118                	ld	a4,0(a0)
   113d6:	8f31                	xor	a4,a4,a2
   113d8:	011706b3          	add	a3,a4,a7
   113dc:	fff74713          	not	a4,a4
   113e0:	8f75                	and	a4,a4,a3
   113e2:	8f6d                	and	a4,a4,a1
   113e4:	ff49                	bnez	a4,1137e <memchr+0x3a>
   113e6:	17e1                	addi	a5,a5,-8
   113e8:	0521                	addi	a0,a0,8
   113ea:	fef365e3          	bltu	t1,a5,113d4 <memchr+0x90>
   113ee:	b779                	j	1137c <memchr+0x38>
   113f0:	87b2                	mv	a5,a2
   113f2:	b751                	j	11376 <memchr+0x32>

00000000000113f4 <memcpy>:
   113f4:	00a5c7b3          	xor	a5,a1,a0
   113f8:	8b9d                	andi	a5,a5,7
   113fa:	00c508b3          	add	a7,a0,a2
   113fe:	e7a1                	bnez	a5,11446 <memcpy+0x52>
   11400:	479d                	li	a5,7
   11402:	04c7f263          	bgeu	a5,a2,11446 <memcpy+0x52>
   11406:	00757793          	andi	a5,a0,7
   1140a:	872a                	mv	a4,a0
   1140c:	eba9                	bnez	a5,1145e <memcpy+0x6a>
   1140e:	ff88f613          	andi	a2,a7,-8
   11412:	fc060793          	addi	a5,a2,-64
   11416:	06f76763          	bltu	a4,a5,11484 <memcpy+0x90>
   1141a:	02c77363          	bgeu	a4,a2,11440 <memcpy+0x4c>
   1141e:	86ae                	mv	a3,a1
   11420:	87ba                	mv	a5,a4
   11422:	0006b803          	ld	a6,0(a3)
   11426:	07a1                	addi	a5,a5,8
   11428:	06a1                	addi	a3,a3,8
   1142a:	ff07bc23          	sd	a6,-8(a5)
   1142e:	fec7eae3          	bltu	a5,a2,11422 <memcpy+0x2e>
   11432:	fff60793          	addi	a5,a2,-1
   11436:	8f99                	sub	a5,a5,a4
   11438:	9be1                	andi	a5,a5,-8
   1143a:	07a1                	addi	a5,a5,8
   1143c:	973e                	add	a4,a4,a5
   1143e:	95be                	add	a1,a1,a5
   11440:	01176663          	bltu	a4,a7,1144c <memcpy+0x58>
   11444:	8082                	ret
   11446:	872a                	mv	a4,a0
   11448:	ff157ee3          	bgeu	a0,a7,11444 <memcpy+0x50>
   1144c:	0005c783          	lbu	a5,0(a1)
   11450:	0705                	addi	a4,a4,1
   11452:	0585                	addi	a1,a1,1
   11454:	fef70fa3          	sb	a5,-1(a4)
   11458:	ff176ae3          	bltu	a4,a7,1144c <memcpy+0x58>
   1145c:	8082                	ret
   1145e:	0005c683          	lbu	a3,0(a1)
   11462:	0705                	addi	a4,a4,1
   11464:	00777793          	andi	a5,a4,7
   11468:	fed70fa3          	sb	a3,-1(a4)
   1146c:	0585                	addi	a1,a1,1
   1146e:	d3c5                	beqz	a5,1140e <memcpy+0x1a>
   11470:	0005c683          	lbu	a3,0(a1)
   11474:	0705                	addi	a4,a4,1
   11476:	00777793          	andi	a5,a4,7
   1147a:	fed70fa3          	sb	a3,-1(a4)
   1147e:	0585                	addi	a1,a1,1
   11480:	fff9                	bnez	a5,1145e <memcpy+0x6a>
   11482:	b771                	j	1140e <memcpy+0x1a>
   11484:	6194                	ld	a3,0(a1)
   11486:	0085b283          	ld	t0,8(a1)
   1148a:	0105bf83          	ld	t6,16(a1)
   1148e:	0185bf03          	ld	t5,24(a1)
   11492:	0205be83          	ld	t4,32(a1)
   11496:	0285be03          	ld	t3,40(a1)
   1149a:	0305b303          	ld	t1,48(a1)
   1149e:	0385b803          	ld	a6,56(a1)
   114a2:	04858593          	addi	a1,a1,72
   114a6:	e314                	sd	a3,0(a4)
   114a8:	ff85b683          	ld	a3,-8(a1)
   114ac:	00573423          	sd	t0,8(a4)
   114b0:	01f73823          	sd	t6,16(a4)
   114b4:	01e73c23          	sd	t5,24(a4)
   114b8:	03d73023          	sd	t4,32(a4)
   114bc:	03c73423          	sd	t3,40(a4)
   114c0:	02673823          	sd	t1,48(a4)
   114c4:	03073c23          	sd	a6,56(a4)
   114c8:	04870713          	addi	a4,a4,72
   114cc:	fed73c23          	sd	a3,-8(a4)
   114d0:	faf76ae3          	bltu	a4,a5,11484 <memcpy+0x90>
   114d4:	b799                	j	1141a <memcpy+0x26>

00000000000114d6 <memmove>:
   114d6:	02a5f263          	bgeu	a1,a0,114fa <memmove+0x24>
   114da:	00c587b3          	add	a5,a1,a2
   114de:	00f57e63          	bgeu	a0,a5,114fa <memmove+0x24>
   114e2:	00c50733          	add	a4,a0,a2
   114e6:	ca5d                	beqz	a2,1159c <memmove+0xc6>
   114e8:	17fd                	addi	a5,a5,-1
   114ea:	0007c683          	lbu	a3,0(a5)
   114ee:	177d                	addi	a4,a4,-1
   114f0:	00d70023          	sb	a3,0(a4)
   114f4:	fef59ae3          	bne	a1,a5,114e8 <memmove+0x12>
   114f8:	8082                	ret
   114fa:	47fd                	li	a5,31
   114fc:	02c7e163          	bltu	a5,a2,1151e <memmove+0x48>
   11500:	87aa                	mv	a5,a0
   11502:	fff60693          	addi	a3,a2,-1
   11506:	c245                	beqz	a2,115a6 <memmove+0xd0>
   11508:	0685                	addi	a3,a3,1
   1150a:	96be                	add	a3,a3,a5
   1150c:	0585                	addi	a1,a1,1
   1150e:	fff5c703          	lbu	a4,-1(a1)
   11512:	0785                	addi	a5,a5,1
   11514:	fee78fa3          	sb	a4,-1(a5)
   11518:	fed79ae3          	bne	a5,a3,1150c <memmove+0x36>
   1151c:	8082                	ret
   1151e:	00a5e7b3          	or	a5,a1,a0
   11522:	8b9d                	andi	a5,a5,7
   11524:	efad                	bnez	a5,1159e <memmove+0xc8>
   11526:	fe060893          	addi	a7,a2,-32
   1152a:	fe08f893          	andi	a7,a7,-32
   1152e:	02088893          	addi	a7,a7,32
   11532:	01150833          	add	a6,a0,a7
   11536:	872e                	mv	a4,a1
   11538:	87aa                	mv	a5,a0
   1153a:	6314                	ld	a3,0(a4)
   1153c:	02078793          	addi	a5,a5,32
   11540:	02070713          	addi	a4,a4,32
   11544:	fed7b023          	sd	a3,-32(a5)
   11548:	fe873683          	ld	a3,-24(a4)
   1154c:	fed7b423          	sd	a3,-24(a5)
   11550:	ff073683          	ld	a3,-16(a4)
   11554:	fed7b823          	sd	a3,-16(a5)
   11558:	ff873683          	ld	a3,-8(a4)
   1155c:	fed7bc23          	sd	a3,-8(a5)
   11560:	fcf81de3          	bne	a6,a5,1153a <memmove+0x64>
   11564:	01867713          	andi	a4,a2,24
   11568:	95c6                	add	a1,a1,a7
   1156a:	01f67813          	andi	a6,a2,31
   1156e:	cf0d                	beqz	a4,115a8 <memmove+0xd2>
   11570:	872e                	mv	a4,a1
   11572:	88be                	mv	a7,a5
   11574:	4e1d                	li	t3,7
   11576:	0721                	addi	a4,a4,8
   11578:	ff873303          	ld	t1,-8(a4)
   1157c:	08a1                	addi	a7,a7,8
   1157e:	40e806b3          	sub	a3,a6,a4
   11582:	fe68bc23          	sd	t1,-8(a7)
   11586:	96ae                	add	a3,a3,a1
   11588:	fede67e3          	bltu	t3,a3,11576 <memmove+0xa0>
   1158c:	ff880713          	addi	a4,a6,-8
   11590:	9b61                	andi	a4,a4,-8
   11592:	0721                	addi	a4,a4,8
   11594:	8a1d                	andi	a2,a2,7
   11596:	97ba                	add	a5,a5,a4
   11598:	95ba                	add	a1,a1,a4
   1159a:	b7a5                	j	11502 <memmove+0x2c>
   1159c:	8082                	ret
   1159e:	fff60693          	addi	a3,a2,-1
   115a2:	87aa                	mv	a5,a0
   115a4:	b795                	j	11508 <memmove+0x32>
   115a6:	8082                	ret
   115a8:	8642                	mv	a2,a6
   115aa:	bfa1                	j	11502 <memmove+0x2c>

00000000000115ac <__malloc_lock>:
   115ac:	8082                	ret

00000000000115ae <__malloc_unlock>:
   115ae:	8082                	ret

00000000000115b0 <_realloc_r>:
   115b0:	715d                	addi	sp,sp,-80
   115b2:	f84a                	sd	s2,48(sp)
   115b4:	e486                	sd	ra,72(sp)
   115b6:	e0a2                	sd	s0,64(sp)
   115b8:	fc26                	sd	s1,56(sp)
   115ba:	f44e                	sd	s3,40(sp)
   115bc:	f052                	sd	s4,32(sp)
   115be:	ec56                	sd	s5,24(sp)
   115c0:	e85a                	sd	s6,16(sp)
   115c2:	e45e                	sd	s7,8(sp)
   115c4:	e062                	sd	s8,0(sp)
   115c6:	8932                	mv	s2,a2
   115c8:	1a058563          	beqz	a1,11772 <_realloc_r+0x1c2>
   115cc:	8aae                	mv	s5,a1
   115ce:	8a2a                	mv	s4,a0
   115d0:	fddff0ef          	jal	ra,115ac <__malloc_lock>
   115d4:	ff8ab783          	ld	a5,-8(s5)
   115d8:	01790413          	addi	s0,s2,23
   115dc:	02e00713          	li	a4,46
   115e0:	ff0a8b13          	addi	s6,s5,-16
   115e4:	ffc7f493          	andi	s1,a5,-4
   115e8:	0a877f63          	bgeu	a4,s0,116a6 <_realloc_r+0xf6>
   115ec:	80000737          	lui	a4,0x80000
   115f0:	9841                	andi	s0,s0,-16
   115f2:	fff74713          	not	a4,a4
   115f6:	0a876c63          	bltu	a4,s0,116ae <_realloc_r+0xfe>
   115fa:	0b246a63          	bltu	s0,s2,116ae <_realloc_r+0xfe>
   115fe:	009b09b3          	add	s3,s6,s1
   11602:	1284d763          	bge	s1,s0,11730 <_realloc_r+0x180>
   11606:	00003717          	auipc	a4,0x3
   1160a:	90a70713          	addi	a4,a4,-1782 # 13f10 <__malloc_av_>
   1160e:	6b14                	ld	a3,16(a4)
   11610:	0089b703          	ld	a4,8(s3)
   11614:	1b368063          	beq	a3,s3,117b4 <_realloc_r+0x204>
   11618:	ffe77693          	andi	a3,a4,-2
   1161c:	96ce                	add	a3,a3,s3
   1161e:	6694                	ld	a3,8(a3)
   11620:	8a85                	andi	a3,a3,1
   11622:	12069d63          	bnez	a3,1175c <_realloc_r+0x1ac>
   11626:	9b71                	andi	a4,a4,-4
   11628:	00e486b3          	add	a3,s1,a4
   1162c:	2686df63          	bge	a3,s0,118aa <_realloc_r+0x2fa>
   11630:	8b85                	andi	a5,a5,1
   11632:	e38d                	bnez	a5,11654 <_realloc_r+0xa4>
   11634:	ff0abc03          	ld	s8,-16(s5)
   11638:	418b0c33          	sub	s8,s6,s8
   1163c:	008c3783          	ld	a5,8(s8)
   11640:	9bf1                	andi	a5,a5,-4
   11642:	973e                	add	a4,a4,a5
   11644:	00970bb3          	add	s7,a4,s1
   11648:	288bd663          	bge	s7,s0,118d4 <_realloc_r+0x324>
   1164c:	00f48bb3          	add	s7,s1,a5
   11650:	088bd063          	bge	s7,s0,116d0 <_realloc_r+0x120>
   11654:	85ca                	mv	a1,s2
   11656:	8552                	mv	a0,s4
   11658:	e8cff0ef          	jal	ra,10ce4 <_malloc_r>
   1165c:	892a                	mv	s2,a0
   1165e:	c121                	beqz	a0,1169e <_realloc_r+0xee>
   11660:	ff8ab783          	ld	a5,-8(s5)
   11664:	ff050713          	addi	a4,a0,-16
   11668:	9bf9                	andi	a5,a5,-2
   1166a:	97da                	add	a5,a5,s6
   1166c:	24e78963          	beq	a5,a4,118be <_realloc_r+0x30e>
   11670:	ff848613          	addi	a2,s1,-8
   11674:	04800793          	li	a5,72
   11678:	24c7ea63          	bltu	a5,a2,118cc <_realloc_r+0x31c>
   1167c:	02700713          	li	a4,39
   11680:	000ab683          	ld	a3,0(s5)
   11684:	1cc76e63          	bltu	a4,a2,11860 <_realloc_r+0x2b0>
   11688:	87aa                	mv	a5,a0
   1168a:	8756                	mv	a4,s5
   1168c:	e394                	sd	a3,0(a5)
   1168e:	6714                	ld	a3,8(a4)
   11690:	e794                	sd	a3,8(a5)
   11692:	6b18                	ld	a4,16(a4)
   11694:	eb98                	sd	a4,16(a5)
   11696:	85d6                	mv	a1,s5
   11698:	8552                	mv	a0,s4
   1169a:	15b000ef          	jal	ra,11ff4 <_free_r>
   1169e:	8552                	mv	a0,s4
   116a0:	f0fff0ef          	jal	ra,115ae <__malloc_unlock>
   116a4:	a809                	j	116b6 <_realloc_r+0x106>
   116a6:	02000413          	li	s0,32
   116aa:	f5247ae3          	bgeu	s0,s2,115fe <_realloc_r+0x4e>
   116ae:	47b1                	li	a5,12
   116b0:	00fa2023          	sw	a5,0(s4)
   116b4:	4901                	li	s2,0
   116b6:	60a6                	ld	ra,72(sp)
   116b8:	6406                	ld	s0,64(sp)
   116ba:	854a                	mv	a0,s2
   116bc:	74e2                	ld	s1,56(sp)
   116be:	7942                	ld	s2,48(sp)
   116c0:	79a2                	ld	s3,40(sp)
   116c2:	7a02                	ld	s4,32(sp)
   116c4:	6ae2                	ld	s5,24(sp)
   116c6:	6b42                	ld	s6,16(sp)
   116c8:	6ba2                	ld	s7,8(sp)
   116ca:	6c02                	ld	s8,0(sp)
   116cc:	6161                	addi	sp,sp,80
   116ce:	8082                	ret
   116d0:	018c3783          	ld	a5,24(s8)
   116d4:	010c3703          	ld	a4,16(s8)
   116d8:	ff848613          	addi	a2,s1,-8
   116dc:	04800693          	li	a3,72
   116e0:	ef1c                	sd	a5,24(a4)
   116e2:	eb98                	sd	a4,16(a5)
   116e4:	010c0913          	addi	s2,s8,16
   116e8:	017c09b3          	add	s3,s8,s7
   116ec:	26c6e663          	bltu	a3,a2,11958 <_realloc_r+0x3a8>
   116f0:	02700593          	li	a1,39
   116f4:	000ab703          	ld	a4,0(s5)
   116f8:	87ca                	mv	a5,s2
   116fa:	02c5f163          	bgeu	a1,a2,1171c <_realloc_r+0x16c>
   116fe:	00ec3823          	sd	a4,16(s8)
   11702:	008ab703          	ld	a4,8(s5)
   11706:	03700793          	li	a5,55
   1170a:	00ec3c23          	sd	a4,24(s8)
   1170e:	28c7e963          	bltu	a5,a2,119a0 <_realloc_r+0x3f0>
   11712:	010ab703          	ld	a4,16(s5)
   11716:	020c0793          	addi	a5,s8,32
   1171a:	0ac1                	addi	s5,s5,16
   1171c:	e398                	sd	a4,0(a5)
   1171e:	008ab703          	ld	a4,8(s5)
   11722:	84de                	mv	s1,s7
   11724:	8b62                	mv	s6,s8
   11726:	e798                	sd	a4,8(a5)
   11728:	010ab703          	ld	a4,16(s5)
   1172c:	8aca                	mv	s5,s2
   1172e:	eb98                	sd	a4,16(a5)
   11730:	008b3603          	ld	a2,8(s6)
   11734:	408487b3          	sub	a5,s1,s0
   11738:	477d                	li	a4,31
   1173a:	8a05                	andi	a2,a2,1
   1173c:	04f76963          	bltu	a4,a5,1178e <_realloc_r+0x1de>
   11740:	8e45                	or	a2,a2,s1
   11742:	00cb3423          	sd	a2,8(s6)
   11746:	0089b783          	ld	a5,8(s3)
   1174a:	0017e793          	ori	a5,a5,1
   1174e:	00f9b423          	sd	a5,8(s3)
   11752:	8552                	mv	a0,s4
   11754:	e5bff0ef          	jal	ra,115ae <__malloc_unlock>
   11758:	8956                	mv	s2,s5
   1175a:	bfb1                	j	116b6 <_realloc_r+0x106>
   1175c:	8b85                	andi	a5,a5,1
   1175e:	ee079be3          	bnez	a5,11654 <_realloc_r+0xa4>
   11762:	ff0abc03          	ld	s8,-16(s5)
   11766:	418b0c33          	sub	s8,s6,s8
   1176a:	008c3783          	ld	a5,8(s8)
   1176e:	9bf1                	andi	a5,a5,-4
   11770:	bdf1                	j	1164c <_realloc_r+0x9c>
   11772:	6406                	ld	s0,64(sp)
   11774:	60a6                	ld	ra,72(sp)
   11776:	74e2                	ld	s1,56(sp)
   11778:	7942                	ld	s2,48(sp)
   1177a:	79a2                	ld	s3,40(sp)
   1177c:	7a02                	ld	s4,32(sp)
   1177e:	6ae2                	ld	s5,24(sp)
   11780:	6b42                	ld	s6,16(sp)
   11782:	6ba2                	ld	s7,8(sp)
   11784:	6c02                	ld	s8,0(sp)
   11786:	85b2                	mv	a1,a2
   11788:	6161                	addi	sp,sp,80
   1178a:	d5aff06f          	j	10ce4 <_malloc_r>
   1178e:	8e41                	or	a2,a2,s0
   11790:	00cb3423          	sd	a2,8(s6)
   11794:	008b05b3          	add	a1,s6,s0
   11798:	0017e793          	ori	a5,a5,1
   1179c:	e59c                	sd	a5,8(a1)
   1179e:	0089b783          	ld	a5,8(s3)
   117a2:	05c1                	addi	a1,a1,16
   117a4:	8552                	mv	a0,s4
   117a6:	0017e793          	ori	a5,a5,1
   117aa:	00f9b423          	sd	a5,8(s3)
   117ae:	047000ef          	jal	ra,11ff4 <_free_r>
   117b2:	b745                	j	11752 <_realloc_r+0x1a2>
   117b4:	9b71                	andi	a4,a4,-4
   117b6:	00e486b3          	add	a3,s1,a4
   117ba:	02040613          	addi	a2,s0,32
   117be:	0cc6d063          	bge	a3,a2,1187e <_realloc_r+0x2ce>
   117c2:	8b85                	andi	a5,a5,1
   117c4:	e80798e3          	bnez	a5,11654 <_realloc_r+0xa4>
   117c8:	ff0abc03          	ld	s8,-16(s5)
   117cc:	418b0c33          	sub	s8,s6,s8
   117d0:	008c3783          	ld	a5,8(s8)
   117d4:	9bf1                	andi	a5,a5,-4
   117d6:	973e                	add	a4,a4,a5
   117d8:	009709b3          	add	s3,a4,s1
   117dc:	e6c9c8e3          	blt	s3,a2,1164c <_realloc_r+0x9c>
   117e0:	018c3783          	ld	a5,24(s8)
   117e4:	010c3703          	ld	a4,16(s8)
   117e8:	ff848613          	addi	a2,s1,-8
   117ec:	04800693          	li	a3,72
   117f0:	ef1c                	sd	a5,24(a4)
   117f2:	eb98                	sd	a4,16(a5)
   117f4:	010c0913          	addi	s2,s8,16
   117f8:	1cc6e563          	bltu	a3,a2,119c2 <_realloc_r+0x412>
   117fc:	02700593          	li	a1,39
   11800:	000ab703          	ld	a4,0(s5)
   11804:	87ca                	mv	a5,s2
   11806:	02c5f163          	bgeu	a1,a2,11828 <_realloc_r+0x278>
   1180a:	00ec3823          	sd	a4,16(s8)
   1180e:	008ab703          	ld	a4,8(s5)
   11812:	03700793          	li	a5,55
   11816:	00ec3c23          	sd	a4,24(s8)
   1181a:	1ac7e963          	bltu	a5,a2,119cc <_realloc_r+0x41c>
   1181e:	010ab703          	ld	a4,16(s5)
   11822:	020c0793          	addi	a5,s8,32
   11826:	0ac1                	addi	s5,s5,16
   11828:	e398                	sd	a4,0(a5)
   1182a:	008ab703          	ld	a4,8(s5)
   1182e:	e798                	sd	a4,8(a5)
   11830:	010ab703          	ld	a4,16(s5)
   11834:	eb98                	sd	a4,16(a5)
   11836:	008c0733          	add	a4,s8,s0
   1183a:	408987b3          	sub	a5,s3,s0
   1183e:	00002697          	auipc	a3,0x2
   11842:	6ee6b123          	sd	a4,1762(a3) # 13f20 <__malloc_av_+0x10>
   11846:	0017e793          	ori	a5,a5,1
   1184a:	e71c                	sd	a5,8(a4)
   1184c:	008c3783          	ld	a5,8(s8)
   11850:	8552                	mv	a0,s4
   11852:	8b85                	andi	a5,a5,1
   11854:	8c5d                	or	s0,s0,a5
   11856:	008c3423          	sd	s0,8(s8)
   1185a:	d55ff0ef          	jal	ra,115ae <__malloc_unlock>
   1185e:	bda1                	j	116b6 <_realloc_r+0x106>
   11860:	e114                	sd	a3,0(a0)
   11862:	008ab683          	ld	a3,8(s5)
   11866:	03700713          	li	a4,55
   1186a:	e514                	sd	a3,8(a0)
   1186c:	0ec76e63          	bltu	a4,a2,11968 <_realloc_r+0x3b8>
   11870:	010a8713          	addi	a4,s5,16
   11874:	01050793          	addi	a5,a0,16
   11878:	010ab683          	ld	a3,16(s5)
   1187c:	bd01                	j	1168c <_realloc_r+0xdc>
   1187e:	9b22                	add	s6,s6,s0
   11880:	408687b3          	sub	a5,a3,s0
   11884:	00002717          	auipc	a4,0x2
   11888:	69673e23          	sd	s6,1692(a4) # 13f20 <__malloc_av_+0x10>
   1188c:	0017e793          	ori	a5,a5,1
   11890:	00fb3423          	sd	a5,8(s6)
   11894:	ff8ab783          	ld	a5,-8(s5)
   11898:	8552                	mv	a0,s4
   1189a:	8956                	mv	s2,s5
   1189c:	8b85                	andi	a5,a5,1
   1189e:	8c5d                	or	s0,s0,a5
   118a0:	fe8abc23          	sd	s0,-8(s5)
   118a4:	d0bff0ef          	jal	ra,115ae <__malloc_unlock>
   118a8:	b539                	j	116b6 <_realloc_r+0x106>
   118aa:	0189b783          	ld	a5,24(s3)
   118ae:	0109b703          	ld	a4,16(s3)
   118b2:	84b6                	mv	s1,a3
   118b4:	00db09b3          	add	s3,s6,a3
   118b8:	ef1c                	sd	a5,24(a4)
   118ba:	eb98                	sd	a4,16(a5)
   118bc:	bd95                	j	11730 <_realloc_r+0x180>
   118be:	ff853783          	ld	a5,-8(a0)
   118c2:	9bf1                	andi	a5,a5,-4
   118c4:	94be                	add	s1,s1,a5
   118c6:	009b09b3          	add	s3,s6,s1
   118ca:	b59d                	j	11730 <_realloc_r+0x180>
   118cc:	85d6                	mv	a1,s5
   118ce:	c09ff0ef          	jal	ra,114d6 <memmove>
   118d2:	b3d1                	j	11696 <_realloc_r+0xe6>
   118d4:	0189b783          	ld	a5,24(s3)
   118d8:	0109b703          	ld	a4,16(s3)
   118dc:	ff848613          	addi	a2,s1,-8
   118e0:	04800693          	li	a3,72
   118e4:	ef1c                	sd	a5,24(a4)
   118e6:	eb98                	sd	a4,16(a5)
   118e8:	010c3703          	ld	a4,16(s8)
   118ec:	018c3783          	ld	a5,24(s8)
   118f0:	010c0913          	addi	s2,s8,16
   118f4:	017c09b3          	add	s3,s8,s7
   118f8:	ef1c                	sd	a5,24(a4)
   118fa:	eb98                	sd	a4,16(a5)
   118fc:	04c6ee63          	bltu	a3,a2,11958 <_realloc_r+0x3a8>
   11900:	02700693          	li	a3,39
   11904:	000ab703          	ld	a4,0(s5)
   11908:	87ca                	mv	a5,s2
   1190a:	e0c6f9e3          	bgeu	a3,a2,1171c <_realloc_r+0x16c>
   1190e:	00ec3823          	sd	a4,16(s8)
   11912:	008ab703          	ld	a4,8(s5)
   11916:	03700793          	li	a5,55
   1191a:	00ec3c23          	sd	a4,24(s8)
   1191e:	010ab703          	ld	a4,16(s5)
   11922:	dec7fae3          	bgeu	a5,a2,11716 <_realloc_r+0x166>
   11926:	02ec3023          	sd	a4,32(s8)
   1192a:	018ab703          	ld	a4,24(s5)
   1192e:	04800793          	li	a5,72
   11932:	02ec3423          	sd	a4,40(s8)
   11936:	020ab703          	ld	a4,32(s5)
   1193a:	06f61f63          	bne	a2,a5,119b8 <_realloc_r+0x408>
   1193e:	02ec3823          	sd	a4,48(s8)
   11942:	028ab703          	ld	a4,40(s5)
   11946:	040c0793          	addi	a5,s8,64
   1194a:	030a8a93          	addi	s5,s5,48
   1194e:	02ec3c23          	sd	a4,56(s8)
   11952:	000ab703          	ld	a4,0(s5)
   11956:	b3d9                	j	1171c <_realloc_r+0x16c>
   11958:	85d6                	mv	a1,s5
   1195a:	854a                	mv	a0,s2
   1195c:	b7bff0ef          	jal	ra,114d6 <memmove>
   11960:	8aca                	mv	s5,s2
   11962:	84de                	mv	s1,s7
   11964:	8b62                	mv	s6,s8
   11966:	b3e9                	j	11730 <_realloc_r+0x180>
   11968:	010ab703          	ld	a4,16(s5)
   1196c:	e918                	sd	a4,16(a0)
   1196e:	018ab703          	ld	a4,24(s5)
   11972:	ed18                	sd	a4,24(a0)
   11974:	00f60963          	beq	a2,a5,11986 <_realloc_r+0x3d6>
   11978:	020a8713          	addi	a4,s5,32
   1197c:	02050793          	addi	a5,a0,32
   11980:	020ab683          	ld	a3,32(s5)
   11984:	b321                	j	1168c <_realloc_r+0xdc>
   11986:	020ab683          	ld	a3,32(s5)
   1198a:	030a8713          	addi	a4,s5,48
   1198e:	03050793          	addi	a5,a0,48
   11992:	f114                	sd	a3,32(a0)
   11994:	028ab683          	ld	a3,40(s5)
   11998:	f514                	sd	a3,40(a0)
   1199a:	030ab683          	ld	a3,48(s5)
   1199e:	b1fd                	j	1168c <_realloc_r+0xdc>
   119a0:	010ab783          	ld	a5,16(s5)
   119a4:	02fc3023          	sd	a5,32(s8)
   119a8:	018ab783          	ld	a5,24(s5)
   119ac:	02fc3423          	sd	a5,40(s8)
   119b0:	020ab703          	ld	a4,32(s5)
   119b4:	f8d605e3          	beq	a2,a3,1193e <_realloc_r+0x38e>
   119b8:	030c0793          	addi	a5,s8,48
   119bc:	020a8a93          	addi	s5,s5,32
   119c0:	bbb1                	j	1171c <_realloc_r+0x16c>
   119c2:	85d6                	mv	a1,s5
   119c4:	854a                	mv	a0,s2
   119c6:	b11ff0ef          	jal	ra,114d6 <memmove>
   119ca:	b5b5                	j	11836 <_realloc_r+0x286>
   119cc:	010ab783          	ld	a5,16(s5)
   119d0:	02fc3023          	sd	a5,32(s8)
   119d4:	018ab783          	ld	a5,24(s5)
   119d8:	02fc3423          	sd	a5,40(s8)
   119dc:	020ab703          	ld	a4,32(s5)
   119e0:	00d60763          	beq	a2,a3,119ee <_realloc_r+0x43e>
   119e4:	030c0793          	addi	a5,s8,48
   119e8:	020a8a93          	addi	s5,s5,32
   119ec:	bd35                	j	11828 <_realloc_r+0x278>
   119ee:	02ec3823          	sd	a4,48(s8)
   119f2:	028ab703          	ld	a4,40(s5)
   119f6:	040c0793          	addi	a5,s8,64
   119fa:	030a8a93          	addi	s5,s5,48
   119fe:	02ec3c23          	sd	a4,56(s8)
   11a02:	000ab703          	ld	a4,0(s5)
   11a06:	b50d                	j	11828 <_realloc_r+0x278>

0000000000011a08 <_sbrk_r>:
   11a08:	1141                	addi	sp,sp,-16
   11a0a:	e022                	sd	s0,0(sp)
   11a0c:	842a                	mv	s0,a0
   11a0e:	852e                	mv	a0,a1
   11a10:	00003797          	auipc	a5,0x3
   11a14:	de07a623          	sw	zero,-532(a5) # 147fc <errno>
   11a18:	e406                	sd	ra,8(sp)
   11a1a:	477000ef          	jal	ra,12690 <_sbrk>
   11a1e:	57fd                	li	a5,-1
   11a20:	00f50663          	beq	a0,a5,11a2c <_sbrk_r+0x24>
   11a24:	60a2                	ld	ra,8(sp)
   11a26:	6402                	ld	s0,0(sp)
   11a28:	0141                	addi	sp,sp,16
   11a2a:	8082                	ret
   11a2c:	00003797          	auipc	a5,0x3
   11a30:	dd078793          	addi	a5,a5,-560 # 147fc <errno>
   11a34:	439c                	lw	a5,0(a5)
   11a36:	d7fd                	beqz	a5,11a24 <_sbrk_r+0x1c>
   11a38:	c01c                	sw	a5,0(s0)
   11a3a:	60a2                	ld	ra,8(sp)
   11a3c:	6402                	ld	s0,0(sp)
   11a3e:	0141                	addi	sp,sp,16
   11a40:	8082                	ret

0000000000011a42 <__sread>:
   11a42:	1141                	addi	sp,sp,-16
   11a44:	e022                	sd	s0,0(sp)
   11a46:	842e                	mv	s0,a1
   11a48:	01259583          	lh	a1,18(a1)
   11a4c:	e406                	sd	ra,8(sp)
   11a4e:	18f000ef          	jal	ra,123dc <_read_r>
   11a52:	00054963          	bltz	a0,11a64 <__sread+0x22>
   11a56:	685c                	ld	a5,144(s0)
   11a58:	60a2                	ld	ra,8(sp)
   11a5a:	97aa                	add	a5,a5,a0
   11a5c:	e85c                	sd	a5,144(s0)
   11a5e:	6402                	ld	s0,0(sp)
   11a60:	0141                	addi	sp,sp,16
   11a62:	8082                	ret
   11a64:	01045783          	lhu	a5,16(s0)
   11a68:	777d                	lui	a4,0xfffff
   11a6a:	177d                	addi	a4,a4,-1
   11a6c:	8ff9                	and	a5,a5,a4
   11a6e:	00f41823          	sh	a5,16(s0)
   11a72:	60a2                	ld	ra,8(sp)
   11a74:	6402                	ld	s0,0(sp)
   11a76:	0141                	addi	sp,sp,16
   11a78:	8082                	ret

0000000000011a7a <__seofread>:
   11a7a:	4501                	li	a0,0
   11a7c:	8082                	ret

0000000000011a7e <__swrite>:
   11a7e:	01059783          	lh	a5,16(a1)
   11a82:	7179                	addi	sp,sp,-48
   11a84:	f022                	sd	s0,32(sp)
   11a86:	ec26                	sd	s1,24(sp)
   11a88:	e84a                	sd	s2,16(sp)
   11a8a:	e44e                	sd	s3,8(sp)
   11a8c:	f406                	sd	ra,40(sp)
   11a8e:	1007f713          	andi	a4,a5,256
   11a92:	842e                	mv	s0,a1
   11a94:	84aa                	mv	s1,a0
   11a96:	8932                	mv	s2,a2
   11a98:	89b6                	mv	s3,a3
   11a9a:	01259583          	lh	a1,18(a1)
   11a9e:	e305                	bnez	a4,11abe <__swrite+0x40>
   11aa0:	777d                	lui	a4,0xfffff
   11aa2:	177d                	addi	a4,a4,-1
   11aa4:	8ff9                	and	a5,a5,a4
   11aa6:	00f41823          	sh	a5,16(s0)
   11aaa:	7402                	ld	s0,32(sp)
   11aac:	70a2                	ld	ra,40(sp)
   11aae:	86ce                	mv	a3,s3
   11ab0:	864a                	mv	a2,s2
   11ab2:	69a2                	ld	s3,8(sp)
   11ab4:	6942                	ld	s2,16(sp)
   11ab6:	8526                	mv	a0,s1
   11ab8:	64e2                	ld	s1,24(sp)
   11aba:	6145                	addi	sp,sp,48
   11abc:	a8b1                	j	11b18 <_write_r>
   11abe:	4689                	li	a3,2
   11ac0:	4601                	li	a2,0
   11ac2:	79c000ef          	jal	ra,1225e <_lseek_r>
   11ac6:	01041783          	lh	a5,16(s0)
   11aca:	01241583          	lh	a1,18(s0)
   11ace:	bfc9                	j	11aa0 <__swrite+0x22>

0000000000011ad0 <__sseek>:
   11ad0:	1141                	addi	sp,sp,-16
   11ad2:	e022                	sd	s0,0(sp)
   11ad4:	842e                	mv	s0,a1
   11ad6:	01259583          	lh	a1,18(a1)
   11ada:	e406                	sd	ra,8(sp)
   11adc:	782000ef          	jal	ra,1225e <_lseek_r>
   11ae0:	57fd                	li	a5,-1
   11ae2:	00f50d63          	beq	a0,a5,11afc <__sseek+0x2c>
   11ae6:	01045783          	lhu	a5,16(s0)
   11aea:	6705                	lui	a4,0x1
   11aec:	e848                	sd	a0,144(s0)
   11aee:	8fd9                	or	a5,a5,a4
   11af0:	00f41823          	sh	a5,16(s0)
   11af4:	60a2                	ld	ra,8(sp)
   11af6:	6402                	ld	s0,0(sp)
   11af8:	0141                	addi	sp,sp,16
   11afa:	8082                	ret
   11afc:	01045783          	lhu	a5,16(s0)
   11b00:	777d                	lui	a4,0xfffff
   11b02:	177d                	addi	a4,a4,-1
   11b04:	8ff9                	and	a5,a5,a4
   11b06:	00f41823          	sh	a5,16(s0)
   11b0a:	60a2                	ld	ra,8(sp)
   11b0c:	6402                	ld	s0,0(sp)
   11b0e:	0141                	addi	sp,sp,16
   11b10:	8082                	ret

0000000000011b12 <__sclose>:
   11b12:	01259583          	lh	a1,18(a1)
   11b16:	aa1d                	j	11c4c <_close_r>

0000000000011b18 <_write_r>:
   11b18:	87ae                	mv	a5,a1
   11b1a:	1141                	addi	sp,sp,-16
   11b1c:	e022                	sd	s0,0(sp)
   11b1e:	85b2                	mv	a1,a2
   11b20:	842a                	mv	s0,a0
   11b22:	8636                	mv	a2,a3
   11b24:	853e                	mv	a0,a5
   11b26:	e406                	sd	ra,8(sp)
   11b28:	00003797          	auipc	a5,0x3
   11b2c:	cc07aa23          	sw	zero,-812(a5) # 147fc <errno>
   11b30:	3cb000ef          	jal	ra,126fa <_write>
   11b34:	57fd                	li	a5,-1
   11b36:	00f50663          	beq	a0,a5,11b42 <_write_r+0x2a>
   11b3a:	60a2                	ld	ra,8(sp)
   11b3c:	6402                	ld	s0,0(sp)
   11b3e:	0141                	addi	sp,sp,16
   11b40:	8082                	ret
   11b42:	00003797          	auipc	a5,0x3
   11b46:	cba78793          	addi	a5,a5,-838 # 147fc <errno>
   11b4a:	439c                	lw	a5,0(a5)
   11b4c:	d7fd                	beqz	a5,11b3a <_write_r+0x22>
   11b4e:	c01c                	sw	a5,0(s0)
   11b50:	60a2                	ld	ra,8(sp)
   11b52:	6402                	ld	s0,0(sp)
   11b54:	0141                	addi	sp,sp,16
   11b56:	8082                	ret

0000000000011b58 <__swsetup_r>:
   11b58:	74818793          	addi	a5,gp,1864 # 14748 <_impure_ptr>
   11b5c:	639c                	ld	a5,0(a5)
   11b5e:	1101                	addi	sp,sp,-32
   11b60:	e822                	sd	s0,16(sp)
   11b62:	e426                	sd	s1,8(sp)
   11b64:	ec06                	sd	ra,24(sp)
   11b66:	84aa                	mv	s1,a0
   11b68:	842e                	mv	s0,a1
   11b6a:	c399                	beqz	a5,11b70 <__swsetup_r+0x18>
   11b6c:	4bb8                	lw	a4,80(a5)
   11b6e:	cf29                	beqz	a4,11bc8 <__swsetup_r+0x70>
   11b70:	01041703          	lh	a4,16(s0)
   11b74:	03071793          	slli	a5,a4,0x30
   11b78:	93c1                	srli	a5,a5,0x30
   11b7a:	0087f693          	andi	a3,a5,8
   11b7e:	c2a5                	beqz	a3,11bde <__swsetup_r+0x86>
   11b80:	6c14                	ld	a3,24(s0)
   11b82:	cabd                	beqz	a3,11bf8 <__swsetup_r+0xa0>
   11b84:	0017f713          	andi	a4,a5,1
   11b88:	cf11                	beqz	a4,11ba4 <__swsetup_r+0x4c>
   11b8a:	501c                	lw	a5,32(s0)
   11b8c:	00042623          	sw	zero,12(s0)
   11b90:	4501                	li	a0,0
   11b92:	40f007bb          	negw	a5,a5
   11b96:	d41c                	sw	a5,40(s0)
   11b98:	ce89                	beqz	a3,11bb2 <__swsetup_r+0x5a>
   11b9a:	60e2                	ld	ra,24(sp)
   11b9c:	6442                	ld	s0,16(sp)
   11b9e:	64a2                	ld	s1,8(sp)
   11ba0:	6105                	addi	sp,sp,32
   11ba2:	8082                	ret
   11ba4:	8b89                	andi	a5,a5,2
   11ba6:	4701                	li	a4,0
   11ba8:	e391                	bnez	a5,11bac <__swsetup_r+0x54>
   11baa:	5018                	lw	a4,32(s0)
   11bac:	c458                	sw	a4,12(s0)
   11bae:	4501                	li	a0,0
   11bb0:	f6ed                	bnez	a3,11b9a <__swsetup_r+0x42>
   11bb2:	01041783          	lh	a5,16(s0)
   11bb6:	0807f713          	andi	a4,a5,128
   11bba:	d365                	beqz	a4,11b9a <__swsetup_r+0x42>
   11bbc:	0407e793          	ori	a5,a5,64
   11bc0:	00f41823          	sh	a5,16(s0)
   11bc4:	557d                	li	a0,-1
   11bc6:	bfd1                	j	11b9a <__swsetup_r+0x42>
   11bc8:	853e                	mv	a0,a5
   11bca:	ca3fe0ef          	jal	ra,1086c <__sinit>
   11bce:	01041703          	lh	a4,16(s0)
   11bd2:	03071793          	slli	a5,a4,0x30
   11bd6:	93c1                	srli	a5,a5,0x30
   11bd8:	0087f693          	andi	a3,a5,8
   11bdc:	f2d5                	bnez	a3,11b80 <__swsetup_r+0x28>
   11bde:	0107f693          	andi	a3,a5,16
   11be2:	cea9                	beqz	a3,11c3c <__swsetup_r+0xe4>
   11be4:	8b91                	andi	a5,a5,4
   11be6:	e79d                	bnez	a5,11c14 <__swsetup_r+0xbc>
   11be8:	6c14                	ld	a3,24(s0)
   11bea:	00876793          	ori	a5,a4,8
   11bee:	00f41823          	sh	a5,16(s0)
   11bf2:	17c2                	slli	a5,a5,0x30
   11bf4:	93c1                	srli	a5,a5,0x30
   11bf6:	f6d9                	bnez	a3,11b84 <__swsetup_r+0x2c>
   11bf8:	2807f713          	andi	a4,a5,640
   11bfc:	20000613          	li	a2,512
   11c00:	f8c702e3          	beq	a4,a2,11b84 <__swsetup_r+0x2c>
   11c04:	85a2                	mv	a1,s0
   11c06:	8526                	mv	a0,s1
   11c08:	718000ef          	jal	ra,12320 <__smakebuf_r>
   11c0c:	01045783          	lhu	a5,16(s0)
   11c10:	6c14                	ld	a3,24(s0)
   11c12:	bf8d                	j	11b84 <__swsetup_r+0x2c>
   11c14:	6c2c                	ld	a1,88(s0)
   11c16:	cd81                	beqz	a1,11c2e <__swsetup_r+0xd6>
   11c18:	07440793          	addi	a5,s0,116
   11c1c:	00f58763          	beq	a1,a5,11c2a <__swsetup_r+0xd2>
   11c20:	8526                	mv	a0,s1
   11c22:	3d2000ef          	jal	ra,11ff4 <_free_r>
   11c26:	01041703          	lh	a4,16(s0)
   11c2a:	04043c23          	sd	zero,88(s0)
   11c2e:	6c14                	ld	a3,24(s0)
   11c30:	fdb77713          	andi	a4,a4,-37
   11c34:	00042423          	sw	zero,8(s0)
   11c38:	e014                	sd	a3,0(s0)
   11c3a:	bf45                	j	11bea <__swsetup_r+0x92>
   11c3c:	47a5                	li	a5,9
   11c3e:	c09c                	sw	a5,0(s1)
   11c40:	04076713          	ori	a4,a4,64
   11c44:	00e41823          	sh	a4,16(s0)
   11c48:	557d                	li	a0,-1
   11c4a:	bf81                	j	11b9a <__swsetup_r+0x42>

0000000000011c4c <_close_r>:
   11c4c:	1141                	addi	sp,sp,-16
   11c4e:	e022                	sd	s0,0(sp)
   11c50:	842a                	mv	s0,a0
   11c52:	852e                	mv	a0,a1
   11c54:	00003797          	auipc	a5,0x3
   11c58:	ba07a423          	sw	zero,-1112(a5) # 147fc <errno>
   11c5c:	e406                	sd	ra,8(sp)
   11c5e:	0ff000ef          	jal	ra,1255c <_close>
   11c62:	57fd                	li	a5,-1
   11c64:	00f50663          	beq	a0,a5,11c70 <_close_r+0x24>
   11c68:	60a2                	ld	ra,8(sp)
   11c6a:	6402                	ld	s0,0(sp)
   11c6c:	0141                	addi	sp,sp,16
   11c6e:	8082                	ret
   11c70:	00003797          	auipc	a5,0x3
   11c74:	b8c78793          	addi	a5,a5,-1140 # 147fc <errno>
   11c78:	439c                	lw	a5,0(a5)
   11c7a:	d7fd                	beqz	a5,11c68 <_close_r+0x1c>
   11c7c:	c01c                	sw	a5,0(s0)
   11c7e:	60a2                	ld	ra,8(sp)
   11c80:	6402                	ld	s0,0(sp)
   11c82:	0141                	addi	sp,sp,16
   11c84:	8082                	ret

0000000000011c86 <_fclose_r>:
   11c86:	1101                	addi	sp,sp,-32
   11c88:	ec06                	sd	ra,24(sp)
   11c8a:	e822                	sd	s0,16(sp)
   11c8c:	e426                	sd	s1,8(sp)
   11c8e:	e04a                	sd	s2,0(sp)
   11c90:	c989                	beqz	a1,11ca2 <_fclose_r+0x1c>
   11c92:	84aa                	mv	s1,a0
   11c94:	842e                	mv	s0,a1
   11c96:	c119                	beqz	a0,11c9c <_fclose_r+0x16>
   11c98:	493c                	lw	a5,80(a0)
   11c9a:	cfa5                	beqz	a5,11d12 <_fclose_r+0x8c>
   11c9c:	01041783          	lh	a5,16(s0)
   11ca0:	eb89                	bnez	a5,11cb2 <_fclose_r+0x2c>
   11ca2:	60e2                	ld	ra,24(sp)
   11ca4:	6442                	ld	s0,16(sp)
   11ca6:	4901                	li	s2,0
   11ca8:	854a                	mv	a0,s2
   11caa:	64a2                	ld	s1,8(sp)
   11cac:	6902                	ld	s2,0(sp)
   11cae:	6105                	addi	sp,sp,32
   11cb0:	8082                	ret
   11cb2:	85a2                	mv	a1,s0
   11cb4:	8526                	mv	a0,s1
   11cb6:	088000ef          	jal	ra,11d3e <__sflush_r>
   11cba:	683c                	ld	a5,80(s0)
   11cbc:	892a                	mv	s2,a0
   11cbe:	c791                	beqz	a5,11cca <_fclose_r+0x44>
   11cc0:	780c                	ld	a1,48(s0)
   11cc2:	8526                	mv	a0,s1
   11cc4:	9782                	jalr	a5
   11cc6:	04054c63          	bltz	a0,11d1e <_fclose_r+0x98>
   11cca:	01045783          	lhu	a5,16(s0)
   11cce:	0807f793          	andi	a5,a5,128
   11cd2:	efa1                	bnez	a5,11d2a <_fclose_r+0xa4>
   11cd4:	6c2c                	ld	a1,88(s0)
   11cd6:	c991                	beqz	a1,11cea <_fclose_r+0x64>
   11cd8:	07440793          	addi	a5,s0,116
   11cdc:	00f58563          	beq	a1,a5,11ce6 <_fclose_r+0x60>
   11ce0:	8526                	mv	a0,s1
   11ce2:	312000ef          	jal	ra,11ff4 <_free_r>
   11ce6:	04043c23          	sd	zero,88(s0)
   11cea:	7c2c                	ld	a1,120(s0)
   11cec:	c591                	beqz	a1,11cf8 <_fclose_r+0x72>
   11cee:	8526                	mv	a0,s1
   11cf0:	304000ef          	jal	ra,11ff4 <_free_r>
   11cf4:	06043c23          	sd	zero,120(s0)
   11cf8:	b7dfe0ef          	jal	ra,10874 <__sfp_lock_acquire>
   11cfc:	00041823          	sh	zero,16(s0)
   11d00:	b77fe0ef          	jal	ra,10876 <__sfp_lock_release>
   11d04:	60e2                	ld	ra,24(sp)
   11d06:	6442                	ld	s0,16(sp)
   11d08:	854a                	mv	a0,s2
   11d0a:	64a2                	ld	s1,8(sp)
   11d0c:	6902                	ld	s2,0(sp)
   11d0e:	6105                	addi	sp,sp,32
   11d10:	8082                	ret
   11d12:	b5bfe0ef          	jal	ra,1086c <__sinit>
   11d16:	01041783          	lh	a5,16(s0)
   11d1a:	d7c1                	beqz	a5,11ca2 <_fclose_r+0x1c>
   11d1c:	bf59                	j	11cb2 <_fclose_r+0x2c>
   11d1e:	01045783          	lhu	a5,16(s0)
   11d22:	597d                	li	s2,-1
   11d24:	0807f793          	andi	a5,a5,128
   11d28:	d7d5                	beqz	a5,11cd4 <_fclose_r+0x4e>
   11d2a:	6c0c                	ld	a1,24(s0)
   11d2c:	8526                	mv	a0,s1
   11d2e:	2c6000ef          	jal	ra,11ff4 <_free_r>
   11d32:	b74d                	j	11cd4 <_fclose_r+0x4e>

0000000000011d34 <fclose>:
   11d34:	74818793          	addi	a5,gp,1864 # 14748 <_impure_ptr>
   11d38:	85aa                	mv	a1,a0
   11d3a:	6388                	ld	a0,0(a5)
   11d3c:	b7a9                	j	11c86 <_fclose_r>

0000000000011d3e <__sflush_r>:
   11d3e:	01059783          	lh	a5,16(a1)
   11d42:	7179                	addi	sp,sp,-48
   11d44:	f022                	sd	s0,32(sp)
   11d46:	03079713          	slli	a4,a5,0x30
   11d4a:	9341                	srli	a4,a4,0x30
   11d4c:	e44e                	sd	s3,8(sp)
   11d4e:	f406                	sd	ra,40(sp)
   11d50:	ec26                	sd	s1,24(sp)
   11d52:	e84a                	sd	s2,16(sp)
   11d54:	00877693          	andi	a3,a4,8
   11d58:	842e                	mv	s0,a1
   11d5a:	89aa                	mv	s3,a0
   11d5c:	eadd                	bnez	a3,11e12 <__sflush_r+0xd4>
   11d5e:	6705                	lui	a4,0x1
   11d60:	80070713          	addi	a4,a4,-2048 # 800 <register_fini-0xf8b0>
   11d64:	4594                	lw	a3,8(a1)
   11d66:	8fd9                	or	a5,a5,a4
   11d68:	00f59823          	sh	a5,16(a1)
   11d6c:	0ed05e63          	blez	a3,11e68 <__sflush_r+0x12a>
   11d70:	6438                	ld	a4,72(s0)
   11d72:	cb41                	beqz	a4,11e02 <__sflush_r+0xc4>
   11d74:	17c2                	slli	a5,a5,0x30
   11d76:	93c1                	srli	a5,a5,0x30
   11d78:	0009a483          	lw	s1,0(s3)
   11d7c:	03379693          	slli	a3,a5,0x33
   11d80:	0009a023          	sw	zero,0(s3)
   11d84:	780c                	ld	a1,48(s0)
   11d86:	0e06c563          	bltz	a3,11e70 <__sflush_r+0x132>
   11d8a:	4601                	li	a2,0
   11d8c:	4685                	li	a3,1
   11d8e:	854e                	mv	a0,s3
   11d90:	9702                	jalr	a4
   11d92:	57fd                	li	a5,-1
   11d94:	862a                	mv	a2,a0
   11d96:	10f50563          	beq	a0,a5,11ea0 <__sflush_r+0x162>
   11d9a:	01045783          	lhu	a5,16(s0)
   11d9e:	6438                	ld	a4,72(s0)
   11da0:	780c                	ld	a1,48(s0)
   11da2:	8b91                	andi	a5,a5,4
   11da4:	c799                	beqz	a5,11db2 <__sflush_r+0x74>
   11da6:	4414                	lw	a3,8(s0)
   11da8:	6c3c                	ld	a5,88(s0)
   11daa:	8e15                	sub	a2,a2,a3
   11dac:	c399                	beqz	a5,11db2 <__sflush_r+0x74>
   11dae:	583c                	lw	a5,112(s0)
   11db0:	8e1d                	sub	a2,a2,a5
   11db2:	4681                	li	a3,0
   11db4:	854e                	mv	a0,s3
   11db6:	9702                	jalr	a4
   11db8:	57fd                	li	a5,-1
   11dba:	0af51d63          	bne	a0,a5,11e74 <__sflush_r+0x136>
   11dbe:	0009a703          	lw	a4,0(s3)
   11dc2:	01041783          	lh	a5,16(s0)
   11dc6:	cb7d                	beqz	a4,11ebc <__sflush_r+0x17e>
   11dc8:	46f5                	li	a3,29
   11dca:	00d70563          	beq	a4,a3,11dd4 <__sflush_r+0x96>
   11dce:	46d9                	li	a3,22
   11dd0:	0ed71c63          	bne	a4,a3,11ec8 <__sflush_r+0x18a>
   11dd4:	6c14                	ld	a3,24(s0)
   11dd6:	777d                	lui	a4,0xfffff
   11dd8:	7ff70713          	addi	a4,a4,2047 # fffffffffffff7ff <__BSS_END__+0xfffffffffffeafff>
   11ddc:	8ff9                	and	a5,a5,a4
   11dde:	00f41823          	sh	a5,16(s0)
   11de2:	00042423          	sw	zero,8(s0)
   11de6:	e014                	sd	a3,0(s0)
   11de8:	6c2c                	ld	a1,88(s0)
   11dea:	0099a023          	sw	s1,0(s3)
   11dee:	c991                	beqz	a1,11e02 <__sflush_r+0xc4>
   11df0:	07440793          	addi	a5,s0,116
   11df4:	00f58563          	beq	a1,a5,11dfe <__sflush_r+0xc0>
   11df8:	854e                	mv	a0,s3
   11dfa:	1fa000ef          	jal	ra,11ff4 <_free_r>
   11dfe:	04043c23          	sd	zero,88(s0)
   11e02:	4501                	li	a0,0
   11e04:	70a2                	ld	ra,40(sp)
   11e06:	7402                	ld	s0,32(sp)
   11e08:	64e2                	ld	s1,24(sp)
   11e0a:	6942                	ld	s2,16(sp)
   11e0c:	69a2                	ld	s3,8(sp)
   11e0e:	6145                	addi	sp,sp,48
   11e10:	8082                	ret
   11e12:	0185b903          	ld	s2,24(a1)
   11e16:	fe0906e3          	beqz	s2,11e02 <__sflush_r+0xc4>
   11e1a:	6184                	ld	s1,0(a1)
   11e1c:	8b0d                	andi	a4,a4,3
   11e1e:	0125b023          	sd	s2,0(a1)
   11e22:	412484bb          	subw	s1,s1,s2
   11e26:	4781                	li	a5,0
   11e28:	e311                	bnez	a4,11e2c <__sflush_r+0xee>
   11e2a:	519c                	lw	a5,32(a1)
   11e2c:	c45c                	sw	a5,12(s0)
   11e2e:	00904663          	bgtz	s1,11e3a <__sflush_r+0xfc>
   11e32:	bfc1                	j	11e02 <__sflush_r+0xc4>
   11e34:	992a                	add	s2,s2,a0
   11e36:	fc9056e3          	blez	s1,11e02 <__sflush_r+0xc4>
   11e3a:	603c                	ld	a5,64(s0)
   11e3c:	780c                	ld	a1,48(s0)
   11e3e:	86a6                	mv	a3,s1
   11e40:	864a                	mv	a2,s2
   11e42:	854e                	mv	a0,s3
   11e44:	9782                	jalr	a5
   11e46:	9c89                	subw	s1,s1,a0
   11e48:	fea046e3          	bgtz	a0,11e34 <__sflush_r+0xf6>
   11e4c:	01045783          	lhu	a5,16(s0)
   11e50:	70a2                	ld	ra,40(sp)
   11e52:	64e2                	ld	s1,24(sp)
   11e54:	0407e793          	ori	a5,a5,64
   11e58:	00f41823          	sh	a5,16(s0)
   11e5c:	7402                	ld	s0,32(sp)
   11e5e:	6942                	ld	s2,16(sp)
   11e60:	69a2                	ld	s3,8(sp)
   11e62:	557d                	li	a0,-1
   11e64:	6145                	addi	sp,sp,48
   11e66:	8082                	ret
   11e68:	59b8                	lw	a4,112(a1)
   11e6a:	f0e043e3          	bgtz	a4,11d70 <__sflush_r+0x32>
   11e6e:	bf51                	j	11e02 <__sflush_r+0xc4>
   11e70:	6850                	ld	a2,144(s0)
   11e72:	bf05                	j	11da2 <__sflush_r+0x64>
   11e74:	01045783          	lhu	a5,16(s0)
   11e78:	777d                	lui	a4,0xfffff
   11e7a:	7ff70713          	addi	a4,a4,2047 # fffffffffffff7ff <__BSS_END__+0xfffffffffffeafff>
   11e7e:	8ff9                	and	a5,a5,a4
   11e80:	6c14                	ld	a3,24(s0)
   11e82:	0107979b          	slliw	a5,a5,0x10
   11e86:	4107d79b          	sraiw	a5,a5,0x10
   11e8a:	00f41823          	sh	a5,16(s0)
   11e8e:	00042423          	sw	zero,8(s0)
   11e92:	e014                	sd	a3,0(s0)
   11e94:	03379713          	slli	a4,a5,0x33
   11e98:	f40758e3          	bgez	a4,11de8 <__sflush_r+0xaa>
   11e9c:	e848                	sd	a0,144(s0)
   11e9e:	b7a9                	j	11de8 <__sflush_r+0xaa>
   11ea0:	0009a783          	lw	a5,0(s3)
   11ea4:	ee078be3          	beqz	a5,11d9a <__sflush_r+0x5c>
   11ea8:	4775                	li	a4,29
   11eaa:	00e78563          	beq	a5,a4,11eb4 <__sflush_r+0x176>
   11eae:	4759                	li	a4,22
   11eb0:	f8e79ee3          	bne	a5,a4,11e4c <__sflush_r+0x10e>
   11eb4:	0099a023          	sw	s1,0(s3)
   11eb8:	4501                	li	a0,0
   11eba:	b7a9                	j	11e04 <__sflush_r+0xc6>
   11ebc:	777d                	lui	a4,0xfffff
   11ebe:	7ff70713          	addi	a4,a4,2047 # fffffffffffff7ff <__BSS_END__+0xfffffffffffeafff>
   11ec2:	6c14                	ld	a3,24(s0)
   11ec4:	8ff9                	and	a5,a5,a4
   11ec6:	b7d1                	j	11e8a <__sflush_r+0x14c>
   11ec8:	0407e793          	ori	a5,a5,64
   11ecc:	00f41823          	sh	a5,16(s0)
   11ed0:	557d                	li	a0,-1
   11ed2:	bf0d                	j	11e04 <__sflush_r+0xc6>

0000000000011ed4 <_fflush_r>:
   11ed4:	1101                	addi	sp,sp,-32
   11ed6:	e822                	sd	s0,16(sp)
   11ed8:	ec06                	sd	ra,24(sp)
   11eda:	842a                	mv	s0,a0
   11edc:	c119                	beqz	a0,11ee2 <_fflush_r+0xe>
   11ede:	493c                	lw	a5,80(a0)
   11ee0:	cb89                	beqz	a5,11ef2 <_fflush_r+0x1e>
   11ee2:	01059783          	lh	a5,16(a1)
   11ee6:	ef89                	bnez	a5,11f00 <_fflush_r+0x2c>
   11ee8:	60e2                	ld	ra,24(sp)
   11eea:	6442                	ld	s0,16(sp)
   11eec:	4501                	li	a0,0
   11eee:	6105                	addi	sp,sp,32
   11ef0:	8082                	ret
   11ef2:	e42e                	sd	a1,8(sp)
   11ef4:	979fe0ef          	jal	ra,1086c <__sinit>
   11ef8:	65a2                	ld	a1,8(sp)
   11efa:	01059783          	lh	a5,16(a1)
   11efe:	d7ed                	beqz	a5,11ee8 <_fflush_r+0x14>
   11f00:	8522                	mv	a0,s0
   11f02:	6442                	ld	s0,16(sp)
   11f04:	60e2                	ld	ra,24(sp)
   11f06:	6105                	addi	sp,sp,32
   11f08:	bd1d                	j	11d3e <__sflush_r>

0000000000011f0a <fflush>:
   11f0a:	85aa                	mv	a1,a0
   11f0c:	c509                	beqz	a0,11f16 <fflush+0xc>
   11f0e:	74818793          	addi	a5,gp,1864 # 14748 <_impure_ptr>
   11f12:	6388                	ld	a0,0(a5)
   11f14:	b7c1                	j	11ed4 <_fflush_r>
   11f16:	73818793          	addi	a5,gp,1848 # 14738 <_global_impure_ptr>
   11f1a:	6388                	ld	a0,0(a5)
   11f1c:	00000597          	auipc	a1,0x0
   11f20:	fb858593          	addi	a1,a1,-72 # 11ed4 <_fflush_r>
   11f24:	d2ffe06f          	j	10c52 <_fwalk_reent>

0000000000011f28 <_malloc_trim_r>:
   11f28:	7179                	addi	sp,sp,-48
   11f2a:	f022                	sd	s0,32(sp)
   11f2c:	ec26                	sd	s1,24(sp)
   11f2e:	e84a                	sd	s2,16(sp)
   11f30:	e44e                	sd	s3,8(sp)
   11f32:	842e                	mv	s0,a1
   11f34:	f406                	sd	ra,40(sp)
   11f36:	00002997          	auipc	s3,0x2
   11f3a:	fda98993          	addi	s3,s3,-38 # 13f10 <__malloc_av_>
   11f3e:	892a                	mv	s2,a0
   11f40:	e6cff0ef          	jal	ra,115ac <__malloc_lock>
   11f44:	0109b683          	ld	a3,16(s3)
   11f48:	6705                	lui	a4,0x1
   11f4a:	fdf70793          	addi	a5,a4,-33 # fdf <register_fini-0xf0d1>
   11f4e:	6684                	ld	s1,8(a3)
   11f50:	40878433          	sub	s0,a5,s0
   11f54:	98f1                	andi	s1,s1,-4
   11f56:	9426                	add	s0,s0,s1
   11f58:	8031                	srli	s0,s0,0xc
   11f5a:	147d                	addi	s0,s0,-1
   11f5c:	0432                	slli	s0,s0,0xc
   11f5e:	00e44b63          	blt	s0,a4,11f74 <_malloc_trim_r+0x4c>
   11f62:	4581                	li	a1,0
   11f64:	854a                	mv	a0,s2
   11f66:	aa3ff0ef          	jal	ra,11a08 <_sbrk_r>
   11f6a:	0109b783          	ld	a5,16(s3)
   11f6e:	97a6                	add	a5,a5,s1
   11f70:	00f50d63          	beq	a0,a5,11f8a <_malloc_trim_r+0x62>
   11f74:	854a                	mv	a0,s2
   11f76:	e38ff0ef          	jal	ra,115ae <__malloc_unlock>
   11f7a:	70a2                	ld	ra,40(sp)
   11f7c:	7402                	ld	s0,32(sp)
   11f7e:	64e2                	ld	s1,24(sp)
   11f80:	6942                	ld	s2,16(sp)
   11f82:	69a2                	ld	s3,8(sp)
   11f84:	4501                	li	a0,0
   11f86:	6145                	addi	sp,sp,48
   11f88:	8082                	ret
   11f8a:	408005b3          	neg	a1,s0
   11f8e:	854a                	mv	a0,s2
   11f90:	a79ff0ef          	jal	ra,11a08 <_sbrk_r>
   11f94:	57fd                	li	a5,-1
   11f96:	02f50a63          	beq	a0,a5,11fca <_malloc_trim_r+0xa2>
   11f9a:	7b818793          	addi	a5,gp,1976 # 147b8 <__malloc_current_mallinfo>
   11f9e:	439c                	lw	a5,0(a5)
   11fa0:	0109b703          	ld	a4,16(s3)
   11fa4:	8c81                	sub	s1,s1,s0
   11fa6:	0014e493          	ori	s1,s1,1
   11faa:	4087843b          	subw	s0,a5,s0
   11fae:	854a                	mv	a0,s2
   11fb0:	e704                	sd	s1,8(a4)
   11fb2:	7a81ac23          	sw	s0,1976(gp) # 147b8 <__malloc_current_mallinfo>
   11fb6:	df8ff0ef          	jal	ra,115ae <__malloc_unlock>
   11fba:	70a2                	ld	ra,40(sp)
   11fbc:	7402                	ld	s0,32(sp)
   11fbe:	64e2                	ld	s1,24(sp)
   11fc0:	6942                	ld	s2,16(sp)
   11fc2:	69a2                	ld	s3,8(sp)
   11fc4:	4505                	li	a0,1
   11fc6:	6145                	addi	sp,sp,48
   11fc8:	8082                	ret
   11fca:	4581                	li	a1,0
   11fcc:	854a                	mv	a0,s2
   11fce:	a3bff0ef          	jal	ra,11a08 <_sbrk_r>
   11fd2:	0109b703          	ld	a4,16(s3)
   11fd6:	46fd                	li	a3,31
   11fd8:	40e507b3          	sub	a5,a0,a4
   11fdc:	f8f6dce3          	bge	a3,a5,11f74 <_malloc_trim_r+0x4c>
   11fe0:	75018693          	addi	a3,gp,1872 # 14750 <__malloc_sbrk_base>
   11fe4:	6294                	ld	a3,0(a3)
   11fe6:	0017e793          	ori	a5,a5,1
   11fea:	e71c                	sd	a5,8(a4)
   11fec:	8d15                	sub	a0,a0,a3
   11fee:	7aa1ac23          	sw	a0,1976(gp) # 147b8 <__malloc_current_mallinfo>
   11ff2:	b749                	j	11f74 <_malloc_trim_r+0x4c>

0000000000011ff4 <_free_r>:
   11ff4:	c9e5                	beqz	a1,120e4 <_free_r+0xf0>
   11ff6:	1101                	addi	sp,sp,-32
   11ff8:	e822                	sd	s0,16(sp)
   11ffa:	e426                	sd	s1,8(sp)
   11ffc:	842e                	mv	s0,a1
   11ffe:	84aa                	mv	s1,a0
   12000:	ec06                	sd	ra,24(sp)
   12002:	daaff0ef          	jal	ra,115ac <__malloc_lock>
   12006:	ff843583          	ld	a1,-8(s0)
   1200a:	ff040713          	addi	a4,s0,-16
   1200e:	00002517          	auipc	a0,0x2
   12012:	f0250513          	addi	a0,a0,-254 # 13f10 <__malloc_av_>
   12016:	ffe5f793          	andi	a5,a1,-2
   1201a:	00f70633          	add	a2,a4,a5
   1201e:	6614                	ld	a3,8(a2)
   12020:	01053803          	ld	a6,16(a0)
   12024:	9af1                	andi	a3,a3,-4
   12026:	12c80d63          	beq	a6,a2,12160 <_free_r+0x16c>
   1202a:	e614                	sd	a3,8(a2)
   1202c:	8985                	andi	a1,a1,1
   1202e:	00d60833          	add	a6,a2,a3
   12032:	e1d1                	bnez	a1,120b6 <_free_r+0xc2>
   12034:	ff043303          	ld	t1,-16(s0)
   12038:	00883583          	ld	a1,8(a6)
   1203c:	00002897          	auipc	a7,0x2
   12040:	ee488893          	addi	a7,a7,-284 # 13f20 <__malloc_av_+0x10>
   12044:	40670733          	sub	a4,a4,t1
   12048:	01073803          	ld	a6,16(a4)
   1204c:	979a                	add	a5,a5,t1
   1204e:	8985                	andi	a1,a1,1
   12050:	0f180b63          	beq	a6,a7,12146 <_free_r+0x152>
   12054:	01873303          	ld	t1,24(a4)
   12058:	00683c23          	sd	t1,24(a6)
   1205c:	01033823          	sd	a6,16(t1) # 1015e <waste_detector+0x6>
   12060:	16058063          	beqz	a1,121c0 <_free_r+0x1cc>
   12064:	0017e693          	ori	a3,a5,1
   12068:	e714                	sd	a3,8(a4)
   1206a:	e21c                	sd	a5,0(a2)
   1206c:	1ff00693          	li	a3,511
   12070:	08f6e463          	bltu	a3,a5,120f8 <_free_r+0x104>
   12074:	838d                	srli	a5,a5,0x3
   12076:	2781                	sext.w	a5,a5
   12078:	0017869b          	addiw	a3,a5,1
   1207c:	0016969b          	slliw	a3,a3,0x1
   12080:	068e                	slli	a3,a3,0x3
   12082:	650c                	ld	a1,8(a0)
   12084:	9536                	add	a0,a0,a3
   12086:	6110                	ld	a2,0(a0)
   12088:	4685                	li	a3,1
   1208a:	4027d79b          	sraiw	a5,a5,0x2
   1208e:	00f697b3          	sll	a5,a3,a5
   12092:	8fcd                	or	a5,a5,a1
   12094:	ff050693          	addi	a3,a0,-16
   12098:	ef14                	sd	a3,24(a4)
   1209a:	eb10                	sd	a2,16(a4)
   1209c:	00002697          	auipc	a3,0x2
   120a0:	e6f6be23          	sd	a5,-388(a3) # 13f18 <__malloc_av_+0x8>
   120a4:	e118                	sd	a4,0(a0)
   120a6:	ee18                	sd	a4,24(a2)
   120a8:	6442                	ld	s0,16(sp)
   120aa:	60e2                	ld	ra,24(sp)
   120ac:	8526                	mv	a0,s1
   120ae:	64a2                	ld	s1,8(sp)
   120b0:	6105                	addi	sp,sp,32
   120b2:	cfcff06f          	j	115ae <__malloc_unlock>
   120b6:	00883583          	ld	a1,8(a6)
   120ba:	8985                	andi	a1,a1,1
   120bc:	e58d                	bnez	a1,120e6 <_free_r+0xf2>
   120be:	97b6                	add	a5,a5,a3
   120c0:	00002897          	auipc	a7,0x2
   120c4:	e6088893          	addi	a7,a7,-416 # 13f20 <__malloc_av_+0x10>
   120c8:	6a14                	ld	a3,16(a2)
   120ca:	0017e813          	ori	a6,a5,1
   120ce:	00f705b3          	add	a1,a4,a5
   120d2:	11168263          	beq	a3,a7,121d6 <_free_r+0x1e2>
   120d6:	6e10                	ld	a2,24(a2)
   120d8:	ee90                	sd	a2,24(a3)
   120da:	ea14                	sd	a3,16(a2)
   120dc:	01073423          	sd	a6,8(a4)
   120e0:	e19c                	sd	a5,0(a1)
   120e2:	b769                	j	1206c <_free_r+0x78>
   120e4:	8082                	ret
   120e6:	0017e693          	ori	a3,a5,1
   120ea:	fed43c23          	sd	a3,-8(s0)
   120ee:	e21c                	sd	a5,0(a2)
   120f0:	1ff00693          	li	a3,511
   120f4:	f8f6f0e3          	bgeu	a3,a5,12074 <_free_r+0x80>
   120f8:	0097d693          	srli	a3,a5,0x9
   120fc:	4611                	li	a2,4
   120fe:	08d66f63          	bltu	a2,a3,1219c <_free_r+0x1a8>
   12102:	0067d693          	srli	a3,a5,0x6
   12106:	2681                	sext.w	a3,a3
   12108:	0396859b          	addiw	a1,a3,57
   1210c:	0015959b          	slliw	a1,a1,0x1
   12110:	0386861b          	addiw	a2,a3,56
   12114:	058e                	slli	a1,a1,0x3
   12116:	95aa                	add	a1,a1,a0
   12118:	6194                	ld	a3,0(a1)
   1211a:	15c1                	addi	a1,a1,-16
   1211c:	0cd58d63          	beq	a1,a3,121f6 <_free_r+0x202>
   12120:	6690                	ld	a2,8(a3)
   12122:	9a71                	andi	a2,a2,-4
   12124:	00c7f563          	bgeu	a5,a2,1212e <_free_r+0x13a>
   12128:	6a94                	ld	a3,16(a3)
   1212a:	fed59be3          	bne	a1,a3,12120 <_free_r+0x12c>
   1212e:	6e8c                	ld	a1,24(a3)
   12130:	ef0c                	sd	a1,24(a4)
   12132:	eb14                	sd	a3,16(a4)
   12134:	6442                	ld	s0,16(sp)
   12136:	e998                	sd	a4,16(a1)
   12138:	60e2                	ld	ra,24(sp)
   1213a:	8526                	mv	a0,s1
   1213c:	64a2                	ld	s1,8(sp)
   1213e:	ee98                	sd	a4,24(a3)
   12140:	6105                	addi	sp,sp,32
   12142:	c6cff06f          	j	115ae <__malloc_unlock>
   12146:	10059763          	bnez	a1,12254 <_free_r+0x260>
   1214a:	6a0c                	ld	a1,16(a2)
   1214c:	6e10                	ld	a2,24(a2)
   1214e:	97b6                	add	a5,a5,a3
   12150:	0017e693          	ori	a3,a5,1
   12154:	ed90                	sd	a2,24(a1)
   12156:	ea0c                	sd	a1,16(a2)
   12158:	e714                	sd	a3,8(a4)
   1215a:	973e                	add	a4,a4,a5
   1215c:	e31c                	sd	a5,0(a4)
   1215e:	b7a9                	j	120a8 <_free_r+0xb4>
   12160:	8985                	andi	a1,a1,1
   12162:	97b6                	add	a5,a5,a3
   12164:	e989                	bnez	a1,12176 <_free_r+0x182>
   12166:	ff043583          	ld	a1,-16(s0)
   1216a:	8f0d                	sub	a4,a4,a1
   1216c:	6f14                	ld	a3,24(a4)
   1216e:	6b10                	ld	a2,16(a4)
   12170:	97ae                	add	a5,a5,a1
   12172:	ee14                	sd	a3,24(a2)
   12174:	ea90                	sd	a2,16(a3)
   12176:	75818693          	addi	a3,gp,1880 # 14758 <__malloc_trim_threshold>
   1217a:	0017e613          	ori	a2,a5,1
   1217e:	6294                	ld	a3,0(a3)
   12180:	e710                	sd	a2,8(a4)
   12182:	00002617          	auipc	a2,0x2
   12186:	d8e63f23          	sd	a4,-610(a2) # 13f20 <__malloc_av_+0x10>
   1218a:	f0d7efe3          	bltu	a5,a3,120a8 <_free_r+0xb4>
   1218e:	77018793          	addi	a5,gp,1904 # 14770 <__malloc_top_pad>
   12192:	638c                	ld	a1,0(a5)
   12194:	8526                	mv	a0,s1
   12196:	d93ff0ef          	jal	ra,11f28 <_malloc_trim_r>
   1219a:	b739                	j	120a8 <_free_r+0xb4>
   1219c:	4651                	li	a2,20
   1219e:	02d67363          	bgeu	a2,a3,121c4 <_free_r+0x1d0>
   121a2:	05400613          	li	a2,84
   121a6:	06d66463          	bltu	a2,a3,1220e <_free_r+0x21a>
   121aa:	00c7d693          	srli	a3,a5,0xc
   121ae:	2681                	sext.w	a3,a3
   121b0:	06f6859b          	addiw	a1,a3,111
   121b4:	0015959b          	slliw	a1,a1,0x1
   121b8:	06e6861b          	addiw	a2,a3,110
   121bc:	058e                	slli	a1,a1,0x3
   121be:	bfa1                	j	12116 <_free_r+0x122>
   121c0:	97b6                	add	a5,a5,a3
   121c2:	b719                	j	120c8 <_free_r+0xd4>
   121c4:	2681                	sext.w	a3,a3
   121c6:	05c6859b          	addiw	a1,a3,92
   121ca:	0015959b          	slliw	a1,a1,0x1
   121ce:	05b6861b          	addiw	a2,a3,91
   121d2:	058e                	slli	a1,a1,0x3
   121d4:	b789                	j	12116 <_free_r+0x122>
   121d6:	00002697          	auipc	a3,0x2
   121da:	d6e6b123          	sd	a4,-670(a3) # 13f38 <__malloc_av_+0x28>
   121de:	00002697          	auipc	a3,0x2
   121e2:	d4e6b923          	sd	a4,-686(a3) # 13f30 <__malloc_av_+0x20>
   121e6:	01173c23          	sd	a7,24(a4)
   121ea:	01173823          	sd	a7,16(a4)
   121ee:	01073423          	sd	a6,8(a4)
   121f2:	e19c                	sd	a5,0(a1)
   121f4:	bd55                	j	120a8 <_free_r+0xb4>
   121f6:	6508                	ld	a0,8(a0)
   121f8:	4785                	li	a5,1
   121fa:	4026561b          	sraiw	a2,a2,0x2
   121fe:	00c79633          	sll	a2,a5,a2
   12202:	8e49                	or	a2,a2,a0
   12204:	00002797          	auipc	a5,0x2
   12208:	d0c7ba23          	sd	a2,-748(a5) # 13f18 <__malloc_av_+0x8>
   1220c:	b715                	j	12130 <_free_r+0x13c>
   1220e:	15400613          	li	a2,340
   12212:	00d66d63          	bltu	a2,a3,1222c <_free_r+0x238>
   12216:	00f7d693          	srli	a3,a5,0xf
   1221a:	2681                	sext.w	a3,a3
   1221c:	0786859b          	addiw	a1,a3,120
   12220:	0015959b          	slliw	a1,a1,0x1
   12224:	0776861b          	addiw	a2,a3,119
   12228:	058e                	slli	a1,a1,0x3
   1222a:	b5f5                	j	12116 <_free_r+0x122>
   1222c:	55400613          	li	a2,1364
   12230:	00d66d63          	bltu	a2,a3,1224a <_free_r+0x256>
   12234:	0127d693          	srli	a3,a5,0x12
   12238:	2681                	sext.w	a3,a3
   1223a:	07d6859b          	addiw	a1,a3,125
   1223e:	0015959b          	slliw	a1,a1,0x1
   12242:	07c6861b          	addiw	a2,a3,124
   12246:	058e                	slli	a1,a1,0x3
   12248:	b5f9                	j	12116 <_free_r+0x122>
   1224a:	7f000593          	li	a1,2032
   1224e:	07e00613          	li	a2,126
   12252:	b5d1                	j	12116 <_free_r+0x122>
   12254:	0017e693          	ori	a3,a5,1
   12258:	e714                	sd	a3,8(a4)
   1225a:	e21c                	sd	a5,0(a2)
   1225c:	b5b1                	j	120a8 <_free_r+0xb4>

000000000001225e <_lseek_r>:
   1225e:	87ae                	mv	a5,a1
   12260:	1141                	addi	sp,sp,-16
   12262:	e022                	sd	s0,0(sp)
   12264:	85b2                	mv	a1,a2
   12266:	842a                	mv	s0,a0
   12268:	8636                	mv	a2,a3
   1226a:	853e                	mv	a0,a5
   1226c:	e406                	sd	ra,8(sp)
   1226e:	00002797          	auipc	a5,0x2
   12272:	5807a723          	sw	zero,1422(a5) # 147fc <errno>
   12276:	3b6000ef          	jal	ra,1262c <_lseek>
   1227a:	57fd                	li	a5,-1
   1227c:	00f50663          	beq	a0,a5,12288 <_lseek_r+0x2a>
   12280:	60a2                	ld	ra,8(sp)
   12282:	6402                	ld	s0,0(sp)
   12284:	0141                	addi	sp,sp,16
   12286:	8082                	ret
   12288:	00002797          	auipc	a5,0x2
   1228c:	57478793          	addi	a5,a5,1396 # 147fc <errno>
   12290:	439c                	lw	a5,0(a5)
   12292:	d7fd                	beqz	a5,12280 <_lseek_r+0x22>
   12294:	c01c                	sw	a5,0(s0)
   12296:	60a2                	ld	ra,8(sp)
   12298:	6402                	ld	s0,0(sp)
   1229a:	0141                	addi	sp,sp,16
   1229c:	8082                	ret

000000000001229e <__swhatbuf_r>:
   1229e:	7175                	addi	sp,sp,-144
   122a0:	e122                	sd	s0,128(sp)
   122a2:	842e                	mv	s0,a1
   122a4:	01259583          	lh	a1,18(a1)
   122a8:	fca6                	sd	s1,120(sp)
   122aa:	f8ca                	sd	s2,112(sp)
   122ac:	e506                	sd	ra,136(sp)
   122ae:	84b2                	mv	s1,a2
   122b0:	8936                	mv	s2,a3
   122b2:	0205cc63          	bltz	a1,122ea <__swhatbuf_r+0x4c>
   122b6:	0030                	addi	a2,sp,8
   122b8:	22c000ef          	jal	ra,124e4 <_fstat_r>
   122bc:	02054763          	bltz	a0,122ea <__swhatbuf_r+0x4c>
   122c0:	47b2                	lw	a5,12(sp)
   122c2:	673d                	lui	a4,0xf
   122c4:	60aa                	ld	ra,136(sp)
   122c6:	8ff9                	and	a5,a5,a4
   122c8:	6709                	lui	a4,0x2
   122ca:	8f99                	sub	a5,a5,a4
   122cc:	0017b793          	seqz	a5,a5
   122d0:	640a                	ld	s0,128(sp)
   122d2:	00f92023          	sw	a5,0(s2)
   122d6:	40000793          	li	a5,1024
   122da:	e09c                	sd	a5,0(s1)
   122dc:	6505                	lui	a0,0x1
   122de:	74e6                	ld	s1,120(sp)
   122e0:	7946                	ld	s2,112(sp)
   122e2:	80050513          	addi	a0,a0,-2048 # 800 <register_fini-0xf8b0>
   122e6:	6149                	addi	sp,sp,144
   122e8:	8082                	ret
   122ea:	01045783          	lhu	a5,16(s0)
   122ee:	00092023          	sw	zero,0(s2)
   122f2:	0807f793          	andi	a5,a5,128
   122f6:	cb99                	beqz	a5,1230c <__swhatbuf_r+0x6e>
   122f8:	60aa                	ld	ra,136(sp)
   122fa:	640a                	ld	s0,128(sp)
   122fc:	04000793          	li	a5,64
   12300:	e09c                	sd	a5,0(s1)
   12302:	7946                	ld	s2,112(sp)
   12304:	74e6                	ld	s1,120(sp)
   12306:	4501                	li	a0,0
   12308:	6149                	addi	sp,sp,144
   1230a:	8082                	ret
   1230c:	60aa                	ld	ra,136(sp)
   1230e:	640a                	ld	s0,128(sp)
   12310:	40000793          	li	a5,1024
   12314:	e09c                	sd	a5,0(s1)
   12316:	7946                	ld	s2,112(sp)
   12318:	74e6                	ld	s1,120(sp)
   1231a:	4501                	li	a0,0
   1231c:	6149                	addi	sp,sp,144
   1231e:	8082                	ret

0000000000012320 <__smakebuf_r>:
   12320:	0105d703          	lhu	a4,16(a1)
   12324:	7179                	addi	sp,sp,-48
   12326:	f022                	sd	s0,32(sp)
   12328:	f406                	sd	ra,40(sp)
   1232a:	ec26                	sd	s1,24(sp)
   1232c:	e84a                	sd	s2,16(sp)
   1232e:	8b09                	andi	a4,a4,2
   12330:	842e                	mv	s0,a1
   12332:	cf09                	beqz	a4,1234c <__smakebuf_r+0x2c>
   12334:	07758713          	addi	a4,a1,119
   12338:	e198                	sd	a4,0(a1)
   1233a:	ed98                	sd	a4,24(a1)
   1233c:	4705                	li	a4,1
   1233e:	d198                	sw	a4,32(a1)
   12340:	70a2                	ld	ra,40(sp)
   12342:	7402                	ld	s0,32(sp)
   12344:	64e2                	ld	s1,24(sp)
   12346:	6942                	ld	s2,16(sp)
   12348:	6145                	addi	sp,sp,48
   1234a:	8082                	ret
   1234c:	0054                	addi	a3,sp,4
   1234e:	0030                	addi	a2,sp,8
   12350:	84aa                	mv	s1,a0
   12352:	f4dff0ef          	jal	ra,1229e <__swhatbuf_r>
   12356:	65a2                	ld	a1,8(sp)
   12358:	892a                	mv	s2,a0
   1235a:	8526                	mv	a0,s1
   1235c:	989fe0ef          	jal	ra,10ce4 <_malloc_r>
   12360:	01041783          	lh	a5,16(s0)
   12364:	c915                	beqz	a0,12398 <__smakebuf_r+0x78>
   12366:	ffffe697          	auipc	a3,0xffffe
   1236a:	2bc68693          	addi	a3,a3,700 # 10622 <_cleanup_r>
   1236e:	ecb4                	sd	a3,88(s1)
   12370:	66a2                	ld	a3,8(sp)
   12372:	4712                	lw	a4,4(sp)
   12374:	0807e793          	ori	a5,a5,128
   12378:	00f41823          	sh	a5,16(s0)
   1237c:	e008                	sd	a0,0(s0)
   1237e:	ec08                	sd	a0,24(s0)
   12380:	d014                	sw	a3,32(s0)
   12382:	eb15                	bnez	a4,123b6 <__smakebuf_r+0x96>
   12384:	0127e7b3          	or	a5,a5,s2
   12388:	00f41823          	sh	a5,16(s0)
   1238c:	70a2                	ld	ra,40(sp)
   1238e:	7402                	ld	s0,32(sp)
   12390:	64e2                	ld	s1,24(sp)
   12392:	6942                	ld	s2,16(sp)
   12394:	6145                	addi	sp,sp,48
   12396:	8082                	ret
   12398:	2007f713          	andi	a4,a5,512
   1239c:	f355                	bnez	a4,12340 <__smakebuf_r+0x20>
   1239e:	9bf1                	andi	a5,a5,-4
   123a0:	0027e793          	ori	a5,a5,2
   123a4:	07740713          	addi	a4,s0,119
   123a8:	00f41823          	sh	a5,16(s0)
   123ac:	4785                	li	a5,1
   123ae:	e018                	sd	a4,0(s0)
   123b0:	ec18                	sd	a4,24(s0)
   123b2:	d01c                	sw	a5,32(s0)
   123b4:	b771                	j	12340 <__smakebuf_r+0x20>
   123b6:	01241583          	lh	a1,18(s0)
   123ba:	8526                	mv	a0,s1
   123bc:	166000ef          	jal	ra,12522 <_isatty_r>
   123c0:	e501                	bnez	a0,123c8 <__smakebuf_r+0xa8>
   123c2:	01041783          	lh	a5,16(s0)
   123c6:	bf7d                	j	12384 <__smakebuf_r+0x64>
   123c8:	01045783          	lhu	a5,16(s0)
   123cc:	9bf1                	andi	a5,a5,-4
   123ce:	0017e793          	ori	a5,a5,1
   123d2:	0107979b          	slliw	a5,a5,0x10
   123d6:	4107d79b          	sraiw	a5,a5,0x10
   123da:	b76d                	j	12384 <__smakebuf_r+0x64>

00000000000123dc <_read_r>:
   123dc:	87ae                	mv	a5,a1
   123de:	1141                	addi	sp,sp,-16
   123e0:	e022                	sd	s0,0(sp)
   123e2:	85b2                	mv	a1,a2
   123e4:	842a                	mv	s0,a0
   123e6:	8636                	mv	a2,a3
   123e8:	853e                	mv	a0,a5
   123ea:	e406                	sd	ra,8(sp)
   123ec:	00002797          	auipc	a5,0x2
   123f0:	4007a823          	sw	zero,1040(a5) # 147fc <errno>
   123f4:	26a000ef          	jal	ra,1265e <_read>
   123f8:	57fd                	li	a5,-1
   123fa:	00f50663          	beq	a0,a5,12406 <_read_r+0x2a>
   123fe:	60a2                	ld	ra,8(sp)
   12400:	6402                	ld	s0,0(sp)
   12402:	0141                	addi	sp,sp,16
   12404:	8082                	ret
   12406:	00002797          	auipc	a5,0x2
   1240a:	3f678793          	addi	a5,a5,1014 # 147fc <errno>
   1240e:	439c                	lw	a5,0(a5)
   12410:	d7fd                	beqz	a5,123fe <_read_r+0x22>
   12412:	c01c                	sw	a5,0(s0)
   12414:	60a2                	ld	ra,8(sp)
   12416:	6402                	ld	s0,0(sp)
   12418:	0141                	addi	sp,sp,16
   1241a:	8082                	ret

000000000001241c <cleanup_glue>:
   1241c:	1101                	addi	sp,sp,-32
   1241e:	e822                	sd	s0,16(sp)
   12420:	842e                	mv	s0,a1
   12422:	618c                	ld	a1,0(a1)
   12424:	e426                	sd	s1,8(sp)
   12426:	ec06                	sd	ra,24(sp)
   12428:	84aa                	mv	s1,a0
   1242a:	c199                	beqz	a1,12430 <cleanup_glue+0x14>
   1242c:	ff1ff0ef          	jal	ra,1241c <cleanup_glue>
   12430:	85a2                	mv	a1,s0
   12432:	6442                	ld	s0,16(sp)
   12434:	60e2                	ld	ra,24(sp)
   12436:	8526                	mv	a0,s1
   12438:	64a2                	ld	s1,8(sp)
   1243a:	6105                	addi	sp,sp,32
   1243c:	be65                	j	11ff4 <_free_r>

000000000001243e <_reclaim_reent>:
   1243e:	74818793          	addi	a5,gp,1864 # 14748 <_impure_ptr>
   12442:	639c                	ld	a5,0(a5)
   12444:	08a78f63          	beq	a5,a0,124e2 <_reclaim_reent+0xa4>
   12448:	7d38                	ld	a4,120(a0)
   1244a:	7179                	addi	sp,sp,-48
   1244c:	ec26                	sd	s1,24(sp)
   1244e:	f406                	sd	ra,40(sp)
   12450:	f022                	sd	s0,32(sp)
   12452:	e84a                	sd	s2,16(sp)
   12454:	e44e                	sd	s3,8(sp)
   12456:	84aa                	mv	s1,a0
   12458:	c715                	beqz	a4,12484 <_reclaim_reent+0x46>
   1245a:	4901                	li	s2,0
   1245c:	20000993          	li	s3,512
   12460:	012707b3          	add	a5,a4,s2
   12464:	638c                	ld	a1,0(a5)
   12466:	c981                	beqz	a1,12476 <_reclaim_reent+0x38>
   12468:	6180                	ld	s0,0(a1)
   1246a:	8526                	mv	a0,s1
   1246c:	b89ff0ef          	jal	ra,11ff4 <_free_r>
   12470:	85a2                	mv	a1,s0
   12472:	f87d                	bnez	s0,12468 <_reclaim_reent+0x2a>
   12474:	7cb8                	ld	a4,120(s1)
   12476:	0921                	addi	s2,s2,8
   12478:	ff3914e3          	bne	s2,s3,12460 <_reclaim_reent+0x22>
   1247c:	85ba                	mv	a1,a4
   1247e:	8526                	mv	a0,s1
   12480:	b75ff0ef          	jal	ra,11ff4 <_free_r>
   12484:	70ac                	ld	a1,96(s1)
   12486:	c581                	beqz	a1,1248e <_reclaim_reent+0x50>
   12488:	8526                	mv	a0,s1
   1248a:	b6bff0ef          	jal	ra,11ff4 <_free_r>
   1248e:	1f84b583          	ld	a1,504(s1)
   12492:	cd81                	beqz	a1,124aa <_reclaim_reent+0x6c>
   12494:	20048913          	addi	s2,s1,512
   12498:	01258963          	beq	a1,s2,124aa <_reclaim_reent+0x6c>
   1249c:	6180                	ld	s0,0(a1)
   1249e:	8526                	mv	a0,s1
   124a0:	b55ff0ef          	jal	ra,11ff4 <_free_r>
   124a4:	85a2                	mv	a1,s0
   124a6:	fe891be3          	bne	s2,s0,1249c <_reclaim_reent+0x5e>
   124aa:	64cc                	ld	a1,136(s1)
   124ac:	c581                	beqz	a1,124b4 <_reclaim_reent+0x76>
   124ae:	8526                	mv	a0,s1
   124b0:	b45ff0ef          	jal	ra,11ff4 <_free_r>
   124b4:	48bc                	lw	a5,80(s1)
   124b6:	cf99                	beqz	a5,124d4 <_reclaim_reent+0x96>
   124b8:	6cbc                	ld	a5,88(s1)
   124ba:	8526                	mv	a0,s1
   124bc:	9782                	jalr	a5
   124be:	5204b583          	ld	a1,1312(s1)
   124c2:	c989                	beqz	a1,124d4 <_reclaim_reent+0x96>
   124c4:	7402                	ld	s0,32(sp)
   124c6:	70a2                	ld	ra,40(sp)
   124c8:	6942                	ld	s2,16(sp)
   124ca:	69a2                	ld	s3,8(sp)
   124cc:	8526                	mv	a0,s1
   124ce:	64e2                	ld	s1,24(sp)
   124d0:	6145                	addi	sp,sp,48
   124d2:	b7a9                	j	1241c <cleanup_glue>
   124d4:	70a2                	ld	ra,40(sp)
   124d6:	7402                	ld	s0,32(sp)
   124d8:	64e2                	ld	s1,24(sp)
   124da:	6942                	ld	s2,16(sp)
   124dc:	69a2                	ld	s3,8(sp)
   124de:	6145                	addi	sp,sp,48
   124e0:	8082                	ret
   124e2:	8082                	ret

00000000000124e4 <_fstat_r>:
   124e4:	87ae                	mv	a5,a1
   124e6:	1141                	addi	sp,sp,-16
   124e8:	e022                	sd	s0,0(sp)
   124ea:	85b2                	mv	a1,a2
   124ec:	842a                	mv	s0,a0
   124ee:	853e                	mv	a0,a5
   124f0:	e406                	sd	ra,8(sp)
   124f2:	00002797          	auipc	a5,0x2
   124f6:	3007a523          	sw	zero,778(a5) # 147fc <errno>
   124fa:	0c4000ef          	jal	ra,125be <_fstat>
   124fe:	57fd                	li	a5,-1
   12500:	00f50663          	beq	a0,a5,1250c <_fstat_r+0x28>
   12504:	60a2                	ld	ra,8(sp)
   12506:	6402                	ld	s0,0(sp)
   12508:	0141                	addi	sp,sp,16
   1250a:	8082                	ret
   1250c:	00002797          	auipc	a5,0x2
   12510:	2f078793          	addi	a5,a5,752 # 147fc <errno>
   12514:	439c                	lw	a5,0(a5)
   12516:	d7fd                	beqz	a5,12504 <_fstat_r+0x20>
   12518:	c01c                	sw	a5,0(s0)
   1251a:	60a2                	ld	ra,8(sp)
   1251c:	6402                	ld	s0,0(sp)
   1251e:	0141                	addi	sp,sp,16
   12520:	8082                	ret

0000000000012522 <_isatty_r>:
   12522:	1141                	addi	sp,sp,-16
   12524:	e022                	sd	s0,0(sp)
   12526:	842a                	mv	s0,a0
   12528:	852e                	mv	a0,a1
   1252a:	00002797          	auipc	a5,0x2
   1252e:	2c07a923          	sw	zero,722(a5) # 147fc <errno>
   12532:	e406                	sd	ra,8(sp)
   12534:	0d2000ef          	jal	ra,12606 <_isatty>
   12538:	57fd                	li	a5,-1
   1253a:	00f50663          	beq	a0,a5,12546 <_isatty_r+0x24>
   1253e:	60a2                	ld	ra,8(sp)
   12540:	6402                	ld	s0,0(sp)
   12542:	0141                	addi	sp,sp,16
   12544:	8082                	ret
   12546:	00002797          	auipc	a5,0x2
   1254a:	2b678793          	addi	a5,a5,694 # 147fc <errno>
   1254e:	439c                	lw	a5,0(a5)
   12550:	d7fd                	beqz	a5,1253e <_isatty_r+0x1c>
   12552:	c01c                	sw	a5,0(s0)
   12554:	60a2                	ld	ra,8(sp)
   12556:	6402                	ld	s0,0(sp)
   12558:	0141                	addi	sp,sp,16
   1255a:	8082                	ret

000000000001255c <_close>:
   1255c:	4581                	li	a1,0
   1255e:	4601                	li	a2,0
   12560:	4681                	li	a3,0
   12562:	4701                	li	a4,0
   12564:	4781                	li	a5,0
   12566:	03900893          	li	a7,57
   1256a:	00000073          	ecall
   1256e:	00054463          	bltz	a0,12576 <_close+0x1a>
   12572:	2501                	sext.w	a0,a0
   12574:	8082                	ret
   12576:	1141                	addi	sp,sp,-16
   12578:	e022                	sd	s0,0(sp)
   1257a:	e406                	sd	ra,8(sp)
   1257c:	842a                	mv	s0,a0
   1257e:	208000ef          	jal	ra,12786 <__errno>
   12582:	408007bb          	negw	a5,s0
   12586:	60a2                	ld	ra,8(sp)
   12588:	6402                	ld	s0,0(sp)
   1258a:	c11c                	sw	a5,0(a0)
   1258c:	557d                	li	a0,-1
   1258e:	0141                	addi	sp,sp,16
   12590:	8082                	ret

0000000000012592 <_exit>:
   12592:	4581                	li	a1,0
   12594:	4601                	li	a2,0
   12596:	4681                	li	a3,0
   12598:	4701                	li	a4,0
   1259a:	4781                	li	a5,0
   1259c:	05d00893          	li	a7,93
   125a0:	00000073          	ecall
   125a4:	00054363          	bltz	a0,125aa <_exit+0x18>
   125a8:	a001                	j	125a8 <_exit+0x16>
   125aa:	1141                	addi	sp,sp,-16
   125ac:	e022                	sd	s0,0(sp)
   125ae:	842a                	mv	s0,a0
   125b0:	e406                	sd	ra,8(sp)
   125b2:	4080043b          	negw	s0,s0
   125b6:	1d0000ef          	jal	ra,12786 <__errno>
   125ba:	c100                	sw	s0,0(a0)
   125bc:	a001                	j	125bc <_exit+0x2a>

00000000000125be <_fstat>:
   125be:	7135                	addi	sp,sp,-160
   125c0:	e526                	sd	s1,136(sp)
   125c2:	ed06                	sd	ra,152(sp)
   125c4:	84ae                	mv	s1,a1
   125c6:	e922                	sd	s0,144(sp)
   125c8:	4601                	li	a2,0
   125ca:	858a                	mv	a1,sp
   125cc:	4681                	li	a3,0
   125ce:	4701                	li	a4,0
   125d0:	4781                	li	a5,0
   125d2:	05000893          	li	a7,80
   125d6:	00000073          	ecall
   125da:	842a                	mv	s0,a0
   125dc:	00054e63          	bltz	a0,125f8 <_fstat+0x3a>
   125e0:	0005041b          	sext.w	s0,a0
   125e4:	8526                	mv	a0,s1
   125e6:	858a                	mv	a1,sp
   125e8:	144000ef          	jal	ra,1272c <_conv_stat>
   125ec:	8522                	mv	a0,s0
   125ee:	60ea                	ld	ra,152(sp)
   125f0:	644a                	ld	s0,144(sp)
   125f2:	64aa                	ld	s1,136(sp)
   125f4:	610d                	addi	sp,sp,160
   125f6:	8082                	ret
   125f8:	4080043b          	negw	s0,s0
   125fc:	18a000ef          	jal	ra,12786 <__errno>
   12600:	c100                	sw	s0,0(a0)
   12602:	547d                	li	s0,-1
   12604:	b7c5                	j	125e4 <_fstat+0x26>

0000000000012606 <_isatty>:
   12606:	7119                	addi	sp,sp,-128
   12608:	002c                	addi	a1,sp,8
   1260a:	fc86                	sd	ra,120(sp)
   1260c:	fb3ff0ef          	jal	ra,125be <_fstat>
   12610:	57fd                	li	a5,-1
   12612:	00f50963          	beq	a0,a5,12624 <_isatty+0x1e>
   12616:	4532                	lw	a0,12(sp)
   12618:	70e6                	ld	ra,120(sp)
   1261a:	40d5551b          	sraiw	a0,a0,0xd
   1261e:	8905                	andi	a0,a0,1
   12620:	6109                	addi	sp,sp,128
   12622:	8082                	ret
   12624:	70e6                	ld	ra,120(sp)
   12626:	4501                	li	a0,0
   12628:	6109                	addi	sp,sp,128
   1262a:	8082                	ret

000000000001262c <_lseek>:
   1262c:	1141                	addi	sp,sp,-16
   1262e:	e406                	sd	ra,8(sp)
   12630:	e022                	sd	s0,0(sp)
   12632:	4681                	li	a3,0
   12634:	4701                	li	a4,0
   12636:	4781                	li	a5,0
   12638:	03e00893          	li	a7,62
   1263c:	00000073          	ecall
   12640:	842a                	mv	s0,a0
   12642:	00054763          	bltz	a0,12650 <_lseek+0x24>
   12646:	8522                	mv	a0,s0
   12648:	60a2                	ld	ra,8(sp)
   1264a:	6402                	ld	s0,0(sp)
   1264c:	0141                	addi	sp,sp,16
   1264e:	8082                	ret
   12650:	4080043b          	negw	s0,s0
   12654:	132000ef          	jal	ra,12786 <__errno>
   12658:	c100                	sw	s0,0(a0)
   1265a:	547d                	li	s0,-1
   1265c:	b7ed                	j	12646 <_lseek+0x1a>

000000000001265e <_read>:
   1265e:	1141                	addi	sp,sp,-16
   12660:	e406                	sd	ra,8(sp)
   12662:	e022                	sd	s0,0(sp)
   12664:	4681                	li	a3,0
   12666:	4701                	li	a4,0
   12668:	4781                	li	a5,0
   1266a:	03f00893          	li	a7,63
   1266e:	00000073          	ecall
   12672:	842a                	mv	s0,a0
   12674:	00054763          	bltz	a0,12682 <_read+0x24>
   12678:	8522                	mv	a0,s0
   1267a:	60a2                	ld	ra,8(sp)
   1267c:	6402                	ld	s0,0(sp)
   1267e:	0141                	addi	sp,sp,16
   12680:	8082                	ret
   12682:	4080043b          	negw	s0,s0
   12686:	100000ef          	jal	ra,12786 <__errno>
   1268a:	c100                	sw	s0,0(a0)
   1268c:	547d                	li	s0,-1
   1268e:	b7ed                	j	12678 <_read+0x1a>

0000000000012690 <_sbrk>:
   12690:	77818313          	addi	t1,gp,1912 # 14778 <heap_end.1900>
   12694:	00033783          	ld	a5,0(t1)
   12698:	1141                	addi	sp,sp,-16
   1269a:	e406                	sd	ra,8(sp)
   1269c:	882a                	mv	a6,a0
   1269e:	e385                	bnez	a5,126be <_sbrk+0x2e>
   126a0:	4501                	li	a0,0
   126a2:	4581                	li	a1,0
   126a4:	4601                	li	a2,0
   126a6:	4681                	li	a3,0
   126a8:	4701                	li	a4,0
   126aa:	0d600893          	li	a7,214
   126ae:	00000073          	ecall
   126b2:	57fd                	li	a5,-1
   126b4:	02f50b63          	beq	a0,a5,126ea <_sbrk+0x5a>
   126b8:	87aa                	mv	a5,a0
   126ba:	76a1bc23          	sd	a0,1912(gp) # 14778 <heap_end.1900>
   126be:	00f80533          	add	a0,a6,a5
   126c2:	4581                	li	a1,0
   126c4:	4601                	li	a2,0
   126c6:	4681                	li	a3,0
   126c8:	4701                	li	a4,0
   126ca:	4781                	li	a5,0
   126cc:	0d600893          	li	a7,214
   126d0:	00000073          	ecall
   126d4:	00033783          	ld	a5,0(t1)
   126d8:	983e                	add	a6,a6,a5
   126da:	01051863          	bne	a0,a6,126ea <_sbrk+0x5a>
   126de:	60a2                	ld	ra,8(sp)
   126e0:	76a1bc23          	sd	a0,1912(gp) # 14778 <heap_end.1900>
   126e4:	853e                	mv	a0,a5
   126e6:	0141                	addi	sp,sp,16
   126e8:	8082                	ret
   126ea:	09c000ef          	jal	ra,12786 <__errno>
   126ee:	60a2                	ld	ra,8(sp)
   126f0:	47b1                	li	a5,12
   126f2:	c11c                	sw	a5,0(a0)
   126f4:	557d                	li	a0,-1
   126f6:	0141                	addi	sp,sp,16
   126f8:	8082                	ret

00000000000126fa <_write>:
   126fa:	1141                	addi	sp,sp,-16
   126fc:	e406                	sd	ra,8(sp)
   126fe:	e022                	sd	s0,0(sp)
   12700:	4681                	li	a3,0
   12702:	4701                	li	a4,0
   12704:	4781                	li	a5,0
   12706:	04000893          	li	a7,64
   1270a:	00000073          	ecall
   1270e:	842a                	mv	s0,a0
   12710:	00054763          	bltz	a0,1271e <_write+0x24>
   12714:	8522                	mv	a0,s0
   12716:	60a2                	ld	ra,8(sp)
   12718:	6402                	ld	s0,0(sp)
   1271a:	0141                	addi	sp,sp,16
   1271c:	8082                	ret
   1271e:	4080043b          	negw	s0,s0
   12722:	064000ef          	jal	ra,12786 <__errno>
   12726:	c100                	sw	s0,0(a0)
   12728:	547d                	li	s0,-1
   1272a:	b7ed                	j	12714 <_write+0x1a>

000000000001272c <_conv_stat>:
   1272c:	0005b383          	ld	t2,0(a1)
   12730:	0085b283          	ld	t0,8(a1)
   12734:	0105af83          	lw	t6,16(a1)
   12738:	0145af03          	lw	t5,20(a1)
   1273c:	0185ae83          	lw	t4,24(a1)
   12740:	01c5ae03          	lw	t3,28(a1)
   12744:	0205b303          	ld	t1,32(a1)
   12748:	0305b883          	ld	a7,48(a1)
   1274c:	0405b803          	ld	a6,64(a1)
   12750:	5d90                	lw	a2,56(a1)
   12752:	65b4                	ld	a3,72(a1)
   12754:	6db8                	ld	a4,88(a1)
   12756:	75bc                	ld	a5,104(a1)
   12758:	00751023          	sh	t2,0(a0)
   1275c:	00551123          	sh	t0,2(a0)
   12760:	01f52223          	sw	t6,4(a0)
   12764:	01e51423          	sh	t5,8(a0)
   12768:	01d51523          	sh	t4,10(a0)
   1276c:	01c51623          	sh	t3,12(a0)
   12770:	00651723          	sh	t1,14(a0)
   12774:	01153823          	sd	a7,16(a0)
   12778:	05053823          	sd	a6,80(a0)
   1277c:	e530                	sd	a2,72(a0)
   1277e:	ed14                	sd	a3,24(a0)
   12780:	f518                	sd	a4,40(a0)
   12782:	fd1c                	sd	a5,56(a0)
   12784:	8082                	ret

0000000000012786 <__errno>:
   12786:	74818793          	addi	a5,gp,1864 # 14748 <_impure_ptr>
   1278a:	6388                	ld	a0,0(a5)
   1278c:	8082                	ret
```







