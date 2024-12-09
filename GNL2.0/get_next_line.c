/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glapshin <glapshin@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 20:40:17 by glapshin          #+#    #+#             */
/*   Updated: 2024/12/09 20:57:03 by glapshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *reader(int fd)
{
char	*buffer;
int		bytes_read;

buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
bytes_read = read(fd, buffer, BUFFER_SIZE);
	if(buffer == NULL)
		return ( NULL);
if (bytes_read <= 0)
	return (free (buffer),NULL);
return (buffer);
}
char *get_next_line(int fd)
{
	static char *global_buffer;
	char		*line;
	if (fd < 0 || BUFFER_SIZE <= 0 )
		return (NULL);
	if (!global_buffer)
	global_buffer = reader(fd);
	return (global_buffer);
}
