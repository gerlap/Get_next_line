/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glapshin <glapshin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 20:40:17 by glapshin          #+#    #+#             */
/*   Updated: 2025/01/11 17:55:14 by glapshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;

	src_len = ft_strlen(src);
	if (NULL == dst || NULL == src || !dstsize)
		return (src_len);
	while (*src && --dstsize)
		*dst++ = *src++;
	*dst = '\0';
	return (src_len);
}

void	reader(char **global_buffer, char *buffer, int fd)
{
	char	*temp_buffer;
	int		bytes_read;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buffer);
			free(*global_buffer);
			*global_buffer = NULL;
			return ;
		}
		buffer[bytes_read] = '\0';
		temp_buffer = *global_buffer;
		*global_buffer = ft_strjoin(*global_buffer, buffer);
		free(temp_buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free (buffer);
}

char	*extract_line(char *global_buffer)
{
	char	*line;
	int		i;

	if (!global_buffer)
		return (NULL);
	i = 0;
	while (global_buffer[i] != '\n' && global_buffer[i] != '\0')
		i++;
	if (global_buffer[i] == '\n')
		i++;
	line = ft_substr(global_buffer, 0, i);
	if (!line)
		return (NULL);
	return (line);
}

void	update_buffer(char **global_buffer, char *line)
{
	char	*temp;

	if (!*global_buffer)
		return ;
	if (!line)
	{
		free(*global_buffer);
		*global_buffer = NULL;
		return ;
	}
	temp = ft_strdup(*global_buffer + ft_strlen(line));
	free(*global_buffer);
	*global_buffer = temp;
}

char	*get_next_line(int fd)
{
	static char	*global_buffer;
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!global_buffer)
		global_buffer = ft_strdup("");
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (free(global_buffer), NULL);
	reader(&global_buffer, buffer, fd);
	line = extract_line(global_buffer);
	update_buffer(&global_buffer, line);
	if (!global_buffer)
		return (free(global_buffer), NULL);
	if (line && !line[0])
	{
		free(line);
		free(global_buffer);
		global_buffer = NULL;
		return (NULL);
	}
	return (line);
}
