#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    // Return a random character between ASCII decimal 32 and 126.
    return rand() % (126 - 32 + 1) + 32;
}

char *inputString()
{
    // Create a static string.
    static char randString[10];

    // Set every element in that string to NULL.
    memset(randString, '\0', sizeof(randString));

    // Randomly assign 5 characters to the string.
    // Valid characters are e thru t, excluding n thru q.
    for (int i = 0; i < 5; ++i)
    {
      // Random character selector adapted from:
      // https://stackoverflow.com/questions/19724346/generate-random-characters-in-c
      randString[i] = "efghijklmrst"[rand() % 12];
    }

    // Return the string.
    return randString;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
