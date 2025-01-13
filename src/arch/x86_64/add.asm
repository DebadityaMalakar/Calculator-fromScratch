section .text
global add_numbers

add_numbers:
    ; rdi = num1, rsi = num2
    add rdi, rsi
    mov rax, rdi
    ret
