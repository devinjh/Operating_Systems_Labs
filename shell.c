/* Function prototypes*/
void shellCommand(char *);
int strCmp(char *, char *);
int commandArguments(char *, char *, char *, char *);
void fillStr(char *, int, char *);
void fillShellChoices(char **);

/* Shell Commands*/
void boot();
void clrs();
void echo(char *);
void copy(char *);
void ddir();
void exec(char *);
void help();
void prnt(char *);
void remv(char *);
void senv();
void show(char *);
void twet(char *);

void main()
{
  int numChoices = 12;
  char buffer[512];
  char choices[12][5]; /* Commands are always 4 characters max and one character for the null terminator*/

  fillShellChoices(choices);

  interrupt(33, 0, "Welcome to Andrew, Devin, and Tristans Shell! Enjoy your stay\r\n", 0, 0);

  while(1) {
    interrupt(33, 0, "^(~(oo)~)^\r\n", 0, 0); /* Obligatory year of the pig thing*/
    interrupt(33, 1, buffer, 0, 0); /* let the user input a command*/
    shellCommand(choices, buffer, numChoices); /* process the command*/
  }
  return;
}

void fillShellChoices(char choices[][5])
{
  fillStr(&choices[0][0], 5, "boot\0");
  fillStr(&choices[1][0], 5, "clrs\0");
  fillStr(&choices[2][0], 5, "echo\0");
  fillStr(&choices[3][0], 5, "copy\0");
  fillStr(&choices[4][0], 5, "ddir\0");
  fillStr(&choices[5][0], 5, "exec\0");
  fillStr(&choices[6][0], 5, "help\0");

  fillStr(&choices[7][0], 5, "prnt\0");
  fillStr(&choices[8][0], 5, "remv\0");
  fillStr(&choices[9][0], 5, "senv\0");
  fillStr(&choices[10][0], 5, "show\0");
  fillStr(&choices[11][0], 5, "twet\0");
}

void shellCommand(char choices[][5], char *input, int numChoices)
{
  char arg1[80], arg2[80];
  int i = 0;
  if(!splitArg(input, arg1, arg2)) { /* get the command from the user input, and put the rest in arg2*/
    return;
  }

  for(i = 0; i < numChoices; ++i) {
    if(strCmp(arg1, &choices[i][0])) { /* check if what the user enters matches a command*/
      switch(i) {/* If a match is found, go to the corresponding command function*/
      case 0:
        boot();
        break;
      case 1:
        clrs();
        break;
      case 2:
        echo(arg2);
        break;
      case 3:
        copy(arg2);
        break;
      case 4:
        ddir();
        break;
      case 5:
        exec(arg2);
        break;
      case 6:
        help();
        break;
      case 7:
        prnt(arg2);
        break;
      case 8:
        remv(arg2);
        break;
      case 9:
        senv();
        break;
      case 10:
        show(arg2);
        break;
      case 11:
        twet(arg2);
        break;
      }
      return;/* After you find a match, and run the function, you dont need to check anymore*/
    }
  }
  interrupt(33, 0, "bad command or file name\r\n", 0, 0); /* No command was matched*/
}

void boot()
{
  interrupt(25, 0, 0, 0, 0);
}

void clrs()
{
  interrupt(33, 12, 0, 0, 0);
}

void echo(char *arg2)
{
  interrupt(33, 0, arg2, 0, 0);
  interrupt(33, 0, "\r\n", 0, 0);
}

void copy(char *arg2)
{
  char file1[80], file2[80], extra[80];
  file1[0] = '\0';
  file2[0] = '\0';

  splitArg(arg2, file1, extra); /* fill file1 with the characters up to the next whitespace*/
  splitArg(extra, file2, extra); /* fill file2 with the characters up to the next whitespace*/

  if(extra[0] != '\0') { /* if the user entered more than two files, there are too many arguments*/
    interrupt(33, 0, "Copy was called with too many arguments\r\n", 0, 0);
    return;
  }
  if(file2[0] == '\0' || file1[0] == '\0') {
    interrupt(33, 0, "Copy was called with too few arguments\r\n", 0, 0);
    return;
  }
  interrupt(33, 0, "Copy was called with files: ", 0, 0);
  interrupt(33, 0, file1, 0, 0);
  interrupt(33, 0, " and ", 0, 0);
  interrupt(33, 0, file2, 0, 0);
  interrupt(33, 0, "\r\n", 0, 0);
}

void ddir()
{
  interrupt(33, 4, "Ddir\0", 4, 0);
}

