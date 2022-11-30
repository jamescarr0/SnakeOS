ENTRY(_start)
OUTPUT_FORMAT(binary)
SECTIONS
{
    /* Kernel is loaded 1 megabyte into memory. 1024*1024 = 0x100000
     * Sections start at 1mb (0x100000).  When objects are linked the
     * origin will start at 0x100000
     */

     /* Align Memory sections to 4096 bytes */

     /* Place an assembly section at the end: Our assembly CODE is unaligned
      * Placing at the end will not have an effect on any compiled
      * C functions.  The compiler will automatically align C to
      * 16 bytes. NOTE: While asm code is unaligned, the asm section is aligned
      */

    . = 1M;

    .text : ALIGN(4096)
    {
        *(.text)
    }

    .rodata : ALIGN(4096)
    {
        *(.rodata)
    }

    .data : ALIGN(4096)
    {
        *(.data)
    }

    .bss : ALIGN(4096)
    {
        *(.bss)
    }

    .asm : ALIGN(4096)
    {
        *.(.asm)
    }
}