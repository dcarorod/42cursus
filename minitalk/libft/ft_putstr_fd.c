/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:13:31 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/06/02 12:48:51 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	while (*s)
		write(fd, s++, 1);
}
/*
#include <stdio.h>
int	main(void)
{
	int fd = 1;
	char	str[] = "A la grande le puse Cuca\n";
	ft_putstr_fd(str, fd);
}
*/
