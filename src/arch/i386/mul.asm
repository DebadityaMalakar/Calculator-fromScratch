section .text
global mul_numbers

mul_numbers:
    ; Arguments: eax = low1, edx = high1
    ;            ebx = low2, ecx = high2
    ; Multiply lower 32 bits
    imul ebx
    mov edx, 0          ; Clear high part
    ret
