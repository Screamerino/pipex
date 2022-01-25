/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <lcoreen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 17:43:26 by lcoreen           #+#    #+#             */
/*   Updated: 2021/12/03 17:58:26 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "libft.h"
# include <stdio.h>

typedef struct s_args
{
	int		argc;
	char	**argv;
	char	**env;
	int		outfile;
	int		infile;
	int		*pipes;
	int		here_doc_flag;
}	t_args;

char	*get_cmd(char *str, char **env);
void	run_child(t_args *args, int i);
void	close_pipe(t_args *args, int i);
void	open_files(t_args *args, int argc, char **argv);

#endif