/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 09:53:11 by dcaro-ro          #+#    #+#             */
/*   Updated: 2023/10/17 10:03:53 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_intlen(int n)
{
	int	len;

	len = !n;
	while (n)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		len;
	int		is_neg;
	char	*str;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	is_neg = n < 0;
	len = ft_intlen(n) + is_neg;
	str = malloc(sizeof(char) * (len + 1));
	if (n == 0)
		str[0] = '0';
	if (is_neg)
	{
		n = -n;
		str[0] = '-';
	}
	str[len] = '\0';
	while (n)
	{
		str[--len] = n % 10 + '0';
		n /= 10;
	}
	return (str);
}
/*
#include <stdio.h>
int main(void)
{
	int x = -2147483648;
	int neg = -259860;
	int pos = 2486910;

	printf("INT_MIN: %i\n", x);
	printf("String: %s\n\n", ft_itoa(x));

	printf("Negative: %i\n", neg);
	printf("String: %s\n\n", ft_itoa(neg));

	printf("Positive: %i\n", pos);
	printf("String: %s\n", ft_itoa(pos));

	return 0;
}
*/
