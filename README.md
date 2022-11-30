# Simple OS

## An operating system written in C and built from scratch.

SimpleOS is a 32-bit operating system for X86.

<hr>

### Compile & Run

Install qemu-system-i386

Add the path to your cross-compiler and linker to the top of the Makefile.

For example:

`CC=i686-elf-gcc`
`LD=i686-elf-ld`

Visit [OS Dev GCC Cross Compiler](https://wiki.osdev.org/GCC_Cross-Compiler) for more information and instructions on
how to build a cross-compiler.

Then simply `make` and `make run` OR start qemu manually `qemu-system-i386 -hda ./bin/os.bin`

The most current `os.bin` build is also available in the project `bin` directory.

<hr>

### Current status :nut_and_bolt:

SimpleOS successfully boots into 32 bit protected mode and calls the kernel main function (kernel.c). The GDT and IDT is
loaded and interrupts have been enabled. The PIC (Programmable Interrupt Controller) has been re-mapped to avoid
software and hardware conflicts. Paging is enabled and address can now be mapped to provide virtual addresses.

#### Working Interrupts

- ISR_ZERO: Divide by zero error. <br>
- Int 21 - Keyboard interrupt and triggers on key pressed.

<hr>

### Improvements.

#### Heap

Table based entry method to track the allocation/de-allocation of memory. OSDev has this as the worst performing method,
however it is the easiest and less complex method to implement.

less complex != my idea of less complex :joy: :sweat_smile:

Kmalloc currently returns a minimum size of 4096 bytes regardless. kmalloc(n) where n < 4096 will always allocate 4096
bytes at a minimum. If n = 4097, then 8219 bytes will be allocated and so on. Allocation is based on 4096 blocks.

#### Disk Driver

SimpleOS uses ATA PIO Mode which use a tremendous amount of CPU resources. Every byte transferred between disk and CPU
is sent through the CPU IO Port Bus, and NOT straight to memory.

<hr>

### Work in progress

:x: Implement a filesystem
:white_check_mark: - Parse and tokenise an absolute path string

<hr>

### Update log:

:white_check_mark: Real mode 16 bit bootloader

:white_check_mark: Switch to 32 bit protected mode.

:white_check_mark: Abstracted to C. Load kernel into memory and call main() (kernel.c)

:white_check_mark: Implement and load the global descriptor table.

:white_check_mark: Implement and load the Interrupt Descriptor table, created a working keyboard interrupt.

:white_check_mark: Enabled interrupts.

:white_check_mark: Implement a print function to send character bytes to video memory for output to screen.

:white_check_mark: Implement the heap and memory allocation functions kmalloc, kzalloc and kfree.

:white_check_mark: Implement paging using 4kb pages.

:white_check_mark: Implement a disk driver to read from the disk. (ATA PIO Mode and LBA28)

:white_check_mark: - Parse and tokenise an absolute path string
