Authors: Andrew Robinson, Tristan Hess, Devin Hopkins

In order to run this program. First run the shell script
./compileOS
then run
echo 'c' | bochs -f bdos.txt
to begin BlackDOS



We decided to use a while loop to handle output in the printString() function. We also handle the output to the printer or screen by a switch case statement, to ensure future cases can be added easily. We have replaced all function calls of printString with interrupt 33, including inside the printLogo() function.

Our work can be verified by opening kernel.c in a text editor to see that printString() has been replaced with interrupt 33. Text output can be verified by running the kernel in bochs to view the BlackDOS logo, and opening printer.out to view the "Hello world" statement with our names.