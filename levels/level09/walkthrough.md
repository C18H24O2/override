# level01

After debugging our own code, here's the walkthrough:

The [target program](source.c) does two `fgets` calls, one to read a username and one to read a password.
We can see that the username is `dat_wil`, and the password is `admin`, but inputting the correct credentials doesn't do much for us.

Fortunately, looking at the size of the password's `fgets` call, we can see that we're reading 100 bytes into a 64 bytes-sized buffer. This is a true trollface moment.

We put a payload in an environment variable `OUIOUI` with an x86 execve shellcode, and then write the correct username with a newline, then 64 characters of padding to stdin, and finally the address of environment variable.

We now get shell access :3
