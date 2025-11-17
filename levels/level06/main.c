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
