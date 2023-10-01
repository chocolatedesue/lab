#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    // printf("start sleep\n");

    if (argc != 2)
    {
        fprintf(2,"Usgae: sleep [time]");
        exit(-1);
    }
    int n = atoi(argv[1]);
    // printf("the value of n is %d\n",n);
    if (n < 0)
        return -1;
    int res = sleep(n);
    if (res == -1)
        return -1;
    // int res = sleep(n);
    // printf("end sleep\n");
    exit(0);
}