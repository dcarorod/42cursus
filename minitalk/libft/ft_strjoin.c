/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:18:16 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/06/02 12:49:19 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft.h"

static char	*ft_strcat(char *dst, char *src)
{
	int	i;
	int	j;

	i = ft_strlen(dst);
	j = 0;
	while (src[j] != '\0')
		dst[i++] = src[j++];
	dst[i] = '\0';
	return (dst);
}

static char	*ft_strcpy(char *dst, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dst;

	dst = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!dst)
		return (NULL);
	ft_strcpy(dst, (char *)s1);
	ft_strcat(dst, (char *)s2);
	return (dst);
}
/*
#include <stdio.h>
int	main(void)
{
	char str1[] = "A la grande ";
	char str2[] = "le puse Cuca";
	char *strs = ft_strjoin(str1, str2);

	printf("%s", strs);
}
*/
