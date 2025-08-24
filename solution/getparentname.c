#include "types.h"
#include "stat.h"
#include "user.h"
int main(void) 
{

  char parentbuf[256];
  char childbuf[256];
  int parentbufsize = 256;
  int childbufsize = 256;

  if (getparentname(parentbuf, childbuf, parentbufsize, childbufsize) == -1) {
    exit();
  }

  printf(1, "XV6_TEST_OUTPUT Parent name: %s Child name: %s\n", parentbuf, childbuf);
  exit();
}

