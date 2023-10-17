/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:43:08 by dcaro-ro          #+#    #+#             */
/*   Updated: 2023/10/17 10:04:42 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t		i;
	size_t		needle_len;
	const char	*substr;

	if (needle[0] == '\0')
		return ((char *)haystack);
	i = 0;
	needle_len = ft_strlen(needle);
	if (needle_len > len)
		return (NULL);
	while (i <= (len - needle_len))
	{
		substr = haystack + i;
		if (ft_strncmp(substr, needle, needle_len) == 0)
			return ((char *)substr);
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>
#include <string.h>

int main(void)
{
	char haystack[] = "Una aguja en un pajar";
	char needle[] = "aguja";
	size_t max_len = ft_strlen(haystack);

	printf("haystack: %s\n", haystack);
	printf("needle: %s\n", needle);

	char *result1 = ft_strnstr(haystack, needle, max_len);

	if (result1 != NULL)
		printf("ft_strnstr: needle found: %s\n", result1);
	else
		printf("ft_strnstr: needle not found in the haystack.\n");

	char *result2 = strnstr(haystack, needle, max_len);

	if (result2 != NULL)
		printf("strnstr: needle found: %s\n", result2);
	else
		printf("strnstr: needle not found in the haystack.\n");

	return 0;
}
*/
