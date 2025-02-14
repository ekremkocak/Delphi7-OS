[BITS 32]
org 0

section .data
    welcome db 'Welcome to Hex File!', 0x0D, 0x0A, 0

section .bss

section .text
global _start

_start:
    ; Registers.eax = 5
    mov eax, 5
    mov ebx, 20

    ; Registers.esi = address of welcome
    mov esi, welcome

    ; Custom interrupt or function call
    int 64 ; This is for demonstration. Replace with your specific OS interrupt

ret
    