/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:14:40 by dcaro-ro          #+#    #+#             */
/*   Updated: 2023/10/24 19:53:22 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

static char	*ft_strndup(const char *s, size_t n)
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
