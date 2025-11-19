bool auth(char *s, int a2)
{
  int i;
  int value;
  int len;

  s[strcspn(s, "\n")] = 0;
  len = strnlen(s, 32);
  if ( len <= 5 )
    return 1;
  if ( ptrace(PTRACE_TRACEME, 0, 1, 0) == -1 )
  {
    puts("\x1B[32m.---------------------------.");
    puts("\x1B[31m| !! TAMPERING DETECTED !!  |");
    puts("\x1B[32m'---------------------------'");
    return 1;
  }
  else
  {
    value = (s[3] ^ 0x1337) + 6221293;
    for ( i = 0; i < len; ++i )
    {
      if ( s[i] <= 31 )
        return 1;
      value += (value ^ (unsigned int)s[i]) % 0x539;
    }
    return a2 != value;
  }
}

int main(int argc, const char **argv, const char **envp)
{
  int value;
  char s[28];

  puts("***********************************");
  puts("*\t\tlevel06\t\t  *");
  puts("***********************************");
  printf("-> Enter Login: ");
  fgets(s, 32, stdin);
  puts("***********************************");
  puts("***** NEW ACCOUNT DETECTED ********");
  puts("***********************************");
  printf("-> Enter Serial: ");
  scanf("%s", &s);
  if ( auth(s, value) )
    return 1;
  puts("Authenticated!");
  system("/bin/sh");
  return 0;
}