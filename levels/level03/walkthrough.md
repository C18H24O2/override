# level03

This one is a bit more of a classic indirection challenge, with some arithmetic and a...... `rand` call... oh no.

First, we can see a call to `scanf` in the main function taking in an integer with `%d`. Resisting the urge to bruteforce all known integers and call it a day, we see it saves it to a variable and then calls the `test` function with it as its first parameter, and `0x1337d00d` as its second. Thank you `wil`.

This function performs a difference between the two and, if that difference is between 1 and 21, it calls `decrypt` with the difference, otherwise it calls `rand` and calls `decrypt` with that.

The `decrypt` function takes in a `char` (hint hint) and xors it with a seemingly random string (i would put it here but markdown explodes), finishing by comparing the result with `Congratulations!`.

That's it, we've done some nice static analysis, let us get ourselves a treat: let's bruteforce this thing.

[One script later](brute.py), we get:

```
❯ python3 brute.py
18 Congratulations!
322424827
```

We can see that the difference between the two is 18, so we subtract 18 from `0x1337d00d` and get (in decimal): `322424827`.

Inputting that into the program, we get a shell. ggs
