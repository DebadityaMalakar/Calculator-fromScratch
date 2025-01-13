section .text
global add_numbers

add_numbers:
    ; Arguments: eax = low1, edx = high1
    ;            ebx = low2, ecx = high2
    add eax, ebx        ; Add lower 32 bits
    adc edx, ecx        ; Add higher 32 bits with carry
    ret
