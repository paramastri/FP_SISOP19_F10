#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <pthread.h>
#include <time.h>

pthread_t tid[10];

void *bash(void *arg)
{
    char *dir;
    dir = (char *)arg;
    signal(SIGCHLD, SIG_IGN);
    pid_t pid, sid;
    pid = fork();
    if (pid == 0)
    {
        sid = setsid();

        if (sid < 0)
        {
            exit(EXIT_FAILURE);
        }

        execp("bash", dir, (char *)NULL);
    }
}

int main(void *arg)
{
    pid_t pid, sid;

    pid = fork();

    if (pid < 0)
    {
        exit(EXIT_FAILURE);
    }

    if (pid > 0)
    {
        exit(EXIT_SUCCESS);
    }

    umask(0);

    sid = setsid();

    if (sid < 0)
    {
        exit(EXIT_FAILURE);
    }

    if ((chdir("/")) < 0)
    {
        exit(EXIT_FAILURE);
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    while (1)
    {

        time_t now = time(NULL);
        struct tm tm = *localtime(&now);

        FILE *config = fopen("/home/paramastri/crontab.data", "r");

        int i = 0;
        while () != EOF)
            {
                if ()
                {
                    pthread_create(&tid[i++], NULL, run_command, (void *)s);
                }
            }

        fclose(config);
        // fclose(log);
        sleep(60);
    }

    exit(EXIT_SUCCESS);
}
