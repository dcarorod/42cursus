/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:17:03 by dcaro-ro          #+#    #+#             */
/*   Updated: 2023/10/23 15:17:11 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*dst;

	i = 0;
	dst = malloc(ft_strlen(s1) + 1);
	if (!dst)
		return (0);
	while (s1[i] != '\0')
	{
		dst[i] = s1[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
/*
#include <stdio.h>
int main(void)
{
	char str[] = "Stupid sexy Flanders";
	char *dup = ft_strdup(str);
	int x = ft_strlen(str);
	int y = ft_strlen(dup);

	printf("Original: %s - len: %i\n", str, x);
	printf("Dup: %s - len: %i\n", dup, y);
	return 0;
}
*/
