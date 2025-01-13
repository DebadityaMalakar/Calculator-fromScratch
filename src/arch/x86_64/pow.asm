section .text
global div_numbers

div_numbers:
    ; rdi = dividend, rsi = divisor
    xor rdx, rdx
    div rsi
    mov rax, rdi
    ret
