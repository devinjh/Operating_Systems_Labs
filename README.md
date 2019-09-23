Authors: Andrew Robinson, Tristan Hess, Devin Hopkins

In order to run this program. First run the shell script
./compileOS
then run
echo 'c' | bochs -f bdos.txt
to begin BlackDOS

The main purpose of lab 2 was to write 3 new function readString,
readInt, and writeInt.

Creating readString:
Read string is a function that keeps the user in a loop while it checks for three main actions the user could do. The first is typing the enter key. When this is done the user is finished typing their input. It is expected for a new line to begin and for the carriage to be returned to the left side of the console. Also you must append a NULL terminator to the string before returning. 

The second input you expect from the user is a backspace. Note that backspacing on an empty buffer should do nothing, so we first check if our index is less than 1. If our index is not less than 1, then we have something in the buffer to remove and proceed with the song and dance of making backspace look pretty. First we move the cursor back one position. Second we print a blank space to that position, however this moves our cursor forwards one position, so we must third move our cursor back on position again. Finally, we can replace that position in the buffer with a space. 

The third input is a character was typed. This is the most trivial, we simply place the char inside of the buffer and print it to the console. Then incriment the index. Once the index is at 79 we have filled the buffer and we place a NULL Terminator in the 80th spot of the buffer, print a new line and a carriage return, and leave the function.

Creating readInt:
Read int begins by calling readString and then processes that string into an integer, which is stored into the integer that is passed as an parameter. Whenever an "error" is found, the integer is set to zero and the function returns. This can be thought of as an error value. However, this ideology constrains the user implimentation when zero is a valid input. While the string buffer is filled with valid integers, the integers are placed in the ones place of the return variable "n". Whenever a new integer is placed, first all the existing integers are shifted to the left one decimal place by multiplying by 10.

example:
string buffer = "1025\0"
integer n = 0

Progression of n is as follows:
	iteration 1
	multiply by 10     n = 0
	add next integer   n = 1

	interation 2
	multiply by 10     n = 10
	add next integer   n = 10

	iteration 3
	multiply by 10     n = 100
	add next integer   n = 102

	iteration 4
	multiply by 10     n = 1020
	add next integer   n = 1025

	return

Creating writeInt:
Write int has a slightly simpler implimentation than readInt since the parameters do not need to be checked. Since an integer can only be up to 5 digits long, we create a character array that is 6 long (one extra slot for the NULL terminator). There is also one special case when writing an integer, that is when the integer is equal to zero. Therefore, first we check if the integer is zero, if it is we print it and return. If the integer is not zero we need to check how many digits it is. This is done in a while loop, where we continously divide by 10 until the number is zero. We then use this new information to set the NULL terminator. Finally we fill the rest of the string from right to left with the ones place of the integer. Then divide by 10 to shift each integer to the right by one decimal place.

example:
 integer to write, n = 1234
 integer size = 0
 return string = "      "

 divive the integer by 10 until it reaches zero, incriment size each time
 	divive by 10 n = 123
 	size = 1

 	divide by 10 n = 12
 	size = 2

 	divide by 10 n = 1
 	size = 3

 	divice by 10 n = 0
 	size = 4 
 	END WHILE

 	set NULL terminator at [4]
 	string = "    '\0' "

 from right to left, fill the string with the ones place of the integer, then divide by 10
 	using mod(n,10) string = "   4'\0' "
 	using div(n,10  n = 123

 	using mod(n,10) string = "  34'\0' "
 	using div(n,10  n = 12
 	
 	using mod(n,10) string = " 234'\0' "
 	using div(n,10  n = 1
 	
 	using mod(n,10) string = "1234'\0' "
 	using div(n,10  n = 0
 	
 	print(string)