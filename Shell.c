void shellCommand(char *);
int strCmp(char *, char *);
int commandArguments(char *, char *, char *, char *);
void fillStr(char *, int, char *);
void fillShellChoices(char **);

/* Shell Commands*/
void boot();
void clrs();
void echo(char *);

void main()
{
  int numChoices = 12;
  char buffer[512];
  char choices[12][5];

  fillShellChoices(choices);

  interrupt(33, 2, buffer, 258, 1); /* load config file */
  interrupt(33, 12, buffer[0] + 1, buffer[1] + 1, 0); /* clear screen and set colors to config colors */

  interrupt(33, 0, "Welcome to Andrew, Devin, and Tristans Shell! Enjoy your stay\r\n", 0, 0);
  while(1) {
    interrupt(33, 0, "^(~(oo)~)^\r\n", 0, 0);
    interrupt(33, 1, buffer, 0, 0);
    shellCommand(choices, buffer, numChoices);
  }
  return;
}

void fillShellChoices(char choices[][5])
{
  fillStr(&choices[0][0], 5, "boot\0");
  fillStr(&choices[1][0], 5, "clrs\0");
  fillStr(&choices[2][0], 5, "echo\0");
  fillStr(&choices[3][0], 5, "ddir\0");
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
  if(!splitArg(input, arg1, arg2)) {
    return;
  }

  for(i = 0; i < numChoices; ++i) {
    if(strCmp(arg1, &choices[i][0])) {
      switch(i) {
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
        break;
      case 4:
        break;
      case 5:
        break;
      case 6:
        break;
      case 7:
        break;
      case 8:
        break;
      case 9:
        break;
      case 10:
        break;
      case 11:
        break;
      }
      break;
    }
  }
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