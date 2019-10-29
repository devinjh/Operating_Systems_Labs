Authors: Andrew Robinson, Tristan Hess, and Devin Hopkins

In this lab we introduced an extremely basic file system.

To begin, we wrote a function called readFile(). This function received a name of a file, a buffer, and a size. This function simply grabs every filename by calling a previously implemented function called readSector(). It calls the readSector() function and grabs sector 257, the disk directory sector. Therefore, the entire disk directory (all of the filenames) are loaded into the buffer. The readFile() function then scans through the buffer, attempting to match the filename given as an argument to a filename in the disk directory. If it's successful, readFile() function calls readSector() again, but this time specifies the sector that the file with the filename it was searching for is at. The contents of the file are then displayed. If it doesn't find the file an error message is displayed, and nothing is loaded.

We next had to implement a way to handle error messages. We did this by adding a case to the handleInterrupt21() function. If an error message is to be displayed, interrupt() is called with an appropriate ax (or first integer). This then calls a function called error(). This error() function we had to implement. This is a rather simple function, as it takes an integer and then displays an error message based on the integer it was given.

We rewrote our previously implemented function runProgram(). It now takes a filename in addition to an integer segment. This function now simply calls readFile() with the appropriate arguments instead of calling readSector().

Lastly, we updated our shell by implementing several of the previously non-implemented commands. These commands were ddir, exec, help, prnt, senv, and show. All of these commands used the file directory we set up in the kernel, excluding help. Help was derived by simply creating a user's manual to our kernel.

In order to run this program. First run the shell script
./compileOS.sh
./compileHelp.sh
then run
echo 'c' | bochs -f bdos.txt
to begin BlackDOS
