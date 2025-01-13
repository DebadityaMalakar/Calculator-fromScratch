section .text
global mul_numbers

mul_numbers:
    ; rdi = num1, rsi = num2
    imul rdi, rsi
    mov rax, rdi
    ret
