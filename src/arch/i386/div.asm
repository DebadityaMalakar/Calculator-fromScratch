section .text
global div_numbers

div_numbers:
    ; Arguments: edx:eax = dividend, ebx = divisor
    ; Combine high and low parts for 64-bit division
    div ebx             ; Divide
    ret
