/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <lcoreen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 16:57:36 by lcoreen           #+#    #+#             */
/*   Updated: 2021/12/03 18:37:58 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "get_next_line.h"

void	pipex(t_args *args)
{
	int		i;
	pid_t	child;
	int		status;

	i = args->here_doc_flag - 1;
	while (++i < args->argc - 3)
	{
		if (i != args->argc - 4 && pipe(args->pipes + 2 * i) == -1)
		{
			perror("pipe");
			exit(1);
		}
		child = fork();
		if (child < 0)
		{
			perror("fork error (child)");
			close_pipe(args, i);
			exit(1);
		}
		else if (child == 0)
			run_child(args, i);
		else
			close_pipe(args, i - 1);
	}
	wait(&status);
}

void	init_args(t_args *args, int argc, char **argv, char **env)
{
	args->argc = argc;
	args->argv = argv;
	args->env = env;
	args->here_doc_flag = 0;
	if (!ft_strncmp(argv[1], "here_doc", 8))
		args->here_doc_flag = 1;
	open_files(args, argc, argv);
	args->pipes = malloc(sizeof(int) * 2 * (argc - 4));
	if (args->pipes == NULL)
	{
		close(args->infile);
		close(args->outfile);
		exit(1);
	}
}

int	here_doc(t_args *args)
{
	char	*line;

	if (pipe(args->pipes) == -1)
		return (-1);
	ft_putstr_fd("pipex: here_doc> ", 1);
	line = get_next_line(0);
	if (!line)
		return (-1);
	while (line)
	{
		if (!ft_strncmp(args->argv[2], line, ft_strlen(args->argv[2])))
			break ;
		ft_putstr_fd(line, args->pipes[1]);
		free(line);
		ft_putstr_fd("pipex: here_doc> ", 1);
		line = get_next_line(0);
		if (!line)
			return (-1);
	}
	free(line);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_args	args;

	if (argc <= 4 || (!ft_strncmp(argv[1], "here_doc", 8) && argc != 6))
	{
		ft_putstr_fd("enter something like this"
			" \"./pipex file1 cmd1 ... cmdn file2\"\n", 1);
		ft_putstr_fd("enter something like this"
			" \"./pipex here_doc LIMITER cmd1 cmd2 file2\"\n", 1);
	}
	else
	{
		init_args(&args, argc, argv, env);
		if (args.here_doc_flag)
		{
			if (here_doc(&args) == -1)
			{
				close_pipe(&args, 0);
				free(args.pipes);
				return (1);
			}
		}
		pipex(&args);
		free(args.pipes);
	}
	return (0);
}
