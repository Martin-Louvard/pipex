/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malouvar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 10:36:14 by malouvar          #+#    #+#             */
/*   Updated: 2022/01/21 12:32:13 by malouvar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_paths(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

int	main(int argc, char **argv, char **envp)
{
	t_params	params;

	if (argc != 5)
		return (err("Wrong number of arguments\n"));
	params.infile = open(argv[1], O_RDNOLY);
	if (params.infile < 0)
		perr("Infile error !");
	params.outfile = open(argv[4], O_TRUNC | O_CREAT | O_RDWR);
	if (params.outfile < 0)
		perr("Outfile error !");
	if (pipe(params.end) < 0)
		perr("Pipe error !");
	params.paths = get_paths(envp);
	params.cmd_paths = ft_split(params.path, ':');
	return (0);
}
