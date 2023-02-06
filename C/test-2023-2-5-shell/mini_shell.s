	.file	"mini_shell.c"
	.section	.rodata
.LC0:
	.string	"[ls@mydir]## "
.LC1:
	.string	" "
.LC2:
	.string	"cd"
	.align 8
.LC3:
	.string	"\347\255\211\345\276\205\345\255\220\350\277\233\347\250\213\346\210\220\345\212\237\357\274\201\351\200\200\345\207\272\347\240\201\357\274\232%d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$1568, %rsp
	leaq	-1040(%rbp), %rsi
	movl	$0, %eax
	movl	$128, %edx
	movq	%rsi, %rdi
	movq	%rdx, %rcx
	rep stosq
.L8:
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	movq	stdout(%rip), %rax
	movq	%rax, %rdi
	call	fflush
	movq	stdin(%rip), %rdx
	leaq	-1040(%rbp), %rax
	movl	$1024, %esi
	movq	%rax, %rdi
	call	fgets
	leaq	-1040(%rbp), %rax
	movq	%rax, %rdi
	call	strlen
	subq	$1, %rax
	movb	$0, -1040(%rbp,%rax)
	movq	$.LC1, -16(%rbp)
	leaq	-1568(%rbp), %rsi
	movl	$0, %eax
	movl	$64, %edx
	movq	%rsi, %rdi
	movq	%rdx, %rcx
	rep stosq
	movl	$1, -4(%rbp)
	movq	-16(%rbp), %rdx
	leaq	-1040(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strtok
	movq	%rax, -1568(%rbp)
	jmp	.L2
.L3:
	addl	$1, -4(%rbp)
.L2:
	movq	-16(%rbp), %rax
	movq	%rax, %rsi
	movl	$0, %edi
	call	strtok
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	movq	%rax, -1568(%rbp,%rdx,8)
	movl	-4(%rbp), %eax
	cltq
	movq	-1568(%rbp,%rax,8), %rax
	testq	%rax, %rax
	jne	.L3
	movq	-1568(%rbp), %rax
	movl	$.LC2, %esi
	movq	%rax, %rdi
	call	strcmp
	testl	%eax, %eax
	jne	.L4
	movq	-1560(%rbp), %rax
	testq	%rax, %rax
	je	.L5
	movq	-1560(%rbp), %rax
	movq	%rax, %rdi
	call	chdir
	nop
.L5:
	jmp	.L8
.L4:
	call	fork
	testl	%eax, %eax
	jne	.L7
	movq	-1568(%rbp), %rax
	leaq	-1568(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	execvp
	movl	$0, %edi
	call	exit
.L7:
	movl	$0, -1044(%rbp)
	leaq	-1044(%rbp), %rax
	movl	$0, %edx
	movq	%rax, %rsi
	movl	$-1, %edi
	call	waitpid
	movl	-1044(%rbp), %eax
	sarl	$8, %eax
	movzbl	%al, %eax
	movl	%eax, %esi
	movl	$.LC3, %edi
	movl	$0, %eax
	call	printf
	jmp	.L8
	.cfi_endproc
.LFE2:
	.size	main, .-main
	.ident	"GCC: (GNU) 4.8.5 20150623 (Red Hat 4.8.5-44)"
	.section	.note.GNU-stack,"",@progbits
