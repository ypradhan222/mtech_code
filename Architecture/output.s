	.file	1 "unroll_loop.c"
	.section .mdebug.abi32
	.previous
	.nan	legacy
	.module	fp=xx
	.module	nooddspreg
	.abicalls
	.text
	.rdata
	.align	2
$LC0:
	.ascii	"Final result: %d\012\000"
	.text
	.align	2
	.globl	main
	.set	nomips16
	.set	nomicromips
	.ent	main
	.type	main, @function
main:
	.frame	$fp,64,$31		# vars= 32, regs= 2/0, args= 16, gp= 8
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-64
	sw	$31,60($sp)
	sw	$fp,56($sp)
	move	$fp,$sp
	lui	$28,%hi(__gnu_local_gp)
	addiu	$28,$28,%lo(__gnu_local_gp)
	.cprestore	16
	li	$2,5			# 0x5
	sw	$2,28($fp)
	li	$2,2			# 0x2
	sw	$2,32($fp)
	sw	$0,36($fp)
	sw	$0,40($fp)
	li	$2,10			# 0xa
	sw	$2,48($fp)
	.option	pic0
	b	$L2
	nop

	.option	pic2
$L5:
	sw	$0,44($fp)
	.option	pic0
	b	$L3
	nop

	.option	pic2
$L4:
	lw	$3,36($fp)
	lw	$2,32($fp)
	addu	$2,$3,$2
	sw	$2,36($fp)
	lw	$3,32($fp)
	lw	$2,28($fp)
	subu	$2,$3,$2
	sw	$2,32($fp)
	lw	$3,36($fp)
	lw	$2,32($fp)
	addu	$2,$3,$2
	sw	$2,36($fp)
	lw	$3,32($fp)
	lw	$2,28($fp)
	subu	$2,$3,$2
	sw	$2,32($fp)
	lw	$2,44($fp)
	addiu	$2,$2,1
	sw	$2,44($fp)
$L3:
	lw	$2,44($fp)
	slt	$2,$2,2
	bne	$2,$0,$L4
	nop

	lw	$2,28($fp)
	sw	$2,52($fp)
	lw	$2,32($fp)
	sw	$2,28($fp)
	lw	$2,52($fp)
	sw	$2,32($fp)
	lw	$2,40($fp)
	addiu	$2,$2,2
	sw	$2,40($fp)
$L2:
	lw	$3,40($fp)
	lw	$2,48($fp)
	slt	$2,$3,$2
	bne	$2,$0,$L5
	nop

	lw	$5,36($fp)
	lui	$2,%hi($LC0)
	addiu	$4,$2,%lo($LC0)
	lw	$2,%call16(printf)($28)
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,printf
1:	jalr	$25
	nop

	lw	$28,16($fp)
	move	$2,$0
	move	$sp,$fp
	lw	$31,60($sp)
	lw	$fp,56($sp)
	addiu	$sp,$sp,64
	jr	$31
	nop

	.set	macro
	.set	reorder
	.end	main
	.size	main, .-main
	.ident	"GCC: (Ubuntu 10.3.0-1ubuntu1) 10.3.0"
	.section	.note.GNU-stack,"",@progbits
