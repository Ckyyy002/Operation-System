prepare:
	mkdir -p bin

bootloader:
	nasm -f bin src/bootloader.asm -o bin/bootloader.bin
	nasm -f as86 src/kernel.asm -o bin/kernel-asm.o

stdlib:
	bcc -ansi -c -Iinclude src/std_lib.c -o bin/std_lib.o

kernel:
	bcc -ansi -c -Iinclude src/kernel.c -o bin/kernel.o

link:
	ld86 -o bin/kernel.bin -d bin/kernel.o bin/std_lib.o bin/kernel-asm.o /usr/lib/bcc/libc.a
	dd if=/dev/zero of=bin/floppy.img bs=512 count=2880
	dd if=bin/bootloader.bin of=bin/floppy.img bs=512 count=1 conv=notrunc
	dd if=bin/kernel.bin of=bin/floppy.img bs=512 seek=1 count=15 conv=notrunc

build: prepare bootloader stdlib kernel link

run:
	bochs -f bochsrc.txt
