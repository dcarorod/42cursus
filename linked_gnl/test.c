/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 19:33:02 by dcaro-ro          #+#    #+#             */
/*   Updated: 2023/11/21 10:13:48 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

int	main(void)
{
	int		i;
	int		fd;
	int		count;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
	{
		printf("Error opening the file.\n");
		return (-1);
	}
	i = 0;
	count = 15;
	while (i < count)
	{
		line = get_next_line(fd);
		printf("Line %d: %s\n", i, line);
		free(line);
		i++;
	}
	close (fd);
	return (0);
}
