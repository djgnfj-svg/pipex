/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysong <ysong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 12:15:16 by ysong             #+#    #+#             */
/*   Updated: 2021/09/30 12:17:41 by ysong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipe_exit(char *error)
{
	write(2, error, ft_strlen(error));
	exit(1);
}

int main(int ac, char **av, char **ev)
{
	t_info info;

	if (ac != 5)
		pipe_exit("Check Argument: ./pipex file1 cmd1 cmd2 file2\n");
	pipe_process(&info, av, ev);
	return (0);
}