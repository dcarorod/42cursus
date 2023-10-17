/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:09:28 by dcaro-ro          #+#    #+#             */
/*   Updated: 2023/10/17 14:16:46 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isinset(char c, char const *set)
{
	int	i;

	i =0;
	while (set[i] != '\0')
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	start;
	size_t	end;
	int		trimmed_len;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	while (start <= end && ft_isinset(s1[start], set))
		start++;
	while (end >= start && ft_isinset(s1[end], set))
		end--;
	trimmed_len = end - start;
	if (trimmed_len <= 0)
		return (ft_strdup(""));
	str = malloc(sizeof(char) * (trimmed_len + 1));
	if (!str)
		return (NULL);
	str = ft_substr(s1, start, trimmed_len);
	return (str);
}

#include <stdio.h>
int main(void)
{
	const char *originalStr = "123abcd123efgh123";
	const char *set = "123";

	char *trimmedStr = ft_strtrim(originalStr, set);

	if (!trimmedStr)
	{
		printf("Memory allocation failed.\n");
		return 1;
	}
	printf("Original string: %s\n", originalStr);
	printf("Trimmed string: %s\n", trimmedStr);

	free(trimmedStr);
	return 0;
}
