/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malouvar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 10:37:35 by malouvar          #+#    #+#             */
/*   Updated: 2022/01/21 12:25:39 by malouvar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <stdio.h>
# include <string.h>
# include "libft/includes/libft.h"

typedef struct s_params
{
	int 	end[2];
	int		infile;
	int		outfile;
	pid_t	child1;
	pid_t	child2;
	char	*paths;
	char	**cmd_paths;
	char	**cmd_args;
	char	*cmd;
}	t_params;

int	err(char *msg);

#endif
