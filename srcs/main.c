/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thpham-v <thpham-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 18:32:42 by thpham-v          #+#    #+#             */
/*   Updated: 2021/11/09 16:59:05 by thpham-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	init_first_f(char **argv, char **env, t_var *var)
{
	pipe(var->fd);
	var->path = get_path(env);
	var->fd_file = open(argv[1], O_RDONLY);
	if (var->fd_file == -1)
		return (-2);
	var->cmd = get_cmd(argv[2]);
	if (!var->cmd)
		return (-2);
	var->cmd_path = get_cmd_path(var->cmd, var->path);
	var->str[0] = var->cmd_path;
	if (!var->str[0])
		var->str[0] = var->cmd;
	var->str[1] = get_option(argv[2]);
	var->str[2] = NULL;
	return (0);
}

int	init_last_f(char **argv, t_var *var)
{
	if (var->fd_file != -1)
		close(var->fd_file);
	var->fd_file = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (var->fd_file == -1)
		return (-2);
	var->cmd = get_cmd(argv[3]);
	if (!var->cmd)
		return (-2);
	var->cmd_path = get_cmd_path(var->cmd, var->path);
	var->str[0] = var->cmd_path;
	if (!var->str[0])
		var->str[0] = var->cmd;
	var->str[1] = get_option(argv[3]);
	return (0);
}

static void	first_fork(char **env, t_var *var)
{
	if (var->ret >= 0)
	{
		var->pid1 = fork();
		if (var->pid1 == 0)
		{
			dup2(var->fd_file, STDIN_FILENO);
			dup2(var->fd[1], STDOUT_FILENO);
			close(var->fd[0]);
			close(var->fd[1]);
			if (execve(var->str[0], var->str, env) == -1)
				execve_error(var);
		}
	}
	close(var->fd[1]);
	free(var->cmd);
	var->cmd = NULL;
	free(var->cmd_path);
	var->cmd_path = NULL;
	free(var->str[1]);
	var->str[1] = NULL;
}

static void	last_fork(char **env, t_var *var)
{	
	if (var->ret >= 0)
	{
		var->pid2 = fork();
		if (var->pid2 == 0)
		{
			dup2(var->fd[0], STDIN_FILENO);
			dup2(var->fd_file, STDOUT_FILENO);
			close(var->fd[1]);
			if (execve(var->str[0], var->str, env) == -1)
				execve_error(var);
		}
	}
	close(var->fd[0]);
	free(var->cmd);
	var->cmd = NULL;
	free(var->cmd_path);
	var->cmd_path = NULL;
	free(var->str[1]);
	var->str[1] = NULL;
}

int	main(int argc, char **argv, char **env)
{
	t_var	var;

	if (argc != 5)
		return (1);
	if (*__environ == NULL)
		return (1);
	ft_bzero(&var, sizeof(t_var));
	var.ret = init_first_f(argv, env, &var);
	if (var.ret < 0)
		perror("pipex");
	first_fork(env, &var);
	var.ret = init_last_f(argv, &var);
	if (var.ret < 0)
		perror("pipex");
	last_fork(env, &var);
	wait_pids(&var);
	exit_prg(&var);
	return (0);
}
