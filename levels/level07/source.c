int clear_stdin(void)
{
    int result;
    do {
        result = getchar();
    } while ((unsigned char)result != 10 && (unsigned char)result != 0xFF);
    return result;
}

int get_unum(void)
{
    unsigned int v1[3];

    v1[0] = 0;
    fflush(stdout);
    scanf("%u", v1);
    clear_stdin();
    return v1[0];
}

void prog_timeout(void)
{
    sys_exit(1);
}

int store_number(int a1)
{
    unsigned int unum;
    unsigned int idx;

    printf(" Number: ");
    unum = get_unum();
    printf(" Index: ");
    idx = get_unum();

    if (idx == 3 * (idx / 3) || ((unum >> 24) & 0xFF) == 183) {
        puts(" *** ERROR! ***");
        puts("   This index is reserved for wil!");
        puts(" *** ERROR! ***");
        return 1;
    }

    *(unsigned int *)(a1 + 4 * idx) = unum;
    return 0;
}

int read_number(int a1)
{
    int idx;
    printf(" Index: ");
    idx = get_unum();
    printf(" Number at data[%u] is %u\n", idx, *(unsigned int *)(a1 + 4 * idx));
    return 0;
}

int main(int argc, const char **argv, const char **envp)
{
    unsigned char data[400];
    int result;
    char cmd[4];
    unsigned int canary;

    canary = __readgsdword(0x14);
    result = 0;
    *(int *)cmd = 0;
    memset(data, 0, sizeof(data));

    while (*argv) {
        memset((void *)*argv, 0, strlen(*argv));
        argv++;
    }

    while (*envp) {
        memset((void *)*envp, 0, strlen(*envp));
        envp++;
    }

    puts(
        "----------------------------------------------------\n"
        "  Welcome to wil's crappy number storage service!   \n"
        "----------------------------------------------------\n"
        " Commands:                                          \n"
        "    store - store a number into the data storage    \n"
        "    read  - read a number from the data storage     \n"
        "    quit  - exit the program                        \n"
        "----------------------------------------------------\n"
        "   wil has reserved some storage :>                 \n"
        "----------------------------------------------------\n"
    );

    for (;;) {
        printf("Input command: ");
        result = 1;
        fgets(cmd, 20, stdin);
        cmd[strlen(cmd) - 1] = 0;

        if (!memcmp(cmd, "store", 5)) {
            result = store_number((int)data);
        } else if (!memcmp(cmd, "read", 4)) {
            result = read_number((int)data);
        } else if (!memcmp(cmd, "quit", 4)) {
            return 0;
        }

        if (result)
            printf(" Failed to do %s command\n", cmd);
        else
            printf(" Completed %s command successfully\n", cmd);

        *(int *)cmd = 0;
    }
}