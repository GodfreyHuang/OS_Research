	.file	"2023q1_1.c"
	.option nopic
	.attribute arch, "rv32i2p1"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.align	2
	.globl	count_leading_zeros
	.type	count_leading_zeros, @function
count_leading_zeros:
	addi	sp,sp,-144
	sw	s0,140(sp)
	sw	s2,136(sp)
	sw	s3,132(sp)
	sw	s4,128(sp)
	sw	s5,124(sp)
	sw	s6,120(sp)
	sw	s7,116(sp)
	sw	s8,112(sp)
	sw	s9,108(sp)
	sw	s10,104(sp)
	sw	s11,100(sp)
	addi	s0,sp,144
	sw	a0,-56(s0)
	sw	a1,-52(s0)
	lw	a5,-52(s0)
	slli	a4,a5,31
	lw	a5,-56(s0)
	srli	a2,a5,1
	or	a2,a4,a2
	lw	a5,-52(s0)
	srli	a3,a5,1
	lw	a5,-56(s0)
	or	t3,a5,a2
	lw	a5,-52(s0)
	or	t4,a5,a3
	sw	t3,-56(s0)
	sw	t4,-52(s0)
	lw	a5,-52(s0)
	slli	a4,a5,30
	lw	a5,-56(s0)
	srli	a6,a5,2
	or	a6,a4,a6
	lw	a5,-52(s0)
	srli	a7,a5,2
	lw	a5,-56(s0)
	or	a5,a5,a6
	sw	a5,-112(s0)
	lw	a5,-52(s0)
	or	a5,a5,a7
	sw	a5,-108(s0)
	lw	a5,-112(s0)
	lw	a6,-108(s0)
	sw	a5,-56(s0)
	sw	a6,-52(s0)
	lw	a5,-52(s0)
	slli	a4,a5,28
	lw	a5,-56(s0)
	srli	t1,a5,4
	or	t1,a4,t1
	lw	a5,-52(s0)
	srli	t2,a5,4
	lw	a5,-56(s0)
	or	a5,a5,t1
	sw	a5,-120(s0)
	lw	a5,-52(s0)
	or	a5,a5,t2
	sw	a5,-116(s0)
	lw	a5,-120(s0)
	lw	a6,-116(s0)
	sw	a5,-56(s0)
	sw	a6,-52(s0)
	lw	a5,-52(s0)
	slli	a4,a5,24
	lw	a5,-56(s0)
	srli	s2,a5,8
	or	s2,a4,s2
	lw	a5,-52(s0)
	srli	s3,a5,8
	lw	a5,-56(s0)
	or	a5,a5,s2
	sw	a5,-128(s0)
	lw	a5,-52(s0)
	or	a5,a5,s3
	sw	a5,-124(s0)
	lw	a5,-128(s0)
	lw	a6,-124(s0)
	sw	a5,-56(s0)
	sw	a6,-52(s0)
	lw	a5,-52(s0)
	slli	a4,a5,16
	lw	a5,-56(s0)
	srli	a5,a5,16
	sw	a5,-64(s0)
	lw	a5,-64(s0)
	or	a5,a4,a5
	sw	a5,-64(s0)
	lw	a5,-52(s0)
	srli	a5,a5,16
	sw	a5,-60(s0)
	lw	a5,-56(s0)
	lw	a2,-64(s0)
	lw	a3,-60(s0)
	mv	a4,a2
	or	a5,a5,a4
	sw	a5,-136(s0)
	lw	a5,-52(s0)
	mv	a4,a3
	or	a5,a5,a4
	sw	a5,-132(s0)
	lw	a5,-136(s0)
	lw	a6,-132(s0)
	sw	a5,-56(s0)
	sw	a6,-52(s0)
	lw	a5,-52(s0)
	srli	a5,a5,0
	sw	a5,-72(s0)
	sw	zero,-68(s0)
	lw	a5,-56(s0)
	lw	a2,-72(s0)
	lw	a3,-68(s0)
	mv	a4,a2
	or	a5,a5,a4
	sw	a5,-144(s0)
	lw	a5,-52(s0)
	mv	a4,a3
	or	a5,a5,a4
	sw	a5,-140(s0)
	lw	a5,-144(s0)
	lw	a6,-140(s0)
	sw	a5,-56(s0)
	sw	a6,-52(s0)
	lw	a5,-52(s0)
	slli	a5,a5,31
	lw	a4,-56(s0)
	srli	s10,a4,1
	or	s10,a5,s10
	lw	a5,-52(s0)
	srli	s11,a5,1
	li	a5,1431654400
	addi	a5,a5,1365
	and	a5,s10,a5
	sw	a5,-80(s0)
	li	a5,1431654400
	addi	a5,a5,1365
	and	a5,s11,a5
	sw	a5,-76(s0)
	lw	a2,-56(s0)
	lw	a3,-52(s0)
	lw	a6,-80(s0)
	lw	a7,-76(s0)
	mv	a1,a6
	sub	a4,a2,a1
	mv	a1,a4
	sgtu	a1,a1,a2
	mv	a0,a7
	sub	a5,a3,a0
	sub	a3,a5,a1
	mv	a5,a3
	sw	a4,-56(s0)
	sw	a5,-52(s0)
	lw	a5,-52(s0)
	slli	a5,a5,30
	lw	a4,-56(s0)
	srli	s8,a4,2
	or	s8,a5,s8
	lw	a5,-52(s0)
	srli	s9,a5,2
	li	a5,858992640
	addi	a5,a5,819
	and	a5,s8,a5
	sw	a5,-88(s0)
	li	a5,858992640
	addi	a5,a5,819
	and	a5,s9,a5
	sw	a5,-84(s0)
	lw	a4,-56(s0)
	li	a5,858992640
	addi	a5,a5,819
	and	a5,a4,a5
	sw	a5,-96(s0)
	lw	a4,-52(s0)
	li	a5,858992640
	addi	a5,a5,819
	and	a5,a4,a5
	sw	a5,-92(s0)
	lw	a0,-88(s0)
	lw	a1,-84(s0)
	mv	a3,a0
	lw	a6,-96(s0)
	lw	a7,-92(s0)
	mv	a2,a6
	add	a4,a3,a2
	mv	a3,a4
	mv	a2,a0
	sltu	a3,a3,a2
	mv	a2,a1
	mv	a1,a7
	add	a5,a2,a1
	add	a3,a3,a5
	mv	a5,a3
	sw	a4,-56(s0)
	sw	a5,-52(s0)
	lw	a5,-52(s0)
	slli	a5,a5,28
	lw	a4,-56(s0)
	srli	t5,a4,4
	or	t5,a5,t5
	lw	a5,-52(s0)
	srli	t6,a5,4
	lw	a2,-56(s0)
	lw	a3,-52(s0)
	add	a4,t5,a2
	mv	a1,a4
	sltu	a1,a1,t5
	add	a5,t6,a3
	add	a3,a1,a5
	mv	a5,a3
	li	a3,252645376
	addi	a3,a3,-241
	and	a3,a4,a3
	sw	a3,-56(s0)
	li	a3,252645376
	addi	a3,a3,-241
	and	a5,a5,a3
	sw	a5,-52(s0)
	lw	a5,-52(s0)
	slli	a5,a5,24
	lw	a4,-56(s0)
	srli	s6,a4,8
	or	s6,a5,s6
	lw	a5,-52(s0)
	srli	s7,a5,8
	lw	a2,-56(s0)
	lw	a3,-52(s0)
	add	a4,a2,s6
	mv	a1,a4
	sltu	a1,a1,a2
	add	a5,a3,s7
	add	a3,a1,a5
	mv	a5,a3
	sw	a4,-56(s0)
	sw	a5,-52(s0)
	lw	a5,-52(s0)
	slli	a5,a5,16
	lw	a4,-56(s0)
	srli	s4,a4,16
	or	s4,a5,s4
	lw	a5,-52(s0)
	srli	s5,a5,16
	lw	a2,-56(s0)
	lw	a3,-52(s0)
	add	a4,a2,s4
	mv	a1,a4
	sltu	a1,a1,a2
	add	a5,a3,s5
	add	a3,a1,a5
	mv	a5,a3
	sw	a4,-56(s0)
	sw	a5,-52(s0)
	lw	a5,-52(s0)
	srli	a5,a5,0
	sw	a5,-104(s0)
	sw	zero,-100(s0)
	lw	a2,-56(s0)
	lw	a3,-52(s0)
	lw	a6,-104(s0)
	lw	a7,-100(s0)
	mv	a1,a6
	add	a4,a2,a1
	mv	a1,a4
	sltu	a1,a1,a2
	mv	a0,a7
	add	a5,a3,a0
	add	a3,a1,a5
	mv	a5,a3
	sw	a4,-56(s0)
	sw	a5,-52(s0)
	lhu	a5,-56(s0)
	andi	a5,a5,127
	slli	a5,a5,16
	srli	a5,a5,16
	li	a4,64
	sub	a5,a4,a5
	slli	a5,a5,16
	srli	a5,a5,16
	mv	a0,a5
	lw	s0,140(sp)
	lw	s2,136(sp)
	lw	s3,132(sp)
	lw	s4,128(sp)
	lw	s5,124(sp)
	lw	s6,120(sp)
	lw	s7,116(sp)
	lw	s8,112(sp)
	lw	s9,108(sp)
	lw	s10,104(sp)
	lw	s11,100(sp)
	addi	sp,sp,144
	jr	ra
	.size	count_leading_zeros, .-count_leading_zeros
	.section	.rodata
	.align	2
