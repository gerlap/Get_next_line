/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnltest.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glapshin <glapshin@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 18:07:16 by glapshin          #+#    #+#             */
/*   Updated: 2024/10/16 20:45:12 by glapshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"
// int	main()
// {
// 	int		fd;
// 	char	buf[256];
// 	int		chars_read;

// 	fd = open("file.txt", O_RDONLY);
// 	while ((chars_read = read(fd, buf, 15)))
// 	{
// 		buf[chars_read] = '\0';
// 		printf("buf-> %s\n", buf);
// 	}
// 	// printf("%d\n", fd);
// 	// dup2(fd, 1);
// 	// write(1, "hi", 3);
// 	return (0);
// }
/*
 * Polish linked list for next call
*/
int main()
{
	int		fd;
	char	*line;
	int		lines;

	lines = 1;
	fd = open("file.txt", O_RDONLY);

	while((line = get_next_line(fd)))
		printf("%d->%s\n", lines++, line);
}

