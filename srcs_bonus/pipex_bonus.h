/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malouvar <malouvar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 10:37:35 by malouvar          #+#    #+#             */
/*   Updated: 2022/01/24 16:55:31 by malouvar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <stdio.h>
# include <string.h>
# include "../libft/includes/libft.h"

typedef struct s_params
{
	int		*ends;
	int		infile;
	int		outfile;
	pid_t	child;
	char	*paths;
	char	**cmd_paths;
	char	**cmd_args;
	char	*cmd;
	int		heredoc;
	int		pipe_nb;
	int		cmd_nb;
	int		child_n;
}	t_params;

void	__open_files(t_params *params, int argc, char **argv);
void	__heredoc(t_params *params, char *limiter);
void	__init_pipes(t_params *params, char **envp);
void	__close_tube(t_params *params);
void	__child(t_params *params, char **argv, char **envp);
void	__dup2(int new_in, int new_out);
char	*__cmd(char **cmd_paths, char *args);
int		__check_heredoc(char *argv1, t_params *params);
void	__free_params(t_params *params);
void	__free_args(t_params *params);
char	*__paths(char **envp);
int		__err(char *msg);
void	__perr(char *msg);
#endif
