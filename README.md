Authors: Andrew Robinson, Tristan Hess, Devin Hopkins

In order to run this program. First run the shell script
./compileOS
then run
echo 'c' | bochs -f bdos.txt
to begin BlackDOS

For this lab, we created two functions, a stop() and a runProgram() function.

The runProgram() function does what is the function name says; it runs a program. It takes 3 parameters: an integer indicating which sector the program you want to run is starting in, an integer that tells how many sectors the program consumes, and lastly an integer indicating where you would like the program to run. In this function, a character arrray is loaded with the program from the disk. The segment is then multiplied by 0x1000 to derive the base location. the entire char array (which now contains the program) is put into memory using a provided function: putInMemory(). After the program has been put into memory, the program is then launched using another provided function: launchProgram().

The other function we created is the stop() funciton. This funciton does just what it says it's going to do. If a program doesn't have a nice way to stop written into it, this stop() function allows the program to stop naturally and the operating system to continue naturally as well.
