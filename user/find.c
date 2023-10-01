#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

char *
fmtname(char *path)
{
    static char buf[DIRSIZ + 1];
    char *p;

    // Find first character after last slash.
    for (p = path + strlen(path); p >= path && *p != '/'; p--)
        ;
    p++;

    // Return blank-padded name.
    if (strlen(p) >= DIRSIZ)
        return p;
    memmove(buf, p, strlen(p));
    memset(buf + strlen(p), '\0', DIRSIZ - strlen(p));
    // buf[buf + strlen(p)] = '\0';
    return buf;
}



void match(const char* path, const char* name){
    //printf("%s %s", path, name);
    int pp = 0;
    int pa = 0;
    while(path[pp] != 0){
        pa = 0;
        int np = pp;
        while(name[pa] != 0){
            if (name[pa] == path[np]){
                pa++;
                np++;
            }
            else
                break;
        }
        if(name[pa] == 0){
            printf("%s\n", path);
            return;
        }
        pp++;
    }
}



void find(char *path, char *pattern)
{
    char buf[512], *p;
    int fd;
    struct dirent de;
    struct stat st;

    if ((fd = open(path, 0)) < 0)
    {
        fprintf(2, "find: cannot open %s\n", path);
        return;
    }

    if (fstat(fd, &st) < 0)
    {
        fprintf(2, "find: cannot stat %s\n", path);
        close(fd);
        return;
    }

    switch (st.type)
    {
    case T_FILE:
        // char * f_name =
        // printf("before compare: %s -- %s\n",fmtname(path), pattern);
        // // printf ("res")
        // int res =  strcmp(fmtname(path), pattern);
        // printf("res : %d\n",res);
        if (
            !strcmp(fmtname(path), pattern))
        {
            printf(path);
            printf("\n");
            // exit(0);
        }
        // match(path, pattern);
        break;

    case T_DIR:
        if (strlen(path) + 1 + DIRSIZ + 1 > sizeof buf)
        {
            printf("ls: path too long\n");
            break;
        }
        strcpy(buf, path);
        p = buf + strlen(buf);
        *p++ = '/';
        // find(p,pattern);
        while (read(fd, &de, sizeof(de)) == sizeof(de))
        {
            if (de.inum == 0)
                continue;

            if (de.name[0] == '.' && de.name[1] == 0)
                continue;
            if (de.name[0] == '.' && de.name[1] == '.' && de.name[2] == 0)
                continue;

            memmove(p, de.name, DIRSIZ);
            p[DIRSIZ] = 0;
            if (stat(buf, &st) < 0)
            {
                printf("find: cannot stat %s\n", buf);
                continue;
            }
            // printf("%s %d %d %d\n", fmtname(buf), st.type, st.ino, st.size);
            find(buf,pattern);
        }
        break;
    }
    close(fd);
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(2, "usage: find path pattern\n");
        exit(-1);
    }

    char *path = argv[1],
         *pattern = argv[2];
    find(path, pattern);
    exit(0);
}
