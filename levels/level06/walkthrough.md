# level06

The [target program](source.c) contains a `main()` and `auth()` function, the program take two string as input, runs the `auth` function that "serialize" the second input, and compare it with the first input.

we need to reverse this little algorithm to find a pair that is equal after the second element is serialized :

Our [program](main.c) take the first input as argument, and do the opposite as the program we have to exploit, so that we get our pair :



```c
#include <stdint.h>
#include <stdio.h>
#include <string.h>
int main(void)
{
	char login[] = "wompwomp";
	uint32_t i;
	uintptr_t str;
	size_t len = strlen(login);

	str = ((int)login[3] ^ 0x1337U) + 0x5eeded;

	for (i = 0; i < (int)len; i++)
	{
		if (login[i] < ' ')
			return 1;
		str = str + ((int)login[i] ^ (int)str) % 0x539;
	}
	if (i == str)
		printf("!!!\n");
	printf("%s:%u", login, str);
	//printf("%s 0x%lx\n", &str, (unsigned long)login);
}
```

In this case, the program returns :
```wompwomp:6234482```
```bash
let's try it :
level06@OverRide:~$ ./level06 
***********************************
*		level06		  *
***********************************
-> Enter Login: wompwomp
***********************************
***** NEW ACCOUNT DETECTED ********
***********************************
-> Enter Serial: 6234482
Authenticated!
$ id
uid=1006(level06) gid=1006(level06) euid=1007(level07) egid=100(users) groups=1007(level07),100(users),1006(level06)
```
We are logged as level07 now :3

