/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malouvar <malouvar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 10:36:14 by malouvar          #+#    #+#             */
/*   Updated: 2022/01/24 14:09:37 by malouvar         ###   ########.fr       */
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

void	__close_tube(t_params *params, int argc)
{
	int	i;

	i = 0;
	while (i < params->pipe_nb)
	{
		close(params->end[i]);
		i++;
	}
}

void	__init_pipes(t_params *params, int argc, char **argv, char **envp)
{
	int	i;

	i = 0;
	pipe = malloc(sizeof(int) * (params->pipe_nb));
	if (!pipe)
		__perr("Malloc error !");
	while (i < params->cmd_nb)
	{
		if (pipe(params->ends + (2 * i) < 0))
			__perr("Pipe error !");
		i++;
	}
	params.paths = __paths(envp);
	params.cmd_paths = __split(params.paths, ':');
}

int	__heredoc(t_params *params, char *limiter)
{
	int		fd;
	char	*line;

	fd = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (fd < 0)
		__perr("Error while creating Heredoc!");
	while (1)
	{
		write(1, "heredoc> ", 9);
		line = get_next_line(0);
		if (!__strncmp(limiter, line, __strlen(limiter)))
			break ;
		write(fd, line, __strlen(line));
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
		__heredoc(&params, argv[2]);
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
	__init_pipes(&params, argc, argv, envp);
	__close_tube(&params);
	waitpid(-1, NULL, 0);
	__free_params(&params);
	return (0);
}
