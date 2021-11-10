/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thpham-v <thpham-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 17:17:18 by thpham-v          #+#    #+#             */
/*   Updated: 2021/09/23 18:12:27 by thpham-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_path(char **env)
{
	int		i;
	char	**tab_path;

	i = 0;
	tab_path = NULL;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
		{
			tab_path = ft_split(env[i] + 5, ':');
			break ;
		}
		i++;
	}
	return (tab_path);
}

char	*get_cmd(char *argv)
{
	int		i;
	char	*cmd;

	i = 0;
	cmd = NULL;
	while (argv[i] && argv[i] != ' ')
		i++;
	if (i > 0)
		cmd = ft_strndup(argv, i);
	return (cmd);
}

char	*get_option(char *argv)
{
	int		i;
	char	*opt;

	i = 0;
	opt = NULL;
	while (argv[i])
	{
		if (argv[i] == ' ')
		{
			while (argv[i] == ' ')
				i++;
			break ;
		}
		i++;
	}
	if (argv[i])
		opt = ft_strndup(&argv[i], ft_strlen(&argv[i]));
	return (opt);
}

char	*get_cmd_path(char *cmd, char **path)
{
	char	*res;
	int		i;
	int		cmd_len;
	int		path_len;

	i = -1;
	cmd_len = ft_strlen(cmd);
	while (path && path[++i])
	{
		path_len = ft_strlen(path[i]);
		res = malloc(sizeof(char) * (path_len + cmd_len + 2));
		if (!res)
			return (NULL);
		ft_strcpy(res, path[i]);
		res[path_len] = '/';
		res[path_len + 1] = '\0';
		ft_strcat(res, cmd);
		if (!access(res, F_OK))
			return (res);
		free(res);
	}
	return (NULL);
}
