/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <lcoreen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 19:21:54 by lcoreen           #+#    #+#             */
/*   Updated: 2021/12/03 16:28:16 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	count_lines(char *save)
{
	int	res;
	int	i;

	i = 0;
	res = 0;
	while (save[i])
	{
		if (save[i] == '\n')
			++res;
		++i;
	}
	return (res);
}

char	*read_line(int fd, char *ret, char *save)
{
	int		rd;
	char	buf[BUFFER_SIZE + 1];

	rd = read(fd, buf, BUFFER_SIZE);
	buf[rd] = '\0';
	while (rd > 0 && count_lines(buf) == 0)
	{
		ret = ft_strjoin2(ret, buf);
		if (ret == NULL)
			return (NULL);
		rd = read(fd, buf, BUFFER_SIZE);
		buf[rd] = '\0';
	}
	ret = ft_strjoin2(ret, buf);
	if (ret == NULL)
		return (NULL);
	ft_strlcpy2(save, buf + ft_strlen2(buf), BUFFER_SIZE + 1);
	if (ft_strlen2(ret) == 0)
	{
		free(ret);
		return (NULL);
	}
	return (ret);
}

char	*get_next_line(int fd)
{
	static char	save[BUFFER_SIZE + 1];
	char		*ret;

	if (read(fd, save, 0) == -1 || BUFFER_SIZE == 0)
		return (NULL);
	ret = ft_strdup2(save);
	if (ret == NULL)
		return (NULL);
	if (count_lines(save) == 0)
	{
		ret = read_line(fd, ret, save);
		if (ret == NULL)
			return (NULL);
	}
	else
		ft_strlcpy2(save, save + ft_strlen2(save), BUFFER_SIZE + 1);
	return (ret);
}
