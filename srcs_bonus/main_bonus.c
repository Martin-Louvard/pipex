/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malouvar <malouvar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 10:36:14 by malouvar          #+#    #+#             */
/*   Updated: 2022/01/24 15:14:02 by malouvar         ###   ########.fr       */
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

void	__dup2(int new_in, int new_out)
{
	dup2(new_in, 0);
	dup2(new_out, 1);
}

void	__child(t_params *params, char **argv, char **envp)
{
	params->child = fork();
	if (params->child == 0)
	{
		if (params->child_n == 0)
			__dup2(params->infile, params->ends[1]);
		else if (params->child_n == (params->cmd_nb - 1))
			__dup2(params->ends[params->pipe_nb - 1] ,params->outfile);
		else
			__dup2(params->ends[2 * params->child_n - 2], params->ends[2 * params->child_n + 1]);
		params->cmd_args = __split(argv[2 + params->heredoc + params->child_n], ' ');
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
	while (i < params->cmd_nb)
	{
		if (pipe(params->ends + (2 * i)) < 0)
		{
			__free_params(params);
			__perr("Pipe error !");
		}
		i++;
	}
}

void	__heredoc(t_params *params, char *limiter)
{
	int		fd;
	char	*line;

	fd = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (fd < 0)
		__perr("Error while creating Heredoc!");
	while (1)
	{
		write(1, "heredoc> ", 9);
		line = __gnl(0);
		if (!__strncmp(limiter, line, __strlen(limiter)))
			break ;
		write(fd, line, __strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	free(line);
	close(fd);
	params->infile = open(".heredoc_tmp", O_RDONLY);
	if (params->infile < 0)
	{
			unlink(".heredoc_tmp");
			__perr("Infile error !");
	}
}

void	__open_files(t_params *params, int argc, char **argv)
{
	if (!params->heredoc)
	{
		params->infile = open(argv[1], O_RDONLY);
		if (params->infile < 0)
			__perr("Infile error !");
		params->outfile = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0644);
		if (params->outfile < 0)
			__perr("Outfile error !");
	}
	else
	{
		__heredoc(params, argv[2]);
		params->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0000644);
		if (params->outfile < 0)
			__perr("Outfile error !");
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_params	params;

	if (__check_heredoc(argv[1], &params) < argc)
		return (__err("Not enough arguments"));
	params.cmd_nb = argc - 3 - params.heredoc;
	params.pipe_nb = (params.cmd_nb - 1) * 2;
	__open_files(&params, argc, argv);
	__init_pipes(&params, envp);
	params.child_n = 0;
	while (params.child_n < params.cmd_nb)
	{
		__child(&params, argv, envp);
		params.child_n++;
	}
	__close_tube(&params);
	waitpid(-1, NULL, 0);
	__free_params(&params);
	return (0);
}
