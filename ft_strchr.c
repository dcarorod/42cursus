/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:16:27 by dcaro-ro          #+#    #+#             */
/*   Updated: 2023/10/23 15:16:38 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
