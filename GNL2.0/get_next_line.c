/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: georgiilapshin <georgiilapshin@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 20:40:17 by glapshin          #+#    #+#             */
/*   Updated: 2025/01/07 14:23:00 by georgiilaps      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *reader(char **basin_buffer, char *buffer, int fd)
{
char	*temp_buffer;
int		bytes_read;

bytes_read = 1;
while (bytes_read > 0)
{
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read == -1)
		return (free(buffer), NULL);
	buffer[bytes_read] = '\0';
	temp_buffer = *basin_buffer;
	*basin_buffer = ft_strjoin(temp_buffer, buffer);
	free(temp_buffer);
	if (ft_strchr(buffer, '\n'))
		break;
}	
free (buffer);
return (*basin_buffer);
}
char *extract_line (char *basin_buffer)
{
	char *line;
	int i;
	
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
char *get_next_line(int fd)
{
	static char	*global_buffer;
	char		*buffer;
	char		*line;
	if (fd < 0 || BUFFER_SIZE <= 0 )
		return (NULL);
	if (!global_buffer)
		global_buffer = ft_calloc(1, sizeof (char));
	if (!global_buffer)
		return (NULL);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
if (!buffer)
    return (NULL);
	global_buffer = reader(global_buffer, buffer, fd);
	line = extract_line(global_buffer);
	global_buffer = update_buffer(&global_buffer, line);
	return (line);
}
char *update_buffer(char **global_buffer, char *line)
{
    char *temp;

    if (!*global_buffer || !line)
        return (NULL);

    temp = ft_strdup(*global_buffer + ft_strlen(line));
    free(*global_buffer);
    *global_buffer = temp;
    return (*global_buffer);
}

