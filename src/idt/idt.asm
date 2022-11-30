section .asm

global int21_wrapper
global no_interrupt

extern int_handler_21
extern no_interrupt_handler
extern enable_interrupts
extern disable_interrupts

enable_interrupts:          ; Enable inetrrupts 
    sti                     ; Can be called from C Code.
    ret

disable_interrupts:         ; Same as above
    cli
    ret

idt_load:
    push ebp
    mov ebp, esp

    mov ebx, [ebp+8] 
    lidt [ebx]
    
    pop ebp
    ret

; Interrupt service routine wrapper.
; An ISR is directly called by the CPU and MUST end with an iret opcode.
; C ends with ret.  The wrapper will call a C interrupt handler function
; and return the nessecary iret opcode once the interrupt is handled.
int21_wrapper:
    cli                     ; Disable interrupts
    pushad                  ; Save reg state
    cld                     ; C code following the sysV ABI requires DF to be clear on function directory
    
    call int_handler_21     ; Call ISR handler.
    
    popad                   ; Restore reg state.
    sti                     ; Enable interrupts
    iret                    ; iret opcode

no_interrupt:
    cli                     ; Disable interrupts
    pushad                  ; Save reg state
    cld                     ; C code following the sysV ABI requires DF to be clear on function directory
    
    call no_interrupt_handler     ; NO ISR assigned, call the no int handler.
    
    popad                   ; Restore reg state.
    sti                     ; Enable interrupts
    iret                    ; iret opcode