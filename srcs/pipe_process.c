/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysong <ysong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 12:20:24 by ysong             #+#    #+#             */
/*   Updated: 2021/09/30 12:27:25 by ysong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_pipe_in(t_info *info, char *argv[], char *envp[])
{
	info->f_in = open(argv[1], O_RDONLY);
	if (info->f_in < 0)
		ft_pipe_exit("Error : input file\n");
	close(info->fd[0]);
	if (dup2(info->fd[1], STDOUT_FILENO) == -1)
		ft_pipe_exit("Error : dup failed1\n");
	close(info->fd[1]);
	if (dup2(info->f_in, STDIN_FILENO) == -1)
		ft_pipe_exit("Error : dup failed2\n");
	close(info->f_in);
	ft_pipe_execute(info, argv[2], envp);
}

void	ft_pipe_out(t_info *info, char *argv[], char *envp[])
{
	info->f_out = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (info->f_out < 0)
		ft_pipe_exit("Error : output file\n");
	close(info->fd[1]);
	if (dup2(info->fd[0], STDIN_FILENO) == -1)
		ft_pipe_exit("Error : dup failed3\n");
	close(info->fd[0]);
	if (dup2(info->f_out, STDOUT_FILENO) == -1)
		ft_pipe_exit("Error : dup failed4\n");
	close(info->f_out);
	ft_pipe_execute(info, argv[3], envp);
}

void pipe_process(t_info *info, char **av, char **ev)
{
	pid_t pid1;
	pid_t pid2;

	if (pipe(info->fd) == -1)
		pipe_exit("Error: pipe failed\n");
	pid1 = fork();
	if (pid1 == -1)
		pipe_exit("Error: fork failed\n");
	if (pid1 == 0)
		pipe_in(info, av, ev);
	pid2 = fork();
	if (pid2 == -1)
		pipe_exit("Error: fork failed\n");
	if (pid2 == 0)
		pipe_out(info, av, ev);
	close(info->fd[0]);
	close(info->fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}
