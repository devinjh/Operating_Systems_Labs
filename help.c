/*       Help program         */
/* Created by Andrew Robinson,*/ 
/* Tristan Hess, Devin Hopkins*/
/* for use in blackdos 2019   */

#include "blackdos.h"

void main()
{
	char * input;

	PRINTS("\r\n\0");
	PRINTS(" ______________________________________________________\r\n\0");
	PRINTS("|                        Page 1                        |\r\n\0");
	PRINTS("|                       Commands                       |\r\n\0");
	PRINTS("|  boot                                                |\r\n\0");
	PRINTS("|  - Restarts the computer                             |\r\n\0");
	PRINTS("|  clrs                                                |\r\n\0");
	PRINTS("|  - Clears the screen                                 |\r\n\0");
	PRINTS("|  echo [arg]                                          |\r\n\0");
	PRINTS("|  - Writes the argument to the standard output        |\r\n\0");
	PRINTS("|  copy [file1] [file2]                                |\r\n\0");
	PRINTS("|  - Copies contents of file1 to file2                 |\r\n\0");
	PRINTS("|  ddir                                                |\r\n\0");
	PRINTS("|  - Prints the file directory                         |\r\n\0");
	PRINTS("|  exec [file]                                         |\r\n\0");
	PRINTS("|  - Executes given program                            |\r\n\0");
	PRINTS("|  - Must be called with the first letter as capital   |\r\n\0");
	PRINTS("|  Options:                                            |\r\n\0");
	PRINTS("|    arg:    argument to be output                     |\r\n\0");
	PRINTS("|    file:   filename of the desired file              |\r\n\0");
	PRINTS("|                                                      |\r\n\0");
	PRINTS("|_____________Press [ENTER] For Next Page______________|\r\n\0");

	while(*input != 0xD)
	{
		*input = interrupt(22, 0, 0, 0, 0);
	}
	*input = 0x0;

	PRINTS("\r\n\0");
	PRINTS(" ______________________________________________________\r\n\0");
	PRINTS("|                        Page 2                        |\r\n\0");
	PRINTS("|                       Commands                       |\r\n\0");
	PRINTS("|  help                                                |\r\n\0");
	PRINTS("|  - Displays help manual of possible commands         |\r\n\0");
	PRINTS("|  prnt [file]                                         |\r\n\0");
	PRINTS("|  - Sends contents of given file to printer           |\r\n\0");
	PRINTS("|  remv [file]                                         |\r\n\0");
	PRINTS("|  - Deletes file with the given file                  |\r\n\0");
	PRINTS("|  senv                                                |\r\n\0");
	PRINTS("|  - Set environment variables                         |\r\n\0");
	PRINTS("|  show [file]                                         |\r\n\0");
	PRINTS("|  - Displays contents of the given file               |\r\n\0");
	PRINTS("|  twet [file]                                         |\r\n\0");
	PRINTS("|  - Create a text file with the given filename        |\r\n\0");
	PRINTS("|  Options:                                            |\r\n\0");
	PRINTS("|    file:   filename of desired file                  |\r\n\0");
	PRINTS("|                                                      |\r\n\0");
	PRINTS("|                                                      |\r\n\0");
	PRINTS("|                                                      |\r\n\0");
	PRINTS("|_____________Press [ENTER] to close help______________|\r\n\0");

	while(*input != 0xD)
	{
		*input = interrupt(22, 0, 0, 0, 0);
	}

	END;

}
