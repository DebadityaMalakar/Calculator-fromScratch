section .text
global sub_numbers

sub_numbers:
    ; Arguments: eax = low1, edx = high1
    ;            ebx = low2, ecx = high2
    sub eax, ebx        ; Subtract lower 32 bits
    sbb edx, ecx        ; Subtract higher 32 bits with borrow
    ret
