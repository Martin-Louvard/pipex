/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malouvar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 10:36:14 by malouvar          #+#    #+#             */
/*   Updated: 2022/01/21 16:11:06 by malouvar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*__cmd(char **cmd_paths, char *args)
{
	char	*try;
	char	*tmp;

	while (*cmd_paths)
	{
		tmp = __strjoin(*cmd_paths, "/");
		try = __strjoin(tmp, args);
		free(tmp);
		if (access(try, 0) == 0)
			return (try);
		free(try);
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
		__err("Error with first command\n");
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
		__err("Error with second command\n");
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

	if (argc != 5)
		return (__err("Wrong number of arguments\n"));
	params.infile = open(argv[1], O_RDONLY);
	if (params.infile < 0)
		__perr("Infile error !");
	params.outfile = open(argv[4], O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (params.outfile < 0)
		__perr("Outfile error !");
	if (pipe(params.end) < 0)
		__perr("Pipe error !");
	params.paths = __paths(envp);
	params.cmd_paths = __split(params.paths, ':');
	params.child1 = fork();
	if (params.child1 == 0)
		__first_proc(params, argv, envp);
	params.child2 = fork();
	if (params.child2 == 0)
		__second_proc(params, argv, envp);
	__close_tube(&params);
	waitpid(params.child1, NULL, 0);
	waitpid(params.child2, NULL, 0);
	__free_params(&params);
	return (0);
}
