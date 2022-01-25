/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <lcoreen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 16:11:07 by lcoreen           #+#    #+#             */
/*   Updated: 2021/12/03 17:33:20 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	ft_strlen2(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != '\n')
		++i;
	if (s[i] == '\n')
		++i;
	return (i);
}

char	*ft_strdup2(const char *s1)
{
	char	*dup;
	int		i;

	i = 0;
	dup = (char *) malloc(ft_strlen2(s1) + 1);
	if (dup == NULL)
		return (NULL);
	while (s1[i] != '\0' && s1[i] != '\n')
	{
		dup[i] = s1[i];
		++i;
	}
	if (s1[i] == '\n')
	{
		dup[i] = s1[i];
		++i;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_strjoin2(char *s1, char *s2)
{
	char	*ret;
	size_t	i;

	ret = (char *) malloc(ft_strlen2(s1) + ft_strlen2(s2) + 1);
	if (ret == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		ret[i] = s1[i];
		++i;
	}
	free(s1);
	while (*s2 && *s2 != '\n')
	{
		ret[i] = *s2;
		++s2;
		++i;
	}
	if (*s2 == '\n')
		ret[i++] = *s2;
	ret[i] = '\0';
	return (ret);
}

size_t	ft_strlcpy2(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		++i;
	}
	while (i < dstsize)
		dst[i++] = 0;
	return (ft_strlen2(src));
}
