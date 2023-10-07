/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: about <about@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 08:06:28 by about             #+#    #+#             */
/*   Updated: 2022/11/22 15:09:47 by about            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line_bonus.h"

static char	*get_after_line(char *src)
{
	size_t	i;
	char	*p;

	if (!src)
		return (NULL);
	i = 0;
	while (src[i] != '\0' && src[i] != '\n')
		i++;
	if (src[i] == '\n')
		i++;
	p = ft_strdup(src + i);
	free(src);
	return (p);
}

static char	*get_line(char *line, int fd)
{
	char	*buf;
	int		i;

	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	i = 1;
	while (!ft_strchr(line, '\n') && i != 0)
	{
		i = read(fd, buf, BUFFER_SIZE);
		if (i == -1)
		{
			free(buf);
			free(line);
			return (NULL);
		}
		buf[i] = '\0';
		if (line == NULL)
			line = ft_strdup("");
		line = ft_strjoin(line, buf);
	}
	free(buf);
	return (line);
}

static char	*set_line(char *src)
{
	char	*dst;
	size_t	i;

	i = 0;
	dst = NULL;
	if (!*src)
	{
		free(src);
		return (NULL);
	}
	while (src[i] && src[i] != '\n')
		i++;
	if (src[i] == '\n')
		i++;
	dst = malloc(sizeof(char) * (i + 1));
	if (!dst)
		return (NULL);
	i = -1;
	while (src[++i] && src[i] != '\n')
		dst[i] = src[i];
	if (src[i] == '\n')
		dst[i++] = '\n';
	dst[i] = '\0';
	return (dst);
}

char	*get_next_line(int fd)
{
	static char	*next[OPEN_MAX];
	char		*line;

	line = NULL;
	if (fd < 0 && BUFFER_SIZE <= 0)
		return (NULL);
	if (read(fd, NULL, 0) < 0)
	{
		if (next[fd])
			free(next[fd]);
		next[fd] = NULL;
		return (NULL);
	}
	next[fd] = get_line(next[fd], fd);
	line = set_line(next[fd]);
	if (!line)
		next[fd] = NULL;
	next[fd] = get_after_line(next[fd]);
	return (line);
}
