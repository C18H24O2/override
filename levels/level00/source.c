#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  int flag [4];
  
  puts("***********************************");
  puts("* \t     -Level00 -\t\t  *");
  puts("***********************************");
  printf("Password:");
  (void)!scanf("%d",flag);
  if (flag[0] != 5276) {
    puts("\nInvalid Password!");
  }
  else {
    puts("\nAuthenticated!");
    (void)!system("/bin/sh");
  }
  return flag[0] != 5276;
}

