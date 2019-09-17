﻿/* ACADEMIC INTEGRITY PLEDGE                                              */
/*                                                                        */
/* - I have not used source code obtained from another student nor        */
/*   any other unauthorized source, either modified or unmodified.        */
/*                                                                        */
/* - All source code and documentation used in my program is either       */
/*   my original work or was derived by me from the source code           */
/*   published in the textbook for this course or presented in            */
/*   class.                                                               */
/*                                                                        */
/* - I have not discussed coding details about this project with          */
/*   anyone other than my instructor. I understand that I may discuss     */
/*   the concepts of this program with other students and that another    */
/*   student may help me debug my program so long as neither of us        */
/*   writes anything during the discussion or modifies any computer       */
/*   file during the discussion.                                          */
/*                                                                        */
/* - I have violated neither the spirit nor letter of these restrictions. */
/*                                                                        */
/*                                                                        */
/*                                                                        */
/* Signed: Andrew Robinson, Tristan Hess, Devin Hopkins Date:9-11-2019    */
/*                                                                        */
/*                                                                        */
/* 3460:4/526 BlackDOS2020 kernel, Version 1.03, Fall 2019.               */

void handleInterrupt21(int, int, int, int);
void printLogo();

void main()
{
  int i;
  char buffer[80];
  for(i = 0; i < 80; ++i)buffer[i] = 0;

  makeInterrupt21();
  printLogo();
  interrupt(33, 0, "Hello world from Andrew :)\r\n\0", 1, 0);
  interrupt(33, 14, i, 0, 0);
  interrupt(33, 13, i, 0, 0);
  while(1);
}

void printLogo()
{
  interrupt(33, 0, "       ___   `._   ____  _            _    _____   ____   _____ \r\n\0", 0, 0);
  interrupt(33, 0, "      /   \\__/__> |  _ \\| |          | |  |  __ \\ / __ \\ / ____|\r\n\0", 0, 0);
  interrupt(33, 0, "     /_  \\  _/    | |_) | | __ _  ___| | _| |  | | |  | | (___ \r\n\0", 0, 0);
  interrupt(33, 0, "    // \\ /./      |  _ <| |/ _` |/ __| |/ / |  | | |  | |\\___ \\ \r\n\0", 0, 0);
  interrupt(33, 0, "   //   \\\\        | |_) | | (_| | (__|   <| |__| | |__| |____) |\r\n\0", 0, 0);
  interrupt(33, 0, "._/'     `\\.      |____/|_|\\__,_|\\___|_|\\_\\_____/ \\____/|_____/\r\n\0", 0, 0);
  interrupt(33, 0, " BlackDOS2020 v. 1.03, c. 2019. Based on a project by M. Black. \r\n\0", 0, 0);
  interrupt(33, 0, " Author(s): Andrew Robinson, Tristan Hess, Devin Hopkins.\r\n\r\n\0", 0);
}

void readInt(int *n)
{
  char buffer[80];
  int i;
  for(i = 0; i < 80; ++i)buffer[i] = 0;
  interrupt(33, 1, buffer, 0, 0); /* read in string, to be converted*/

  *n = 0;
  i = 0;
  while(buffer[i] != '\0') {
    *n *= 10;
    *n += buffer[i] - 48;
    ++i;
  }

}

void writeInt(int n, int cx)
{
  char numToPrint[6];/* All are 5 digit numbers*/
  int i;

  numToPrint[5] = '\0';
  for(i = 4; i >= 0; --i) {
    numToPrint[i] = mod(n, 10) + 48;
    n = div(n, 10);
  }

  interrupt(33, 0, numToPrint, cx, 0);
}

/* read string expects buffer to be an empty char[80]*/
void readString(char *buffer)
{
  int i = 0;
  char *input;

  while(i != 79) {
    input = interrupt(22, 0, 0, 0, 0);

    if(input == 0xD) { /* if return key is pressed*/
      buffer[i] = '\0';/* add 0x0 to the end of the string */
      return;
    }
    else if(input == 0x8 && i > 0) {  /* if backspace was pressed*/
      interrupt(16,  14 * 256 + input, 0, 0, 0); /* print backspace (move the cursor back)*/
      i--; /* go to last char in the buffer*/
      buffer[i] = ' '; /* change it to a space*/
      interrupt(16,  14 * 256 + buffer[i], 0, 0, 0); /* print the space (this looks clean)*/
      interrupt(16, 14 * 256 + input, 0, 0, 0); /* move the cursor back again*/
    }
    else if(input != 0x0) {
      interrupt(16,  14 * 256 + input, 0, 0, 0);
      buffer[i] = input;
      i++;
    }
  }

  buffer[79] = '\0'; /* if you read 79 characters, set 80 to '\0' */
  return;
}

void printString(char *c, int d)
{
  switch(d) {
  case 0:/* print to the console*/
    while(*c != '\0') {
      interrupt(16, 14 * 256 + *c, 0, 0, 0);
      c++;
    }
    break;
  case 1:/* print to the printer*/
    while(*c != '\0') {
      interrupt(23, *c, 0, 0, 0);
      c++;
    }
    break;
  case 2:/* print a single character to the console*/
    interrupt(16, 14 * 256 + *c, 0, 0, 0);
    break;
  }
  return;
}

int mod(int a, int b)
{
  int x = a;
  while (x >= b) x = x - b;
  return x;
}

int div(int a, int b)
{
  int q = 0;
  while (q * b <= a) q++;
  return (q - 1);
}

void handleInterrupt21(int ax, int bx, int cx, int dx)
{
  //return;
  switch(ax) {
  case 0:
    printString(bx, cx);
    break;
  case 1:
    readString(bx);
    break;
  case 13:
    writeInt(bx, cx);
    break;
  case 14:
    readInt(bx);
    break;
  default:
    printString("General BlackDOS error.\r\n\0", 0);
  }
}