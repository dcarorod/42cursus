/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:02:49 by dcaro-ro          #+#    #+#             */
/*   Updated: 2023/10/23 15:03:00 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		start;
	int		end;
	int		i;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	while (start < end && ft_strchr(set, s1[start]))
		start++;
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	if (start >= end)
		return (ft_strdup(""));
	str = (char *)malloc(end - start + 1);
	if (!str)
		return (NULL);
	i = -1;
	while (++i < end - start)
		str[i] = s1[start + i];
	str[end - start] = '\0';
	return (str);
}
/*
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
*/
