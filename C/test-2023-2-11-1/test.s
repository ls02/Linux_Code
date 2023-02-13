	.file	"test.c"
	.section	.rodata
.LC0:
	.string	"\346\210\221\346\230\2571\345\217\267\344\277\241\345\217\267"
.LC1:
	.string	"\346\210\221\346\230\2572\345\217\267\344\277\241\345\217\267"
.LC2:
	.string	"\346\210\221\346\230\2573\345\217\267\344\277\241\345\217\267"
.LC3:
	.string	"\346\210\221\346\230\2574\345\217\267\344\277\241\345\217\267"
.LC4:
	.string	"\346\210\221\346\230\2575\345\217\267\344\277\241\345\217\267"
.LC5:
	.string	"\346\210\221\346\230\2576\345\217\267\344\277\241\345\217\267"
.LC6:
	.string	"\346\210\221\346\230\2577\345\217\267\344\277\241\345\217\267"
	.text
	.globl	handler
	.type	handler, @function
handler:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	cmpl	$7, -4(%rbp)
	ja	.L1
	movl	-4(%rbp), %eax
	movq	.L4(,%rax,8), %rax
	jmp	*%rax
	.section	.rodata
	.align 8
	.align 4
.L4:
	.quad	.L1
	.quad	.L3
	.quad	.L5
	.quad	.L6
	.quad	.L7
	.quad	.L8
	.quad	.L9
	.quad	.L10
	.text
.L3:
	movl	$.LC0, %edi
	call	puts
	jmp	.L1
.L5:
	movl	$.LC1, %edi
	call	puts
	jmp	.L1
.L6:
	movl	$.LC2, %edi
	call	puts
	jmp	.L1
.L7:
	movl	$.LC3, %edi
	call	puts
	jmp	.L1
.L8:
	movl	$.LC4, %edi
	call	puts
	jmp	.L1
.L9:
	movl	$.LC5, %edi
	call	puts
	jmp	.L1
.L10:
	movl	$.LC6, %edi
	call	puts
	nop
.L1:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	handler, .-handler
	.section	.rodata
.LC7:
	.string	"hello"
	.text
	.globl	func
	.type	func, @function
func:
.LFB3:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movl	$.LC7, %edi
	movl	$0, %eax
	call	printf
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	func, .-func
	.section	.rodata
.LC8:
	.string	"11"
	.text
	.globl	main
	.type	main, @function
main:
.LFB4:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	$1, -4(%rbp)
	movl	-4(%rbp), %eax
	movl	$func, %esi
	movl	%eax, %edi
	call	signal
.L13:
	movl	$.LC8, %edi
	movl	$0, %eax
	call	printf
	movl	$1, %edi
	call	sleep
	jmp	.L13
	.cfi_endproc
.LFE4:
	.size	main, .-main
	.ident	"GCC: (GNU) 4.8.5 20150623 (Red Hat 4.8.5-44)"
	.section	.note.GNU-stack,"",@progbits
