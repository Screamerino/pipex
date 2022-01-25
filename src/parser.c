/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <lcoreen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 16:56:51 by lcoreen           #+#    #+#             */
/*   Updated: 2021/12/01 15:04:19 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static char	*get_path(char **env)
{
	char	**temp;
	char	*res;

	while (*env)
	{
		temp = ft_split(*env, '=');
		if (temp == NULL)
			return (NULL);
		if (ft_strncmp(temp[0], "PATH", 4) == 0)
			break ;
		else
		{
			ft_freearr(temp);
			env++;
		}
	}
	res = ft_strdup(temp[1]);
	ft_freearr(temp);
	return (res);
}

static char	*add_char(char *str, char ch)
{
	char	*path;
	int		i;

	i = 0;
	path = (char *) malloc(ft_strlen(str) + 2);
	if (!path)
		return (NULL);
	while (str[i])
	{
		path[i] = str[i];
		++i;
	}
	path[i++] = ch;
	path[i] = '\0';
	return (path);
}

static char	*check_cmd(char *path, char *cmd)
{
	char	*temp;
	char	*temp_path;

	temp_path = add_char(path, '/');
	if (!temp_path)
		return (NULL);
	temp = ft_strjoin(temp_path, cmd);
	free(temp_path);
	if (!temp)
		return (NULL);
	if (access(temp, X_OK) == 0)
		return (temp);
	free(temp);
	return (NULL);
}

static char	*find_cmd(char *str, char *cmd)
{
	char	**paths;
	char	*temp;
	int		i;

	i = 0;
	paths = ft_split(str, ':');
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		temp = check_cmd(paths[i], cmd);
		if (temp)
			break ;
		++i;
	}
	ft_freearr(paths);
	return (temp);
}

char	*get_cmd(char *str, char **env)
{
	char	**splitted_cmd;
	char	*paths;
	char	*cmd;

	splitted_cmd = ft_split(str, ' ');
	if (!splitted_cmd)
		return (NULL);
	paths = get_path(env);
	if (!paths)
	{
		ft_freearr(splitted_cmd);
		return (NULL);
	}
	cmd = find_cmd(paths, splitted_cmd[0]);
	ft_freearr(splitted_cmd);
	free(paths);
	return (cmd);
}
