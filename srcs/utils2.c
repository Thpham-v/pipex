/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thpham-v <thpham-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 16:45:38 by thpham-v          #+#    #+#             */
/*   Updated: 2021/09/23 18:35:18 by thpham-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	is_slash(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

void	ft_putstr_fd(char *str, int fd)
{
	if (str)
		write(fd, str, ft_strlen(str));
}

void	cmd_not_found(char *cmd)
{
	ft_putstr_fd("pipex: command not found: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

void	wait_pids(t_var *var)
{
	if (var->pid1 != 0)
	{
		waitpid(var->pid1, &var->status, 0);
		if (WIFEXITED(var->status))
			var->exit = WEXITSTATUS(var->status);
	}
	if (var->pid2 != 0)
	{
		waitpid(var->pid2, &var->status, 0);
		if (WIFEXITED(var->status))
			var->exit = WEXITSTATUS(var->status);
	}
}
