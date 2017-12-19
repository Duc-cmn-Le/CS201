	; void setVal(str1 *p, str2 *q)
	; p in %rdi, q in %rsi

.setVal:
	movslq	8(%rsi), %rax
	addq	32(%rsi), %rax
	movq	%rax, 184(%rdi)
	ret
	

