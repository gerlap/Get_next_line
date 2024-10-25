/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glapshin <glapshin@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 19:08:34 by glapshin          #+#    #+#             */
/*   Updated: 2024/10/25 18:27:28 by glapshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_list	*list = (NULL);
	char			*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	create_list(&list, fd);
	if (list == NULL)
		return NULL;
	next_line = get_line(list);
	return (next_line);
}
void create_list(t_list **list, int fd)
{
	int		bytes_read;
	char	*buffer;
	while (!find_nl(*list))
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (buffer == NULL)
			return ;
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if(!bytes_read)
	{
		free(buffer);
		return ;
	}
	buffer[bytes_read] = '\0';
	append(list, buffer);
	}
}
int find_nl(t_list *list)// check if node exists
{
	int	i;

	if (list == (NULL))
		return (0);// 0 will be used in condition in find_nl
	while (list)
	{
		i = 0;
		while(list->str_buffer[i] && i < BUFFER_SIZE)
		{
			if(list->str_buffer[i] == '\n')
				return (1);
			i++;
		}
		list = list->next;
	}
	return (0);
}
int main()
{
	printf("")
}


