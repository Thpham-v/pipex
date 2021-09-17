/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thpham-v <thpham-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 17:05:58 by thpham-v          #+#    #+#             */
/*   Updated: 2021/09/17 17:09:35 by thpham-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_first_f(char **argv, char **env, t_var *var)
{
	var->path = get_path(env);
	var->fd_file = open(argv[1], O_RDONLY);
	var->cmd = get_cmd(argv[2]);
	var->cmd_path = get_cmd_path(var->cmd, var->path);
	var->str[0] = var->cmd_path;
	if (!var->str[0])
		var->str[0] = var->cmd;
	var->str[1] = get_option(argv[2]);
	var->str[2] = NULL;
}

void	init_last_f(char **argv, t_var *var)
{
	var->fd_file = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    var->cmd = get_cmd(argv[3]);
    var->cmd_path = get_cmd_path(var->cmd, var->path);
    var->str[0] = var->cmd_path;
    if (!var->str[0])
        var->str[0] = var->cmd;
    var->str[1] = get_option(argv[3]);
}

void	first_f(char **env, t_var *var)
{
	var->pid = fork();
    if (var->pid == 0)
    {
        dup2(var->fd_file, STDIN_FILENO);
        dup2(var->fd[1], STDOUT_FILENO);
        close(var->fd[0]);
        if (execve(var->str[0], var->str, env) == -1)
        {
            perror("pipex");
            exit(0);
        }
    }
}

void	last_fork(char **env, t_var *var)
{
	var->pid = fork();
    if (var->pid == 0)
    {
        dup2(var->fd[0], STDIN_FILENO);
        dup2(var->fd_file, STDOUT_FILENO);
        close(var->fd[1]);
        if (execve(var->str[0], var->str, env) == -1)
        {
            perror("pipex");
            exit(0);
        }
    }
}

int		main(int argc, char **argv, char **env)
{
	t_var var;

	if (argc != 5)
		return (1);
    ft_bzero(&var, sizeof(t_var));
	init_first_f(argv, env, &var);
	pipe(var.fd);
    first_f(env, &var);
	close(var.fd_file);
	init_last_f(argv, &var);
    last_fork(env, &var);
    wait(&var.pid);
	return (0);
}