/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:43:36 by dcaro-ro          #+#    #+#             */
/*   Updated: 2023/10/17 19:31:31 by dcaro-ro         ###   ########.fr       */
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
 // The strchr() function returns a pointer to
 // the first occurrence of the character c in the string s.
*/
