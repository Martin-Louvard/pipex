/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malouvar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 10:36:14 by malouvar          #+#    #+#             */
/*   Updated: 2022/01/21 17:39:13 by malouvar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*__cmd(char **cmd_paths, char *args)
{
	char	*guess;
	char	*tmp;

	while (*cmd_paths)
	{
		tmp = __strjoin(*cmd_paths, "/");
		guess = __strjoin(tmp, args);
		free(tmp);
		if (access(guess, 0) == 0)
			return (guess);
		free(guess);
		cmd_paths++;
	}
	return (NULL);
}

void	__first_proc(t_params params, char **argv, char **envp)
{
	dup2(params.end[1], 1);
	close(params.end[0]);
	dup2(params.infile, 0);
	params.cmd_args = __split(argv[2], ' ');
	params.cmd = __cmd(params.cmd_paths, params.cmd_args[0]);
	if (!params.cmd)
	{
		__free_args(&params);
		__err("Can't find binary file for first command\n");
		exit(1);
	}
	execve(params.cmd, params.cmd_args, envp);
}

void	__second_proc(t_params params, char **argv, char **envp)
{
	dup2(params.end[0], 0);
	close(params.end[1]);
	dup2(params.outfile, 1);
	params.cmd_args = __split(argv[3], ' ');
	params.cmd = __cmd(params.cmd_paths, params.cmd_args[0]);
	if (!params.cmd)
	{
		__free_args(&params);
		__err("Can't find binary file for second command\n");
		exit(1);
	}
	execve(params.cmd, params.cmd_args, envp);
}

void	__close_tube(t_params *params)
{
	close(params->end[0]);
	close(params->end[1]);
}

int	main(int argc, char **argv, char **envp)
{
	t_params	params;

	__check_heredoc(argv[1], &params);

	return (0);
}
