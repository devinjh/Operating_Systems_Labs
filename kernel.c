/* ACADEMIC INTEGRITY PLEDGE                                              */
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
void runProgram(int, int, int);
void error(int);
void readFile(char* fname, char* buffer, int* size);

void main()
{
  /* THIS IS FROM LAB 5 */
  makeInterrupt21();
  printLogo();
  runProgram(30, 8, 2); /* run program at sector 30 */
  interrupt(33, 0, "Bad or missing command interpreter.\r\n\0", 0, 0);
  while(1);

  /* THIS IS FOR LAB 6 */
  /*
  char buffer[512];
  int size;
  makeInterrupt21();
  */

  /* Step 0 – config file */
  /*interrupt(33,2,buffer,258,1);
  interrupt(33,12,buffer[0]+1,buffer[1]+1,0);
  printLogo();
  */

  /* Step 1 – load and print msg file (Lab 3) */
  /*interrupt(33,3,”msg\0”,buffer,&size);
  interrupt(33,0,buffer,0,0);
  while (1);
  */
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

/* ax = 3 */
void readFile(char* fname, char* buffer, int* size)
{
  interrupt(33, 2, fname, buffer, size);
}

void runProgram(int start, int size, int segment)
{
  char buffer[4096];
  int i = 0;
  for(i = 0; i < 4096; ++i)buffer[i] = 0;

  interrupt(33, 2, buffer, start, size); /* read from disk the program*/
  segment *= 0x1000;

  for(i = 0; i < 4096; ++i) {
    putInMemory(segment, i, buffer[i]);
  }

  launchProgram(segment);
}

/* ax = 0 */
void printString(char *c, int d)
{
  switch(d) {
  case 0: /* print to the console */
    while(*c != '\0') {
      interrupt(16, 14 * 256 + *c, 0, 0, 0);
      c++;
    }
    break;
  case 1: /* print to the printer */
    while(*c != '\0') {
      interrupt(23, *c, 0, 0, 0);
      c++;
    }
    break;
  }
  return;
}

/* ax = 1 */
void readString(char *buffer)
{
  int i = 0;
  char *input;

  while(i != 79) {
    *input = interrupt(22, 0, 0, 0, 0);

    switch(*input) {
    case 0xD: /* if [ENTER] is pressed */
      buffer[i] = '\0'; /* add NULL Terminator to the end of the buffer */
      interrupt(16, 14 * 256 + '\n', 0, 0, 0);/* print new line */
      interrupt(16, 14 * 256 + '\r', 0, 0, 0);/* return to the beginning of the line */
      return;
    case 0x8:  /* if backspace was pressed and the buffer is not empty */
      if(i < 1)break;
      interrupt(16,  14 * 256 + *input, 0, 0, 0); /* print backspace (move the cursor back) */
      i--; /* go one char back in the buffer */
      buffer[i] = ' '; /* change it to a space, not technically needed */
      interrupt(16,  14 * 256 + buffer[i], 0, 0, 0); /* print the space (this looks clean) */
      interrupt(16, 14 * 256 + *input, 0, 0, 0); /* move the cursor back again */
      break;
    default:
      interrupt(16,  14 * 256 + *input, 0, 0, 0); /* print the char to the console */
      buffer[i] = *input; /* save the char in the buffer */
      i++; /* move to the next spot in the buffer */
    }
  }

  interrupt(16, 14 * 256 + '\n', 0, 0, 0); /* print new line */
  interrupt(16, 14 * 256 + '\r', 0, 0, 0); /* return to the beginning of the line */
  buffer[79] = '\0'; /* if you read 79 characters, set 80 to '\0' */
  return;
}

/* ax = 2 */
void readSector(char *buffer, int sector, int sectorCount)
{
  int relSecNo = mod(sector, 18) + 1;
  int headNo = mod(div(sector, 18), 2);
  int trackNo = div(sector, 36);
  interrupt(19, 2 * 256 + sectorCount, buffer, trackNo * 256 + relSecNo, headNo * 256);
}

/* ax = 5 */
void stop()
{
  while(1){};
}

/* ax = 6 */
void writeSector(char *buffer, int sector, int sectorCount)
{
  int relSecNo = mod(sector, 18) + 1;
  int headNo = mod(div(sector, 18), 2);
  int trackNo = div(sector, 36);
  interrupt(19, 3 * 256 + sectorCount, buffer, trackNo * 256 + relSecNo, headNo * 256);
}

/* ax = 12 */
void clearScreen(bx, cx)
{
  /* bx =  background color, cx = foreground color                       */
  /* These colors get set to the BH register in interrupt 16             */
  /* Ex) BH = 1Eh ,background is blue(0x01) and foreground is yellow(0x0E) */

  int i = 0;
  while(i != 24) {
    ++i;
    interrupt(16, 14 * 256 + '\n', 0, 0, 0);/* print new line */
    interrupt(16, 14 * 256 + '\r', 0, 0, 0);/* return to the beginning of the line */
  }

  interrupt(16, 512, 0, 0, 0); /* Reset cursor to upper left hand corner*/
  if(bx > 0 && bx < 8 && cx > 0 && cx < 16 ) {
    interrupt(16, 1536, 0x10 * 256 * (bx - 1) + 0x01 * 256 * (cx - 1), 0, 24 * 256 + 79);
  }
}

/* ax = 13 */
void writeInt(int n, int cx)
{
  char numToPrint[6]; /* Maximum 5 digits plus NULL terminator*/
  int i;
  int x = n;
  int end = 0;

  if(n == 0) { /* Special case where n == 0 */
    numToPrint[0] = 48; /* zero in ascii */
    numToPrint[1] = '\0';
    interrupt(33, 0, numToPrint, cx, 0);
    return;
  }

  while(x != 0) {/* Finding the number of digits */
    x = div(x, 10);
    ++end;
  }

  numToPrint[end] = '\0';
  for(i = end - 1; i >= 0; --i) {
    numToPrint[i] = mod(n, 10) + 48;
    n = div(n, 10);
  }

  interrupt(33, 0, numToPrint, cx, 0);
  return;
}

/* ax = 14 */
void readInt(int *n)
{
  char buffer[80];
  int i;
  for(i = 0; i < 80; ++i)buffer[i] = 0;
  interrupt(33, 1, buffer, 0, 0); /* read in string, to be converted */

  *n = 0;
  i = 0;
  while(buffer[i] != '\0') { /* while we are not at the end of the string */
    /* if the char is not between 0-9 (inclusive) then it is garbage input && we should return immediately */
    if(!((buffer[i] - 48) >= 0 && (buffer[i] - 48) <= 9)) {
      *n = 0; /* We set to zero to indicate failure */
      return;
    }
    *n *= 10; /* shifts all the numbers to the left one decimal place */
    *n += buffer[i] - 48; /* puts the most recent number in the ones place */
    ++i; /* move to the next char to process */
  }
  return;
}

void handleInterrupt21(int ax, int bx, int cx, int dx)
{
  switch(ax) {
  case 0:
    printString(bx, cx);
    break;
  case 1:
    readString(bx);
    break;
  case 2:
    readSector(bx, cx, dx);
    break;
  case 3:
    readFile(bx, cx, dx);
    break;
  case 5:
    stop();
    break;
  case 6:
    writeSector(bx, cx, dx);
    break;
  case 12:
    clearScreen(bx, cx);
    break;
  case 13:
    writeInt(bx, cx);
    break;
  case 14:
    readInt(bx);
    break;
  default:
    interrupt(33, 0, "General BlackDOS error.\r\n\0", 0, 0);
  }
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

void error(int bx)
{
   switch (bx) {
	   case 0:
	   /* error 0 = "File not found." */
	   interrupt(16, 3654, 0, 0, 0); interrupt(16, 3689, 0, 0, 0); interrupt(16, 3692, 0, 0, 0);
	   interrupt(16, 3685, 0, 0, 0); interrupt(16, 3616, 0, 0, 0); interrupt(16, 3694, 0, 0, 0);
	   interrupt(16, 3695, 0, 0, 0); interrupt(16, 3700, 0, 0, 0); interrupt(16, 3616, 0, 0, 0);
	   interrupt(16, 3686, 0, 0, 0); interrupt(16, 3695, 0, 0, 0); interrupt(16, 3701, 0, 0, 0);
	   interrupt(16, 3694, 0, 0, 0); interrupt(16, 3684, 0, 0, 0);
	   break;
	   case 1:
	   /* error 1 = "Bad file name." */
	   interrupt(16, 3650, 0, 0, 0); interrupt(16, 3681, 0, 0, 0); interrupt(16, 3684, 0, 0, 0);
	   interrupt(16, 3616, 0, 0, 0); interrupt(16, 3686, 0, 0, 0); interrupt(16, 3689, 0, 0, 0);
	   interrupt(16, 3692, 0, 0, 0); interrupt(16, 3685, 0, 0, 0); interrupt(16, 3616, 0, 0, 0);
	   interrupt(16, 3694, 0, 0, 0); interrupt(16, 3681, 0, 0, 0); interrupt(16, 3693, 0, 0, 0);
	   interrupt(16, 3685, 0, 0, 0);
	   break;
	   case 2:
	   /* error 2 = "Disk full." */
	   interrupt(16, 3652, 0, 0, 0); interrupt(16, 3689, 0, 0, 0); interrupt(16, 3699, 0, 0, 0);
	   interrupt(16, 3691, 0, 0, 0); interrupt(16, 3616, 0, 0, 0); interrupt(16, 3686, 0, 0, 0);
	   interrupt(16, 3701, 0, 0, 0); interrupt(16, 3692, 0, 0, 0); interrupt(16, 3692, 0, 0, 0);
	   break;
	   default:
	   /* default = "General error." */
	   interrupt(16, 3655, 0, 0, 0); interrupt(16, 3685, 0, 0, 0); interrupt(16, 3694, 0, 0, 0);
	   interrupt(16, 3685, 0, 0, 0); interrupt(16, 3698, 0, 0, 0); interrupt(16, 3681, 0, 0, 0);
	   interrupt(16, 3692, 0, 0, 0); interrupt(16, 3616, 0, 0, 0); interrupt(16, 3685, 0, 0, 0);
	   interrupt(16, 3698, 0, 0, 0); interrupt(16, 3698, 0, 0, 0); interrupt(16, 3695, 0, 0, 0);
	   interrupt(16, 3698, 0, 0, 0);
   }
   interrupt(16, 3630, 0, 0, 0); interrupt(16, 3597, 0, 0, 0); interrupt(16, 3594, 0, 0, 0);
   interrupt(33, 5, 0, 0, 0);
}
