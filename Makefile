CC=i686-elf-gcc
LD=i686-elf-ld
NASM = nasm

FLAGS = -g -ffreestanding -falign-jumps -falign-functions -falign-labels
FLAGS += -falign-loops -fstrength-reduce -fomit-frame-pointer -fno-builtin
FLAGS += -finline-functions -Wno-unused-label -Wno-cpp  -std=gnu99 -m32
FLAGS += -Wno-unused-parameter -nostdlib -nostartfiles -nodefaultlibs -Wall -O0 -Iinc

SRCDIR = src
BUILDDIR = bin
OBJDIR = build

ASM_SRC = $(shell find $(SRCDIR) -name "*.asm" | egrep -v "boot|kernel")
C_SRC = $(shell find $(SRCDIR) -name "*.c" | grep -v ./kernel)

C_OBJS := $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.c.o, $(C_SRC))
ASM_OBJS := $(patsubst $(SRCDIR)/%.asm, $(OBJDIR)/%.asm.o, $(ASM_SRC))

default: $(ASM_OBJS) $(C_OBJS) boot kernelbin os

$(OBJDIR)/%.asm.o : $(SRCDIR)/%.asm
	@ echo !==== COMPILING ASM SRC:
	@ echo $^
	@ mkdir -p $(@D)
	$(NASM) -f elf -g $^ -o $@	

$(OBJDIR)/%.c.o : $(SRCDIR)/%.c
	@ echo !==== COMPILING C SRC: 
	@ echo $^
	@ mkdir -p $(@D)
	$(CC) $(FLAGS) -c $^ -o $@

boot: ./src/boot/boot.asm
	@ echo !==== COMPILING BOOT ASM: 
	@ echo $^
	nasm -f bin ./src/boot/boot.asm -o ./bin/boot.bin

./build/kernel/kernel.asm.o: src/kernel/kernel.asm
./build/kernel/kernel.o : src/kernel/kernel.c
	nasm -f elf -g ./src/kernel/kernel.asm -o ./build/kernel/kernel.asm.o
	$(CC) $(INCLUDES) $(FLAGS) -c ./src/kernel/kernel.c -o ./build/kernel/kernel.c.o

kernelbin: ./build/kernel/kernel.asm.o ./build/kernel/kernel.c.o
	@ echo !==== BUILDING KERNEL: 
	$(LD) -g -relocatable ./build/kernel/kernel.asm.o ./build/kernel/kernel.c.o $(C_OBJS) $(ASM_OBJS) -o $(OBJDIR)/$@.o
	$(CC) $(FLAGS) -T ./src/linker.ld -o ./bin/kernel.bin -ffreestanding -O0 -nostdlib $(OBJDIR)/$@.o

os:
	rm -rf ./bin/os.bin
	dd if=./bin/boot.bin >> ./bin/os.bin
	dd if=./bin/kernel.bin >> ./bin/os.bin

	./build_size_check.sh ./bin/os.bin

	# Pad out to 100 sectors.  Allows for a 51kb kernel (room for expansion)
	# So we dont have to keep calculating kernel size as its being built.
	# 100 Sectors will be loaded into memory from the bootloader.

	dd if=/dev/zero bs=512 count=100 >> ./bin/os.bin

run: default
	qemu-system-i386 -hda ./bin/os.bin

debug: ./bin/os.bin
	gdb-multiarch -ex "target remote | qemu-system-i386 -hda ./bin/os.bin -S -gdb stdio" \
		-ex "add-symbol-file ./build/kernelfull.o 0x100000"

clean:
	rm -rf ./bin/*.bin
	rm -rf ./build/kernel/*
	rm -rf ./build/kernelbin.o $(C_OBJS) $(ASM_OBJS)
