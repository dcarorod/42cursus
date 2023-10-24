/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:08:01 by dcaro-ro          #+#    #+#             */
/*   Updated: 2023/10/24 19:54:49 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*buffer1;
	const unsigned char	*buffer2;

	i = 0;
	buffer1 = (const unsigned char *)s1;
	buffer2 = (const unsigned char *)s2;
	while (i < n)
	{
		if (buffer1[i] != buffer2[i])
			return (buffer1[i] - buffer2[i]);
		i++;
	}
	return (0);
}
/* declare pointers for byte-wise comparison, iterate through the memory
	blocks up to n bytes, return the difference if a value is found or
	0 if no differences are found after n bytes*/
