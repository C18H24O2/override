/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bordel.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 23:06:25 by kiroussa          #+#    #+#             */
/*   Updated: 2025/06/07 23:08:15 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc,char **argv,char **envp)
{
  int iVar1;
  size_t ret;
  long lVar2;
  char local_118 [112];
  char pass [48];
  char local_78 [100];
  int ret2;
  FILE *file;
  
  file = (FILE *)0x0;
  ret2 = 0;
  file = fopen(".pass","r");
  if (file == (FILE *)0x0) {
    fwrite("ERROR: failed to open password file\n",1,0x24,stderr);
                    /* WARNING: Subroutine does not return */
    exit(1);
  }
  ret = fread(pass,1,41,file);
  ret2 = (int)ret;
  ret = strcspn(pass,"\n");
  pass[ret] = '\0';
  if (ret2 != 0x29) {
    fwrite("ERROR: failed to read password file\n",1,0x24,stderr);
    fwrite("ERROR: failed to read password file\n",1,0x24,stderr);
                    /* WARNING: Subroutine does not return */
    exit(1);
  }
  fclose(file);
  puts("===== [ Secure Access System v1.0 ] =====");
  puts("/***************************************\\");
  puts("| You must login to access this system. |");
  puts("\\**************************************/");
  printf("--[ Username: ");
  fgets(local_78,100,stdin);
  ret = strcspn(local_78,"\n");
  local_78[ret] = '\0';
  printf("--[ Password: ");
  fgets(local_118,100,stdin);
  ret = strcspn(local_118,"\n");
  local_118[ret] = '\0';
  puts("*****************************************");
  iVar1 = strncmp(pass,local_118,41);
  if (iVar1 == 0) {
    printf("Greetings, %s!\n",local_78);
    system("/bin/sh");
    return 0;
  }
  printf(local_78);
  puts(" does not have access!");
                    /* WARNING: Subroutine does not return */
  exit(1);
}
