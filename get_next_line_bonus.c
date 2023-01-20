/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kilchenk <kilchenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 19:41:03 by kilchenk          #+#    #+#             */
/*   Updated: 2023/01/20 16:53:46 by kilchenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*strjoin_free(char *s1, char *s2)
{
	char	*ret;

	if (s1 == NULL)
		ret = ft_strjoin("", s2);
	else
	{
		ret = ft_strjoin(s1, s2);
		free(s1);
	}
	return (ret);
}

char	*trim_start(char *str)
{
	size_t	i;
	char	*t;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{	
		free(str);
		return (NULL);
	}
	t = ft_substr(str, i + 1, ft_strlen(str) - i - 1);
	free(str);
	return (t);
}

char	*trim_end(char *str)
{
	size_t	i;
	char	*t;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	t = ft_substr(str, 0, i + 1);
	return (t);
}

char	*read_file(int fd, char *ret)
{
	int		read_b;
	char	*line;

	line = malloc(BUFFER_SIZE + 1);
	read_b = read(fd, line, BUFFER_SIZE);
	while (read_b != 0)
	{
		if (read_b == -1)
		{
			if (ret)
				free(ret);
			free(line);
			return (NULL);
		}
		line[read_b] = 0;
		ret = strjoin_free(ret, line);
		if (ft_strrchr(line, '\n'))
			break ;
		read_b = read(fd, line, BUFFER_SIZE);
	}
	free(line);
	return (ret);
}

char	*get_next_line(int fd)
{
	static char	*line[1024];
	char		*ret;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (read(fd, 0, 0) < 0)
	{
		if (line[fd])
			free(line[fd]);
		line[fd] = NULL;
		return (NULL);
	}
	if (!ft_strrchr(line[fd], '\n'))
		line[fd] = read_file(fd, line[fd]);
	if (!line[fd])
		return (NULL);
	ret = trim_end(line[fd]);
	line[fd] = trim_start(line[fd]);
	return (ret);
}
