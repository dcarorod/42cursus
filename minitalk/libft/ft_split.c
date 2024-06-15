/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:14:40 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/06/02 12:49:06 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft.h"

static size_t	ft_count_words(char const *str, char sep)
{
	size_t	wc;
	int		in_word;

	if (!str)
		return (0);
	wc = 0;
	in_word = 0;
	while (*str)
	{
		if (*str == sep)
		{
			if (in_word)
				in_word = 0;
		}
		else if (!in_word)
		{
			wc++;
			in_word = 1;
		}
		str++;
	}
	return (wc);
}

static size_t	ft_wordlen(char const *str, char sep)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != sep)
		i++;
	return (i);
}

/* The strndup() function copies at most n bytes.
If s is longer than n, only n bytes are copied,
and a terminating null byte ('\0') is added */

char	*ft_strndup(const char *s, size_t n)
{
	size_t	i;
	size_t	len;
	char	*str;

	if (!s || n <= 0)
		return (NULL);
	len = ft_strlen(s);
	if (n > len)
		n = len;
	str = malloc(sizeof(char) * (n + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < n)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

/*
returns an array
of strings obtained by splitting ’s’ using the
character ’c’ as a delimiter. The array must end
with a NULL pointer
*/

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	char	**strs;

	strs = malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
	if (!strs || !s)
		return (NULL);
	i = -1;
	j = -1;
	while (s[++i])
	{
		if ((s[i] != c) && (i == 0 || s[i - 1] == c))
		{
			strs[++j] = ft_strndup(s + i, ft_wordlen(s + i, c));
			if (strs[j] == NULL)
			{
				while (--j >= 0)
					free(strs[j]);
				free(strs);
				return (NULL);
			}
		}
	}
	strs[++j] = NULL;
	return (strs);
}
/*
#include <stdio.h>
int main(void) {
	char *input_string = "This,is,a,sample,string";
	char delimiter = ',';
	int wc = ft_count_words(input_string, delimiter);

	char **result = ft_split(input_string, delimiter);

	if (result == NULL)
	{
		printf("Memory allocation failed. Unable to split the string.\n");
		return 1;
	}

	// Iterate through the result array and print the split words
	for (int i = 0; i <= wc; i++)
	{
		printf("Word %d: %s\n", i + 1, result[i]);
		free(result[i]);
	}

	free(result);
	return 0;
}
*/
