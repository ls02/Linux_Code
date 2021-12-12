#include "procb.h"

void ProcBar()
{
  int i = 0;
  char proc[102] = { 0 };
  const char* lable = "|/-\\";

  while (i < 101)
  {
    printf("[%-100s][%d%%][%c]\r", proc, i % 101, lable[i % 4]);
    proc[i] = '#';
    fflush(stdout);

    usleep(100000);
    i++;
  }

  printf("\n");
}
