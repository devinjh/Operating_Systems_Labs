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
bcc -ansi -c -o shell.o shell.c
# link the shell
ld86 -o Shell -d shell.o basm.o
# compile lab7.c
bcc -ansi -c -o lab7.o lab7.c
# link lab7
ld86 -o Lab7 -d lab7.o basm.o
# put shell on the disk and store the program name in dir
./loadFile Shell
# put ddir on the disk and in the dir (for shell command ddir)
./loadFile Ddir
# put Stenv on the disk and in the dir (for shell command senv)
./loadFile Stenv
# put Fib on the disk and in the dir
./loadFile Fib
# put Help on the disk and in the dir
./loadFile Help
# put both of these programs onto the disk and the directory per request
./loadFile T3
./loadFile Cal
# put Lab7 programs on the disk in the dir
./loadFile Lab7
./loadFile fpc02
