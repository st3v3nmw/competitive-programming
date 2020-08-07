	.text
.LC0:
	.string	"%d\n"
printint:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movl	-4(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	nop
	leave
	ret

	.globl	main
	.type	main, @function
main:
	pushq	%rbp
	movq	%rsp, %rbp
	movq	$3, %r8
	movq	$5, %r9
	imulq	%r8, %r9
	movq	$9, %r8
	addq	%r9, %r8
	movq	$16, %r9
	subq	%r9, %r8
	movq	%r8, %rdi
	call	printint
	movl	$0, %eax
	popq	%rbp
	ret
