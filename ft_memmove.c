/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:48:48 by dcaro-ro          #+#    #+#             */
/*   Updated: 2023/10/19 15:20:40 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
memmove() function copies len bytes from string src to string dst.
The two strings may overlap; the copy is always done in a non-destructive manner.
*/

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*tmp_dst;
	const char	*tmp_src;

	if (!src && !dst)
		return (NULL);
	if (len <= 0)
		return (dst);
	tmp_dst = (char *) dst;
	tmp_src = (char *) src;
	if (tmp_dst < tmp_src || tmp_dst >= (tmp_src + len))
	{
		while (len--)
			*tmp_dst++ = *tmp_src++;
	}
	else
	{
		tmp_dst += len;
		tmp_src += len;
		while (len--)
			*(--tmp_dst) = *(--tmp_src);
	}
	return (dst);
}
/*
#include <stdio.h>
#include <string.h>
int main(void)
{
	char str[] = "Hello, World!";
	printf("Original string: %s\n", str);

	//memmove(str + 7, str, 7); // Shifts "World!" to the right by 7 positions
	//printf("after memmove: %s\n", str);

	ft_memmove(str + 7, str, 7); // Shifts "World!" to the right by 7 positions
	printf("after ft_memmove: %s\n", str);
	return 0;
}
*/
