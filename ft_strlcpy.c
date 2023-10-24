/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:22:09 by dcaro-ro          #+#    #+#             */
/*   Updated: 2023/10/23 15:22:27 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize > 0)
	{
		while (src[i] != '\0' && i < dstsize - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}
/*
#include <stdio.h>
#include <string.h>
int main(void)
{
	char src[] = "abcd123";
	size_t dsize = 5;
	char dst[20];
	char str[20];

	size_t x = ft_strlcpy(dst, src, dsize);
	size_t y = strlcpy(str, src, dsize);

	printf("Source: %s\n", src);
	printf("dst: %s\n", dst);
	printf("len mystrlcpy: %zu\n\n", x);
	printf("str: %s\n", str);
	printf("Len original: %zu\n", y);

	return 0;
}
*/
