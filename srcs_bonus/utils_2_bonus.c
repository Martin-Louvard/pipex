/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malouvar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 16:53:57 by malouvar          #+#    #+#             */
/*   Updated: 2022/01/24 16:57:33 by malouvar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	__close_tube(t_params *params)
{
	int	i;

	i = 0;
	while (i < params->pipe_nb)
	{
		close(params->ends[i]);
		i++;
	}
}

void	__init_pipes(t_params *params, char **envp)
{
	int	i;

	i = 0;
	params->paths = __paths(envp);
	params->cmd_paths = __split(params->paths, ':');
	if (!params->cmd_paths)
	{
		__free_params(params);
		__perr("Malloc error !");
	}
	params->ends = malloc(sizeof(int) * (params->pipe_nb));
	if (!params->ends)
	{
		__free_params(params);
		__perr("Malloc error !");
	}
	while (i < params->cmd_nb - 1)
	{
		if (pipe(params->ends + (2 * i)) < 0)
		{
			__free_params(params);
			__perr("Pipe error !");
		}
		i++;
	}
}

void	__child(t_params *params, char **argv, char **envp)
{
	params->child = fork();
	if (params->child == 0)
	{
		if (params->child_n == 0)
			__dup2(params->infile, params->ends[1]);
		else if (params->child_n == (params->cmd_nb - 1))
			__dup2(params->ends[2 * params->child_n - 2], params->outfile);
		else
			__dup2(params->ends[2 * params->child_n - 2],
				params->ends[2 * params->child_n + 1]);
		__close_tube(params);
		params->cmd_args = __split(argv[2 + params->heredoc
				+ params->child_n], ' ');
		params->cmd = __cmd(params->cmd_paths, params->cmd_args[0]);
		if (!params->cmd)
		{
			__free_args(params);
			__err("Can't find binary file for command\n");
			exit(1);
		}
		execve(params->cmd, params->cmd_args, envp);
	}
}

int	__check_heredoc(char *argv1, t_params *params)
{
	if (argv1 && !__strncmp(argv1, "here_doc", 9))
	{
		params->heredoc = 1;
		return (6);
	}
	else
	{
		params->heredoc = 0;
		return (5);
	}
}
