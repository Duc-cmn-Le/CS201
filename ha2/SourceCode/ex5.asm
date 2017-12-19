.L6:
	movq	(%rdx), %rcx
	movq	(%rax), %rsi
	movq	%rsi, 	(%rdx)
	movq	%rcx, 	(%rax)
	addq	$8, %rdx
	addq	$120, %rax
	cmpq	%rdi, %rax
	jne	.L6

