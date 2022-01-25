/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_child_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <lcoreen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 17:41:25 by lcoreen           #+#    #+#             */
/*   Updated: 2021/12/03 17:41:53 by lcoreen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	execute(char *arg, char **env)
{
	char	*cmd;
	char	**new_argv;

	new_argv = ft_split(arg, ' ');
	if (!new_argv)
	{
		perror("split");
		exit(1);
	}
	cmd = get_cmd(arg, env);
	if (!cmd)
	{
		ft_freearr(new_argv);
		perror("get_cmd");
		exit(1);
	}
	execve(cmd, new_argv, env);
	perror("execve");
	free(cmd);
	ft_freearr(new_argv);
	exit(1);
}

static void	begin_child(t_args *args)
{
	if (dup2(args->pipes[1], 1) == -1)
	{
		perror("dup2");
		exit(1);
	}
	if (dup2(args->infile, 0) == -1)
	{
		perror("dup2");
		exit(1);
	}
	close_pipe(args, 0);
	close(args->infile);
}

static void	end_child(t_args *args, int i)
{
	if (dup2(args->pipes[2 * (i - 1)], 0) == -1)
	{
		perror("dup2");
		exit(1);
	}
	close_pipe(args, i - 1);
	if (dup2(args->outfile, 1) == -1)
	{
		perror("dup2");
		exit(1);
	}
	close(args->outfile);
}

static void	mid_child(t_args *args, int i)
{
	if (dup2(args->pipes[2 * (i - 1)], 0) == -1)
	{
		perror("dup2");
		exit(1);
	}
	close_pipe(args, i - 1);
	if (dup2(args->pipes[2 * i + 1], 1) == -1)
	{
		perror("dup2");
		exit(1);
	}
	close_pipe(args, i);
}

void	run_child(t_args *args, int i)
{
	if (i == 0)
		begin_child(args);
	else if (i == args->argc - 4)
		end_child(args, i);
	else
		mid_child(args, i);
	execute(args->argv[i + 2], args->env);
}
