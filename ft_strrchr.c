/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:03:35 by dcaro-ro          #+#    #+#             */
/*   Updated: 2023/10/23 15:03:45 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*last;

	last = NULL;
	while (*s)
	{
		if (*s == (char)c)
			last = (char *)s;
		s++;
	}
	if ((char)c == '\0' && *s == '\0')
		last = (char *)s;
	return (last);
}
/* The strrchr() function returns a pointer to the
last occurrence of the character c in the string */
/*
#include <stdio.h>
int main(void)
{
	char str[] = "Hello, World!";
	char *result;

	char letter = 'd';
	result = ft_strrchr(str, letter);
	if (result != NULL)
	{
		printf("Last 'o' found at position: %ld\n", result - str);
	}
	else
		printf("'%c' not found in string.\n", letter);
	return 0;
}
*/
