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

void main()
{
  char buffer[512];
  int i;
  makeInterrupt21();
  for (i = 0; i < 512; i++) buffer[i] = 0;
  buffer[0] = 1;
  buffer[1] = 0xE;
  interrupt(33, 6, buffer, 258, 1);
  interrupt(33, 12, buffer[0] + 1, buffer[1] + 1, 0);
  printLogo();
  interrupt(33, 2, buffer, 30, 1);
  interrupt(33, 0, buffer, 0, 0);
  while (1) ;
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
  interrupt(33, 1, buffer, 0, 0); /* read in string, to be converted */

  *n = 0;
  i = 0;
  while(buffer[i] != '\0') { /* while we are not at the end of the string */
    /* if the char is not between 0-9 (inclusive) then it is garbage input && we should return immediately */
    if(!((buffer[i] - 48) >= 0 && (buffer[i] - 48) <= 9)) {
      *n = 0;
      return;
    }
    *n *= 10; /* shifts all the numbers to the left one decimal place */
    *n += buffer[i] - 48; /* put the move recent number in the ones place */
    ++i; /* move to the next char to process */
  }
  return;
}

void writeInt(int n, int cx)
{
  char numToPrint[6]; /* All are 5 digit numbers */
  int i;
  int x = n;
  int end = 0;

  if(n == 0) { /* Special case where n == 0 */
    numToPrint[0] = 48; /* zero in asci */
    numToPrint[1] = '\0';
    interrupt(33, 0, numToPrint, cx, 0);
    return;
  }

  while(x != 0) {
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

/* read string expects buffer to be an empty char[80] */
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
/* Notes */
/* The variable sector is the absolute sector */
/* Reading in the sector ah = 2 */
/* Variables */
/* 19 */
/* ax = 512 + sectorCount */
/* bx = buffer */
/* cx = trackNo * 256 + relSecNo */
/* dx = headNo * 256 */

void readSector(char *buffer, int sector, int sectorCount)
{
  int relSecNo = mod(sector, 18) + 1;
  int headNo = mod(div(sector, 18), 2);
  int trackNo = div(sector, 36);
  interrupt(19, 2 * 256 + sectorCount, buffer, trackNo * 256 + relSecNo, headNo * 256);
}

/* Notes */
/* Writing in sector ah = 3 */
/* Variables */
/* 33 */
/* ax = 768 + sectorCount */
/* bx = buffer */
/* cx = trackNo * 256 + relSecNo */
/* dx = headNo * 256 */
void writeSector(char *buffer, int sector, int sectorCount)
{
  int relSecNo = mod(sector, 18) + 1;
  int headNo = mod(div(sector, 18), 2);
  int trackNo = div(sector, 36);
  interrupt(19, 3 * 256 + sectorCount, buffer, trackNo * 256 + relSecNo, headNo * 256);
}

void clearScreen(bx, cx)
{
  /* TODO */
  int i = 0;
  while(i != 24) {
    ++i;
    interrupt(16, 14 * 256 + '\n', 0, 0, 0);/* print new line */
    interrupt(16, 14 * 256 + '\r', 0, 0, 0);/* return to the beginning of the line */
  }

  /*
     AH = 6, indicating function 6;
   AL = 0, meaning scroll whole screen or window;
   BH = the attribute byte for blank lines, explained next;
   CH and CL are the row and column for the upper left-hand corner of the window (0,0); and
   DH and DL are the row and column for the lower right-hand corner, (24,79).
  */

  interrupt(16, 512, 0, 0, 0); /* Reset cursor to upper left hand corner*/
  if(bx > 0 && bx < 8 && cx > 0 && cx < 16 ) {
    interrupt(16, 1536, 0x10 * 256 * (bx - 1) + 0x01 * 256 * (cx - 1), 0, 24 * 256 + 79);
  }
}

void handleInterrupt21(int ax, int bx, int cx, int dx)
{
  /* return; */
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
