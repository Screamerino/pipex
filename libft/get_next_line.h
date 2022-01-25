/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <lcoreen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 16:10:54 by lcoreen           #+#    #+#             */
/*   Updated: 2021/12/03 16:28:16 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFFER_SIZE 256

# include <unistd.h>
# include <stdlib.h>

size_t	ft_strlen2(const char *s);
char	*ft_strjoin2(char *s1, char *s2);
char	*ft_strdup2(const char *s1);
size_t	ft_strlcpy2(char *dst, const char *src, size_t dstsize);
char	*get_next_line(int fd);

#endif
