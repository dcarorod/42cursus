/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoav1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:44:07 by dcaro-ro          #+#    #+#             */
/*   Updated: 2023/10/16 09:55:51 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_intlen(int num)
{
	int len;

	len = 0;
	if (num <= 0)
		len++;
	while (num)
	{
		len++;
		num /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		num;
	int		len;
	char	*str;

	num = n;
	len = ft_intlen(num);
	if (n == -2147483648)
		return (ft_strdup("2147483648"));
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	if (num == 0)
		return (ft_strdup("0"));
	if (num < 0)
	{
		str[0] = '-';
		num = -num;
	}
	while (num)
	{
		str[--len] = num % 10 + '0';
		num /= 10;
	}
	return (str);
}
/*
#include <stdio.h>
int main(void)
{
	int x = -+25;
	//char zero[] = "0";

	char *str = ft_itoa(x);
	printf("int: %i\n", x);
	printf("string: %s\n", str);
	printf("length of str: %i\n", ft_strlen(str));
	//printf("sizeof zero: %zu\n", sizeof(zero));
}
*/
