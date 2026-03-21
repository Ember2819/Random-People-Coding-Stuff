# By Ember2819, google, and random people on the internet.... What are we doing????

# C compiler
CC = clang
# Secondary C compiler
CC2 = gcc
# Assembler (for boot.s)
AS = nasm
# Linker
LD = ld
# Truncate (to make the kernel.bin divisible by 512)
TRUNCATE = truncate
TRUNC_AMNT = 360448
# Objcopy (to translate elf to bin)
OBJCOPY = objcopy
OBJCOPY_ARGS = -O binary

CC_FLAGS = -m32 -ffreestanding -nostdlib -fno-builtin -fno-stack-protector -c

AS_FLAGS = -f bin

LD_FLAGS = -m elf_i386 -T linker.ld

KERNEL_OBJECTS = kernel/kernel.o kernel/ports.o kernel/mem.o
DRIVER_OBJECTS = kernel/drivers/vga.o kernel/drivers/keyboard.o

# Builds the final disk image
all: os.img

%.o: %.c
# If no GCC detected, use clang
	$(CC) $(CC_FLAGS) $< -o $@ || $(CC2) $(CC_FLAGS) $< -o $@

# Assemble the bootloader
bootloader/boot.bin: bootloader/boot.s
	$(AS) $(AS_FLAGS) $< -o $@

# Compile drivers

kernel/drivers/vga.o: kernel/drivers/vga.c
	$(CC) $(CC_FLAGS) $< -o $@ || $(CC2) $(CC_FLAGS) $< -o $@

kernel/drivers/keyboard.o:  kernel/drivers/keyboard.c
	$(CC) $(CC_FLAGS) $< -o $@ || $(CC2) $(CC_FLAGS) $< -o $@
kernel/ports.o: kernel/ports.c
	$(CC) $(CC_FLAGS) $< -o $@ || $(CC2) $(CC_FLAGS) $< -o $@
kernel/mem.o: kernel/mem.c
	$(CC) $(CC_FLAGS) $< -o $@ || $(CC2) $(CC_FLAGS) $< -o $@
# Link all kernel objects 
kernel.elf: $(KERNEL_OBJECTS) $(DRIVER_OBJECTS)
	$(LD) $(LD_FLAGS) $(KERNEL_OBJECTS) $(DRIVER_OBJECTS) -o kernel.elf
kernel.bin: kernel.elf
	$(OBJCOPY) $(OBJCOPY_ARGS) kernel.elf kernel.bin
	$(TRUNCATE) -s $(TRUNC_AMNT) kernel.bin
os.img: bootloader/boot.bin kernel.bin
	cat bootloader/boot.bin kernel.bin > os.img

# Launch the image in QEMU
run: os.img
	qemu-system-i386 -drive format=raw,file=os.img

clean:
	rm -f $(KERNEL_OBJECTS) kernel.bin bootloader/boot.bin os.img

.PHONY: all run clean
