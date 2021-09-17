#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <errno.h>

typedef struct	s_var
{
	int		fd_file;
	int		fd[2];
	char	*str[3];
	char	**path;
	char	*cmd;
	char	*cmd_path;
	pid_t	pid;
}				t_var;


char	**ft_split(char *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**get_path(char **env);
char	*ft_strndup(char *src, int n);
int		ft_strlen(char *str);
char	*get_cmd(char *argv);
char	*get_option(char *argv);
char	*ft_strcpy(char *dest,char *src);
char	*get_cmd_path(char *cmd, char **path);
char	*ft_strcat(char *s1, char *s2);
void	ft_bzero(void *s, size_t n);
void	first_f(char **env, t_var *var);
void	last_f(char **env, t_var *var);

#endif