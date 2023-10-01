#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"
#define MAXLEN 100

void db(char buf[])
{
    // for (int i = 0; )
}

int main(int argc, char *argv[])
{
    char *new_args[MAXARG];
    char *cmd = argv[1];

    for (int i = 1; i < argc; ++i)
    {
        new_args[i - 1] = argv[i];
    }
    int p = argc - 1;

    char buf[MAXLEN];

    int idx = 0;
    while (read(0, buf + idx, 1))
    {
        if (buf[idx] == '\n')
        {
            buf[idx] = '!';
            // break;
        }
        idx++;
        if (idx >= MAXLEN)
        {
            fprintf(2, "too long params\n");
        }
    }

    int pre = 0;
    const int sz = strlen(buf);
    // printf("sz: %d\n", sz);
    for (int i = 0; i < sz; ++i)
    {
        // printf("c: %c\n", buf[i]);
        if (buf[i] == ' ' || buf[i] == '!')
        {
            int fg = buf[i] == '!';
            buf[i] = '\0';
            // printf("read of buf: %s\n", buf + pre);
            new_args[p++] = buf + pre;

            // printf("new arg: %s\n", new_args[p - 1]);
            // printf("new arg in buf: %s\n", buf + pre);
            pre = i + 1;

            if (fg)
            {
                // printf("v of p: %d\n", p);
                // for (int i = 0; i < p; ++i)
                // {
                //     printf("args: %s\n", new_args[i]);
                // }
                int pid = fork();
                if (pid > 0)
                {
                    wait(0);
                }
                else if (!pid)
                {
                    exec(cmd, new_args);
                }
                p = argc - 1;
            }
        }
        // else
    }

    exit(0);
}