void exec(char *arg2)
{
  char filename [80];
  filename[0] = '\0';

  splitArg(arg2, filename, arg2);
  if(arg2[0] != '\0') {
    interrupt(33, 0, "Exec was called with too many arguments\r\n", 0, 0);
    return;
  }
  if(filename[0] == '\0') {
    interrupt(33, 0, "Exec was called with too few arguments\r\n", 0, 0);
    return;
  }

  interrupt(33, 4, filename, 4, 0);
}

void help()
{
  interrupt(33, 4, "Help\0", 4, 0);
}

void prnt(char *arg2)
{
  char filename [80];
  char buffer [4096];
  int size;
  filename[0] = '\0';

  splitArg(arg2, filename, arg2);
  if(arg2[0] != '\0') {
    interrupt(33, 0, "Prnt was called with too many arguments\r\n", 0, 0);
    return;
  }
  if(filename[0] == '\0') {
    interrupt(33, 0, "Prnt was called with too few arguments\r\n", 0, 0);
    return;
  }

  interrupt(33, 3, filename, buffer, size);
  interrupt(33, 0, buffer, 1, 0);
}

void remv(char *arg2)
{
  char  filename [80];
  filename[0] = '\0';

  splitArg(arg2, filename, arg2);
  if(arg2[0] != '\0') {
    interrupt(33, 0, "Remv was called with too many arguments\r\n", 0, 0);
    return;
  }
  if(filename[0] == '\0') {
    interrupt(33, 0, "Remv was called with too few arguments\r\n", 0, 0);
    return;
  }

  interrupt(33, 0, "Remv was called with filename: ", 0, 0);
  interrupt(33, 0, filename, 0, 0);
  interrupt(33, 0, "\r\n", 0, 0);
}

void senv()
{
  interrupt(33, 4, "Stenv\0", 4, 0);
}

void show(char *arg2)
{
  char  filename [80];
  char buffer [4096];
  int size;
  filename[0] = '\0';

  splitArg(arg2, filename, arg2);
  if(arg2[0] != '\0') {
    interrupt(33, 0, "Show was called with too many arguments\r\n", 0, 0);
    return;
  }
  if(filename[0] == '\0') {
    interrupt(33, 0, "Show was called with too few arguments\r\n", 0, 0);
    return;
  }

  interrupt(33, 3, filename, buffer, size);
  interrupt(33, 0, buffer, 0, 0);
}

void twet(char *arg2)
{
  char  filename [80];
  filename[0] = '\0';

  splitArg(arg2, filename, arg2);
  if(arg2[0] != '\0') {
    interrupt(33, 0, "Twet was called with too many arguments\r\n", 0, 0);
    return;
  }
  if(filename[0] == '\0') {
    interrupt(33, 0, "Twet was called with too few arguments\r\n", 0, 0);
    return;
  }

  interrupt(33, 0, "Twet was called with filename: ", 0, 0);
  interrupt(33, 0, filename, 0, 0);
  interrupt(33, 0, "\r\n", 0, 0);
}

/* Splits the char* buffer into two args based on the first space */
int splitArg(char *buffer, char *arg1, char *arg2)
{
  int i = 0;
  int arg1Index = 0;
  int arg2Index = 0;
  int argToFill = 1;

  while(buffer[i] != '\0') {
    if(buffer[i] == ' ' && argToFill == 1) {
      argToFill++;
    }
    else {
      switch(argToFill) {
      case 1:
        arg1[arg1Index] = buffer[i];
        arg1Index++;
        break;
      case 2:
        arg2[arg2Index] = buffer[i];
        arg2Index++;
        break;
      }
    }
    ++i;
  }
  arg1[arg1Index] = '\0';
  arg2[arg2Index] = '\0';
  return 1; /* success */
}

int strCmp(char *str1, char *str2)
{
  int i = 0;
  while(1) {
    if(str1[i] != str2[i]) { /* if any character in the string doesn't match, they aren't equal*/
      return 0;
    }
    if(str1[i] == '\0' && str2[i] == '\0') { /* if you reach the end of the strings at the same time, they are the same*/
      return 1;
    }
    if(str1[i] == '\0' || str2[i] == '\0') { /* if one string ends before the other they are not the same string*/
      return 0;
    }
    ++i;
  }
}

void fillStr(char *buffer, int bufferSize, char *filler)
{
  int i = 0;
  while(i < bufferSize) {
    buffer[i] = filler[i];
    ++i;
  }
}
