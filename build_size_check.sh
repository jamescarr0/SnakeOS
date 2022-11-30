#!/bin/bash

# Script to check the size of the kernel during the build
# load more sectores into ecx if kernel size exceeds sectors
# loaded.

FILE_SIZE=$(du -k ./bin/os.bin | cut -f1)

if [[ $FILE_SIZE -gt 51 ]]
then
    echo "ERROR: Kernel size exceeds loaded sectors, increase ecx (number of sectors to load) in boot.asm to ensure kernel is fully loaded into memory"
else
    FILE_SIZE+=kb
    echo "Kernel size ok [$FILE_SIZE]"
fi