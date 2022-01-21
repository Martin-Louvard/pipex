/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malouvar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 11:45:19 by malouvar          #+#    #+#             */
/*   Updated: 2022/01/21 14:14:02 by malouvar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	__free_params(t_params *params)
{
	int	i;
	
	i = 0;
	close(params->infile);
	close(params->outfile);
	while (params->cmd_paths[i])
	{
		free(params->cmd_paths[i]);
		i++;
	}
	free(params->cmd_paths);
}

char	*get_paths(char **envp)
{
	while (__strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

int	err(char *msg)
{
	write(2, msg, __strlen(msg));
	return (1);
}

void	perr(char *msg)
{
	perror(msg);
	exit(1);
}
