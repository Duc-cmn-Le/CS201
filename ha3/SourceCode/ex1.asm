;long store_ele(long i, long j, long k, long *dest) 
;i in %rdi, j in %rsi, k in %rdx, dest in %rcx 
store_ele :
	leaq (%rsi,%rsi,2), %rax
	leaq (%rsi,%rax,4), %rax
	movq %rdi, %rsi
	salq $6, %rsi
	addq %rsi, %rdi
	addq %rax, %rdi
	addq %rdi, %rdx
	movq A(,%rdx,8), %rax
	movq %rax, (%rcx)
	movl $3640, %eax
	ret