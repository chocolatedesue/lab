#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

signed main()
{
    int p2c[2];
    int c2p[2];
    // pipe(p);
    if (pipe(p2c) < 0)
    {
        fprintf(2, "error on create p2c");
        exit(-1);
    }
    if (pipe(c2p) < 0)
    {
        fprintf(2, "error on create c2p");
        exit(-1);
    }

    char buf[10];
    int pid = fork();
    if (!pid)
    {
        read(p2c[0], buf, sizeof buf);
        printf("%d: received ping\n", getpid());
        write(c2p[1], "0", 2);
    }
    else if (pid > 0)
    {
        write(p2c[1], "p", 2);
        read(c2p[0], buf, sizeof c2p);
        printf("%d: received pong\n", getpid());
    }
    else
    {
        printf("fork error\n");
        exit(-1);
    }
    exit(0);

}