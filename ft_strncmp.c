/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:05:16 by dcaro-ro          #+#    #+#             */
/*   Updated: 2023/10/23 15:05:26 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	tmp1;
	unsigned char	tmp2;

	i = 0;
	while (i < n)
	{
		tmp1 = (unsigned char)s1[i];
		tmp2 = (unsigned char)s2[i];
		if (tmp1 != tmp2)
			return (tmp1 - tmp2);
		if (tmp1 == '\0' || tmp2 == '\0')
			break ;
		i++;
	}
	return (0);
}
