/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:02:19 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/06/02 12:50:00 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substr;
	size_t			i;
	size_t			remaining_len;
	unsigned int	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	remaining_len = (size_t)(s_len - start);
	if (len > remaining_len)
		len = remaining_len;
	substr = malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}
/*
#include <stdio.h>
int	main(void)
{
	char const *str = "A la grande le puse Cuca.";
	unsigned int start = 12;
	size_t len = 12;

	printf("Original string: %s\n", str);

	char *substr = ft_substr(str, start, len);
	printf("Substring: %s\n", substr);
	return 0;
}
*/
