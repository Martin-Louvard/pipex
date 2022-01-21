/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malouvar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 10:37:35 by malouvar          #+#    #+#             */
/*   Updated: 2022/01/21 17:16:22 by malouvar         ###   ########.fr       */
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
}	t_params;

int		__err(char *msg);
void	__perr(char *msg);
void	__free_params(t_params *params);
char	*__paths(char **envp);
void	__free_args(t_params *params);
#endif
