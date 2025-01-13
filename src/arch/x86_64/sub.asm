section .text
global sub_numbers

sub_numbers:
    ; rdi = num1, rsi = num2
    sub rdi, rsi
    mov rax, rdi
    ret
