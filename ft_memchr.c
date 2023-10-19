/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:40:51 by dcaro-ro          #+#    #+#             */
/*   Updated: 2023/10/19 12:04:57 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
The  memchr() function scans the initial n bytes
of the memory area pointed to by s for the first instance of c.
Both c and the bytes of the memory area pointed
to by s are interpreted as unsigned char.

The memchr function returns a pointer to the located character,
or a null pointer if the character does not occur in the object.
*/

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *)s;
	while (i < n)
	{
		if (str[i] == (unsigned char)c)
			return (str + i);
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>
int main() {
	char str[] = "This is a test string.";
	char x = 'a';
	size_t search_len = ft_strlen(str);
	void *res = ft_memchr(str, x, search_len);
	if (res != NULL) {
		printf("Found '%c' at pos %ld: %s\n", x, (char *)res - str, (char *)res);
	} else {
		printf("'%c' not found in the string.\n", x);
	}
	return 0;
}
*/
