int main(int argc, const char **argv, const char **envp)
{
  char s2[96];
  char ptr[48];
  char s[96];
  int n_read;
  FILE *stream;

  memset(s, 0, sizeof(s));
  memset(ptr, 0, 41);
  memset(s2, 0, sizeof(s2));
  stream = fopen("/home/users/level03/.pass", "r");
  if ( !stream )
  {
    fwrite("ERROR: failed to open password file\n", 1u, 0x24u, stderr);
    exit(1);
  }
  n_read = fread(ptr, 1u, 0x29u, stream);
  ptr[strcspn(ptr, "\n")] = 0;
  if ( n_read != 41 )
  {
    fwrite("ERROR: failed to read password file\n", 1u, 0x24u, stderr);
    fwrite("ERROR: failed to read password file\n", 1u, 0x24u, stderr);
    exit(1);
  }
  fclose(stream);
  puts("===== [ Secure Access System v1.0 ] =====");
  puts("/***************************************\\");
  puts("| You must login to access this system. |");
  puts("\\**************************************/");
  printf("--[ Username: ");
  fgets(s, 100, stdin);
  s[strcspn(s, "\n")] = 0;
  printf("--[ Password: ");
  fgets(s2, 100, stdin);
  s2[strcspn(s2, "\n")] = 0;
  puts("*****************************************");
  if ( strncmp(ptr, s2, 0x29u) )
  {
    printf(s);
    puts(" does not have access!");
    exit(1);
  }
  printf("Greetings, %s!\n", s);
  system("/bin/sh");
  return 0;
}