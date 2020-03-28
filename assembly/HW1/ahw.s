.file	"ahw.s"	 #optional directive
.section	.rodata		 #required directives for rodata
.LC0:
	.string	"Please enter an integer on the next line, followed by enter:\n"
.LC1:
	.string	"%i"
.LC2:
	.string	"The value of x after adding 5 is: %i\n"

.data			#required for file scope data: read-write program data 			
			#of static storage class
x:
	.quad 0

.globl main		#required directive for every function
	.type	main, @function		 #required directive 
.text				 #required directive - code begins here
main:
	pushq	%rbp		#stack housekeeping #1
	movq	%rsp, %rbp		#stack housekeeping #2
	movq	$.LC0, %rdi		#address of string Please enter:\n to %rdi 
				# %rdi is location of 1st parameter
				# not pushing any caller saved registers because
				# there is no valuable data there
	movq 	$0, %rax		# C library ABI says %rax should be zero b4 call to printf
	call	printf	
	movq 	$x, %rsi		#mov the address of x to %rsi (2nd parameter)
	movq	$.LC1, %rdi		#address of string %i in %rdi (1st parameter)
	movq	$0, %rax		# to keep ABI happy
	call 	scanf
here:
	addq	$5, x		#add the constant 5 to what is stored in variable x
	movq	x, %rsi		#value of x to %rsi (2nd parameter)
	movq	$.LC2, %rdi		#address of string The value of to %rdi (1st param)
	movq	$0, %rax		# keep ABI happy
	call	printf
	movq	$0, %rax		#set return value to 0
	leave
	ret
	.size	main, .-main	 #required directive