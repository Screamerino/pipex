/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <lcoreen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 17:41:31 by lcoreen           #+#    #+#             */
/*   Updated: 2021/12/03 17:41:53 by lcoreen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	close_pipe(t_args *args, int i)
{
	if (i >= 0)
	{
		close(args->pipes[2 * i]);
		close(args->pipes[2 * i + 1]);
	}
}

void	open_files(t_args *args, int argc, char **argv)
{
	if (!args->here_doc_flag)
	{
		args->infile = open(argv[1], O_RDONLY);
		if (args->infile == -1)
		{
			perror("Infile doesnt open");
			exit(1);
		}
		args->outfile = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (args->outfile == -1)
		{
			close(args->infile);
			perror("Outfile doesnt open");
			exit(1);
		}
	}
	else
	{
		args->outfile = open(argv[argc - 1], O_CREAT | O_RDWR | O_APPEND, 0644);
		if (args->outfile == -1)
		{
			perror("Outfile doesnt open");
			exit(1);
		}
	}
}
