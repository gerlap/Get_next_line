/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glapshin <glapshin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 20:40:17 by glapshin          #+#    #+#             */
/*   Updated: 2025/01/10 21:43:45 by glapshin         ###   ########.fr       */
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

char	*reader(char **basin_buffer, char *buffer, int fd)
{
	char	*temp_buffer;
	int		bytes_read;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			return (free(buffer), NULL);
		buffer[bytes_read] = '\0';
		temp_buffer = ft_strjoin(*basin_buffer, buffer);
		if (!temp_buffer)
			return (free(buffer), NULL);
		free(*basin_buffer);
		*basin_buffer = temp_buffer;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free (buffer);
	return (*basin_buffer);
}

char	*extract_line(char *basin_buffer)
{
	char	*line;
	int		i;

	if (!basin_buffer)
		return (NULL);
	i = 0;
	while (basin_buffer[i] != '\n' && basin_buffer[i] != '\0')
		i++;
	line = ft_substr(basin_buffer, 0, i);
	if (!line)
		return (NULL);
	return (line);
}

char	*update_buffer(char **global_buffer, char *line)
{
	char	*temp;

	if (!*global_buffer || !line)
		return (NULL);
	temp = ft_strdup(*global_buffer + ft_strlen(line) + 1);
	free(*global_buffer);
	*global_buffer = temp;
	return (*global_buffer);
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
	global_buffer = reader(&global_buffer, buffer, fd);
	line = extract_line(global_buffer);
	global_buffer = update_buffer(&global_buffer, line);	
	if (!global_buffer)
		return (free(global_buffer), NULL);
	return (line);
}
