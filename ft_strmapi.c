/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:53:25 by dcaro-ro          #+#    #+#             */
/*   Updated: 2023/10/19 12:03:23 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	unsigned int	len;
	char			*str;

	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
/*
// Example function to transform characters
char myFunction(unsigned int index, char character)
{
	(void) index;
	// convert lowercase characters to uppercase
	if (character >= 'a' && character <= 'z')
		return character - 32;
	else
		return character;
}

#include <stdio.h>
int main(void)
{
	const char *inputString = "Hello, World!";
	char *result = ft_strmapi(inputString, myFunction);

	if (result)
	{
		printf("Original string: %s\n", inputString);
		printf("Transformed string: %s\n", result);

		free(result);
	}
	else
		printf("Memory allocation failed or invalid input.\n");

	return 0;
}
*/
