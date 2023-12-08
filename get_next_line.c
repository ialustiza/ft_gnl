/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialustiz <ialustiz@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:51:36 by ialustiz          #+#    #+#             */
/*   Updated: 2023/12/08 11:51:40 by ialustiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
// #include <fcntl.h>
// #include <stdio.h>

static void	gnl_read(int fd, char *buf, char **str)
{
	size_t	bytes;
	char	*line;

	bytes = read(fd, buf, BUFFER_SIZE);
	while (bytes > 0)
	{
		buf[bytes] = 0;
		if (!*str)
			*str = ft_substr(buf, 0, bytes);
		else
		{
			line = *str;
			*str = ft_strjoin(*str, buf);
			free(line);
		}
		if (ft_strchr(buf, '\n'))
			break ;
		bytes = read(fd, buf, BUFFER_SIZE);
	}
	free(buf);
}

static char	*gnl_make(char **str)
{
	size_t	left;
	size_t	rigth;
	char	*line;
	char	*tmp;

	if (!*str)
		return (NULL);
	if (!ft_strchr(*str, '\n'))
	{
		line = ft_substr(*str, 0, ft_strlen(*str));
		free(*str);
		*str = 0;
		return (line);
	}
	left = ft_strlen(*str);
	rigth = ft_strlen(ft_strchr(*str, '\n'));
	line = ft_substr(*str, 0, left - rigth + 1);
	tmp = *str;
	*str = ft_substr(ft_strchr(*str, '\n'), 1, rigth - 1);
	free(tmp);
	return (line);
}

char	*get_next_line(int fd)
{
	char		*buf;
	static char	*str;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (0);
	if (BUFFER_SIZE < 1 || fd == -1 || read(fd, buf, 0) == -1)
	{
		free(buf);
		free(str);
		str = NULL;
		return (0);
	}
	gnl_read(fd, buf, &str);
	return (gnl_make(&str));
}

// int	main(void)
// {
// 	int	fd;
// 	int	line;

// 	fd = open("read_error.txt", O_RDONLY);
// 	line = 4;
// 	printf("L1: %s", get_next_line(fd));
// 	printf("L2: %s", get_next_line(fd));
// 	printf("L3: %s", get_next_line(100));
// 	close(fd);
// 	fd = open("read_error.txt", O_RDONLY);
// 	printf("L4: %s", get_next_line(fd));
// 	printf("L5: %s", get_next_line(fd));
// 	printf("L6: %s", get_next_line(fd));
// 	close(fd);	
// }
