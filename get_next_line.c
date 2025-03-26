/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xviladri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 19:15:56 by xviladri          #+#    #+#             */
/*   Updated: 2025/03/26 19:16:30 by xviladri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE
# define GET_NEXT_LINE

#	ifndef BUFFER_SIZE
#	define BUFFER_SIZE 42
#	endif

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

char	*ft_strdup(char *str);
char	*get_next_line(int fd);
#endif

char	*ft_strdup(char *str)
{
	int	i;
	char	*cpy;
	i = 0;
	if (!str || !str[0])
		return (NULL);
	while (str[i])
		i++;
	cpy = (char *)malloc(i + 1 * sizeof(char));
	if (!cpy)
		return (NULL);
	i = 0;
	while (str[i])
	{
		cpy[i] = str[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}
char	*get_next_line(int fd)
{
	static char buffer[BUFFER_SIZE];
	static int pos;
	static int bytes;
	int i;
	char line[15000];
	i = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		if (pos >= bytes)
		{
			bytes = read(fd, buffer, BUFFER_SIZE);
			pos = 0;
			if (bytes <= 0)
				break ;
		}
		if (buffer[pos] == '\n')
		{
			line[i++] = buffer[pos++];
			break ;
		}
		line[i++] = buffer[pos++];
	}
	line[i] = '\0';
	if (i == 0 && bytes <= 0)
		return (NULL);
	return (ft_strdup(line));
}
