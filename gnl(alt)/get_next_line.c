/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glapshin <glapshin@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 19:08:34 by glapshin          #+#    #+#             */
/*   Updated: 2024/12/07 18:33:16 by glapshin         ###   ########.fr       */
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
		return (NULL);
	next_line = get_line(list);
	empty_list(&list);
	return (next_line);
}

void	create_list(t_list **list, int fd)

{
	int		bytes_read;
	char	*buffer;

	while (!find_nl(*list))
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (buffer == NULL)
			return ;
		bytes_read = read (fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			free (buffer);
			return ;
		}
		buffer[bytes_read] = '\0';
		append (list, buffer);
	}
}

int	find_nl(t_list *list)// check if node exists

{
	int	i;

	if (list == (NULL))
		return (0);
	while (list)
	{
		i = 0;
		while (list->str_buffer[i] && i < BUFFER_SIZE)
		{
			if (list->str_buffer[i] == '\n')
				return (1);
			i++;
		}
		list = list->next;
	}
	return (0);
}

void	append(t_list **list, char *buffer)
{
	t_list	*new_node;
	t_list	*last_node;

	if (list == NULL)
		return ;
	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
	{
		free(buffer);
		return ;
	}
	new_node->str_buffer = buffer;
	new_node->next = NULL;
	if (*list == NULL)
		*list = new_node;
	else
	{
		last_node = *list;
		while (last_node->next != NULL)
			last_node = last_node->next;
		last_node->next = new_node;
	}
}

void	empty_list(t_list **list)
{
	t_list	*current;
	t_list	*next_node;

	if (!list || !*list)
		return ;
	current = *list;
	while (current)
	{
		next_node = current->next;
		if (current->str_buffer)
			free (current->str_buffer);
		free (current);
		current = next_node;
	}
	*list = NULL;
}
char	*get_line(t_list *list)
{
	size_t	line_len;
	char	*next_line;
	t_list	*current;

	if (list == NULL)
		return (NULL);
	line_len = ft_strlen(list);
	next_line = malloc(line_len + 1);
	if (next_line == NULL)
		return (NULL);
	copy_str(list, next_line);
	return (next_line);
}
// int main()
// {
// 	printf("")
// }
