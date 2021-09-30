#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>


typedef struct s_info
{
	int		fd[2];
	int		f_in;
	int		f_out;
	char	**command;
	char	**paths;
	char	*path;
	char	*path_cmd;
}	t_info;

typedef struct s_parse
{
	int		i;
	int		j;
	int		cnt;
	int		len;
	char	**pstr;
}	t_parse;

void	pipe_exit(char *error);
#endif