/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:16:27 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/06/02 12:49:10 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0' && *s == '\0')
		return ((char *)s);
	return (NULL);
}
/*
#include <stdio.h>

int main(void)
{
	char str[] = "Stupid Sexy Flanders";
	char letter = 'F';
	char *result = ft_strchr(str, letter);

	if (result != NULL)
		printf("Character found: %c\n", *result);
	else
		printf("Character not found.\n");
	return 0;
}
*/
