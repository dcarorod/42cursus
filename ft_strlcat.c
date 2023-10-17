/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:07:56 by dcaro-ro          #+#    #+#             */
/*   Updated: 2023/10/16 09:48:12 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	src_len;
	size_t	dst_len;

	j = 0;
	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	i = dst_len;
	if (size == 0 || size <= dst_len)
		return (size + src_len);
	while (src[j] != '\0' && (j < (size - dst_len - 1)))
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (src_len + dst_len);
}
/* strlcat() appends string src to the end of dst.
It will append at most dstsize - strlen(dst) - 1 characters.
It will then NUL-terminate, unless dstsize is 0
or the original dst string was longer than dstsize
(in practice this should not happen as it means that either dstsize
is incorrect or that dst is not a proper string).
*/
