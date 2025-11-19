int main(int argc, const char **argv, const char **envp)
{
  int stat_loc; 
  char s[128];
  int ptrace_value;
  __pid_t pid;

  pid = fork();
  memset(s, 0, sizeof(s));
  ptrace_value = 0;
  stat_loc = 0;
  if ( pid )
  {
    do
    {
      wait(&stat_loc);
      if ( (stat_loc & 0x7F) == 0 || (char)((stat_loc & 0x7F) + 1) >> 1 > 0 )
      {
        puts("child is exiting...");
        return 0;
      }
      ptrace_value = ptrace(PTRACE_PEEKUSER, pid, 44, 0);
    }
    while ( ptrace_value != 11 );
    puts("no exec() for you");
    kill(pid, 9);
  }
  else
  {
    prctl(1, 1);
    ptrace(PTRACE_TRACEME, 0, 0, 0);
    puts("Give me some shellcode, k");
    gets(s);
  }
  return 0;
}