#include "pipex.h"

int    main(int ac, char **av, char **env)
{
    int file;
    char **path;
    char *cmd;
    char *cmdpath;
    char *str[3];
    int fd[2];
    pid_t pid;

    if (ac < 5)
        return (1);
    path = get_path(env);
    file = open(av[1], O_RDONLY);
    cmd = get_cmd(av[2]);
    cmdpath = get_cmdpath(cmd, env, path);
    str[0] = cmdpath;
    if (!str[0])
        str[0] = cmd;
    str[1] = get_option(av[2]);
    str[2] = NULL;
    pipe(fd);
    pid = fork();
    if (pid == 0)
    {
        dup2(file, STDIN_FILENO);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        if (execve(str[0], str, env) == -1)
        {
            perror("pipex");
            exit(0);
        }
    }
    close(file);
    file = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    cmd = get_cmd(av[3]);
    cmdpath = get_cmdpath(cmd, path);
    str[0] = cmdpath;
    if (!str[0])
        str[0] = cmd;
    str[1] = get_option(av[3]);
    pid = fork();
    if (pid == 0)
    {
        dup2(fd[0], STDIN_FILENO);
        dup2(file, STDOUT_FILENO);
        close(fd[1]);
        if (execve(str[0], str, env) == -1)
        {
            perror("pipex");
            exit(0);
        }
    }
    wait(&pid);
    return (0);
}