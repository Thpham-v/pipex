/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thpham-v <thpham-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 16:50:27 by thpham-v          #+#    #+#             */
/*   Updated: 2021/11/18 15:22:57 by thpham-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_variables(t_var *var)
{
	if (var->path)
		ft_free_tab(var->path);
	if (var->cmd)
		free(var->cmd);
	if (var->cmd_path)
		free(var->cmd_path);
}

void	exit_prg(t_var *var)
{
	free_variables(var);
	if (var->ret == -4)
		exit(126);
	if (var->ret == -3 && (errno == 2 || errno == 13))
		exit (127);
	if (var->ret < 0)
		exit (1);
	else
		exit(var->exit);
}

void	execve_error(t_var *var)
{
	int	fd;

	var->ret = -3;
	if (!var->path)
		perror("pipex");
	else if (is_slash(var->str[0]))
	{
		fd = open(var->str[0], O_DIRECTORY);
		if (fd != -1)
		{
			close(fd);
			ft_putstr_fd("pipex: ", STDERR_FILENO);
			ft_putstr_fd(var->cmd, STDERR_FILENO);
			ft_putstr_fd(" is a directory\n", STDERR_FILENO);
			var->ret = -4;
		}
		else
			perror("pipex");
	}
	else
		cmd_not_found(var->cmd);
	exit_prg(var);
}
