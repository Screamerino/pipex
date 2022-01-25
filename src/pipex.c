/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <lcoreen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 16:57:36 by lcoreen           #+#    #+#             */
/*   Updated: 2021/12/03 18:29:35 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute(char *arg, char **env)
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

void	child1_process(int *pipes, int file, char *arg, char **env)
{
	close(pipes[0]);
	if (dup2(file, 0) == -1)
	{
		perror("dup2");
		exit(1);
	}
	if (dup2(pipes[1], 1) == -1)
	{
		perror("dup2");
		exit(1);
	}
	close(pipes[1]);
	close(file);
	execute(arg, env);
}

void	child2_process(int *pipes, int file, char *arg, char **env)
{
	close(pipes[1]);
	if (dup2(pipes[0], 0) == -1)
	{
		perror("dup2");
		exit(1);
	}
	if (dup2(file, 1) == -1)
	{
		perror("dup2");
		exit(1);
	}
	close(pipes[0]);
	close(file);
	execute(arg, env);
}

void	pipex(int infile, int outfile, char **argv, char **env)
{
	int		pipes[2];
	pid_t	child1;
	int		status;
	pid_t	child2;

	if (pipe(pipes) == -1)
		return (perror("pipe error"));
	child1 = fork();
	if (child1 < 0)
		return (perror("fork error (child1)"));
	else if (child1 == 0)
		child1_process(pipes, infile, argv[2], env);
	child2 = fork();
	if (child2 < 0)
		return (perror("fork error (child2)"));
	else if (child2 == 0)
		child2_process(pipes, outfile, argv[3], env);
	close(pipes[0]);
	close(pipes[1]);
	wait(&status);
}

int	main(int argc, char **argv, char **env)
{
	int	infile;
	int	outfile;

	if (argc == 5)
	{
		infile = open(argv[1], O_RDONLY);
		if (infile == -1)
		{
			perror("Infile doesnt open");
			return (1);
		}
		outfile = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (outfile == -1)
		{
			perror("Outfile doesnt open");
			return (1);
		}
		pipex(infile, outfile, argv, env);
	}
	else
		ft_putstr_fd("enter smtg like this"
			" \"./pipex file1 cmd1 cmd2 file2\"\n", 1);
	return (0);
}
