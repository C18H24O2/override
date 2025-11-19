# level05

The [target program](source.c) contains only a `main()` function, that `fgets()` 100 characters from stdin into a buffer, transform every uppercase character into their lowercase counterpart, and then gives the buffer as the first argument of `printf()`, we will abuse of printf flags to write into memory and inject a shellcode :

The payload will consist of an environment variable containing our shellcode, using `export`

The second part will consist of using `%p` and `%hn` flags to write at the current printf return value as an address
We are logged as level05 now :3

