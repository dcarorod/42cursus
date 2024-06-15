/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:04:22 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/06/02 12:49:48 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft.h"

/*
The strnstr() function locates the first occurrence of
the null-terminated string needle in the string haystack,
where not more than len characters are searched.
Characters that appear after a `\0' character are not searched.
Since the strnstr() function is a FreeBSD specific API, it
should only be used when portability is not a concern.
*/

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (needle[0] == '\0')
		return ((char *)haystack);
	i = 0;
	while (haystack[i] != '\0' && (i < len))
	{
		j = 0;
		while (haystack[i + j] == needle[j] && haystack[i + j] && (i + j) < len)
		{
			j++;
			if (needle[j] == '\0')
				return ((char *)haystack + i);
		}
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
