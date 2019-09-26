Authors: Andrew Robinson, Tristan Hess, Devin Hopkins

In order to run this program. First run the shell script
./compileOS
then run
echo 'c' | bochs -f bdos.txt
to begin BlackDOS

The main purpose of lab 3 was to write 3 functions: readSector(), writeSector(), and clearScreen().

Creating readSector(): The read sector is a function that reads in data from a disk sector using interrupt 19.

Creating writeSector(): The write sector is a function that writes data to a disk sector using interrupt 19.

Creating clearScreen(): The clear screen is a function that not only clears the screen, but also changes the color of the foreground and background. The first task it completes is to clear the screen. It does this by printing out 24 new line characters. After this, it places the cursor at the top right of the screen. Finally, to change the color of the background and foreground, it calls interrupt 16.
