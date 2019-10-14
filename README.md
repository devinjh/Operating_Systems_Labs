Authors: Andrew Robinson, Tristan Hess, Devin Hopkins

In this lab we implemented a way to take commands and execute them. We added a total of 12 commands (boot, clrs, echo, copy, ddir, exec, help, prnt, remv, senv, show, and twet). In this lab, however, we only implemented 3 of them (boot, clrs, and echo).

When implmenting boot, all we did was call interrupt(25, 0, 0, 0, 0).

When implementing clrs, all we did was call interrupt(33, 12, 0, 0, 0).

Lastly, when implementing echo, all we did was call interrupt(33, 0, "their argument", 0, 0) followed by another interrupt call but with "\r\n" instead of "their argument".

The rest if them simply display to the screen that they were called.

In order to get the program to display the call the correct function, we created a function called "shellCOmmand" that takes the command the user inputs as well as any arguments that go along with that command. The function then splits up any fuinction name from the arguments. Then, it searches for the command the user entered. If it doesn't find it, "bad command or file name" is displayed and the user is asked for another command. If the command is found, the appropriate function is called, and, should the command being called requires arguments, the arguments are passed to the function as well.

We also implemented functions to help keep track of the commands, split up the command name and the argument(s), and a function that compares two strings (to compare the command names).

In order to run this program. First run the shell script
./compileOS
then run
echo 'c' | bochs -f bdos.txt
to begin BlackDOS
