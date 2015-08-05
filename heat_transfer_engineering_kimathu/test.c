#include <stdio.h>
#define dbg(arg,...) (printf("\x1b[41m"),printf(arg,__VA_ARGS__),printf("\x1b[0m"))

int main(void)
{
  printf("\n");
  dbg("debug:%s----%d\n",__FUNCTION__,64);
  return 0;
}
