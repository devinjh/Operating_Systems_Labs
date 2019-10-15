# set floppy to all zeros
dd if=/dev/zero of=floppya.img bs=512 count=2880
# put bootload into floppy at sector 1
dd if=bootload of=floppya.img bs=512 count=1 conv=notrunc
# put map into floppy at sector 256
dd if=map of=floppya.img bs=512 count=1 seek=256 conv=notrunc
# compile kernel
bcc -ansi -c -o kernel.o kernel.c
# link kernel
ld86 -o kernel -d kernel.o kasm.o
# put kernel into floppy at sector 259
dd if=kernel of=floppya.img bs=512 conv=notrunc seek=259
# put config file into floppy at sector 258, config has background and foreground colors
dd if=config of=floppya.img bs=512 count=1 seek=258 conv=notrunc
# compile the shell
bcc -ansi -c -o Shell.o Shell.c
# link the shell
ld86 -o Shell -d Shell.o basm.o
# put the shell program in the floppy at sector 30, give it 10 blocks of memory
dd if=Shell of=floppya.img bs=512 count=10 seek=30 conv=notrunc