.LC0:
	.string	"%d\n"
	.text
	.align	2
	.globl	main
	.type	main, @function
main:
	addi	sp,sp,-48
	sw	ra,44(sp)
	sw	s0,40(sp)
	addi	s0,sp,48
	sw	a0,-36(s0)
	sw	a1,-40(s0)
	li	a4,16
	li	a5,0
	sw	a4,-24(s0)
	sw	a5,-20(s0)
	lw	a0,-24(s0)
	lw	a1,-20(s0)
	call	count_leading_zeros
	mv	a5,a0
	mv	a1,a5
	lui	a5,%hi(.LC0)
	addi	a0,a5,%lo(.LC0)
	call	printf
	li	a4,33
	li	a5,0
	sw	a4,-32(s0)
	sw	a5,-28(s0)
	lw	a0,-32(s0)
	lw	a1,-28(s0)
	call	count_leading_zeros
	mv	a5,a0
	mv	a1,a5
	lui	a5,%hi(.LC0)
	addi	a0,a5,%lo(.LC0)
	call	printf
	li	a5,0
	mv	a0,a5
	lw	ra,44(sp)
	lw	s0,40(sp)
	addi	sp,sp,48
	jr	ra
	.size	main, .-main
	.ident	"GCC: (gc891d8dc23e) 13.2.0"
