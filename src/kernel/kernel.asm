[BITS 32]
global _start

extern main

CODE_SEG equ 0x08
DATA_SEG equ 0x10

_start:
    mov ax, DATA_SEG
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov ebp, 0x00200000           
    mov esp, ebp            ; Set stack pointer further in memory, as we can 
                            ; now access more memory

check_A20_is_on:            ; Check A20 Line is enabled. Legacy Pain!
    pushad
    mov edi, 0x112345       ; Odd megabyte address
    mov esi, 0x012345       ; Even megabyte address
    mov [esi], esi          ; Store the value of esi (0x112345) into the location 
    mov [edi], edi          ; pointed to by esi.  Same for edi.
    cmpsd                   ; (if A20 line is cleared the two pointers would point 
                            ; to the address 0x012345 that would contain 0x112345 (edi)) 
                            ;compare addresses to see if the're equivalent.
    popad
    jne PModeMain           ; A20 has been enabled.
    
    ; A20 NOT ENABLED, use fast A20 Gate to quickly enable A20 line.
    ; A20 is an old legacy 'wrap around feature'
    in al, 0x92
    or al, 2
    out 0x92, al

PModeMain:
    call main               ; kernel.c
    jmp $

                            ; Force Alignment, will always divide into 16 bytes.
times 512 - ($-$$) db 0     ; As we are now mixing C code with assembly we need to make
                            ; sure our assemby stays in alignment.  The C Compiler aligns
                            ; to 16 bytes by default.  512 aligns into 16 perfectly fine
                            ; and will solve any alignment issues we may encounter with
                            ; mixing C and asm.
    