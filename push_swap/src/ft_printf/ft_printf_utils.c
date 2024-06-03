/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 12:22:10 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/06/01 12:22:14 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/push_swap.h"

int	ft_putchar(int c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(const char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len += ft_putchar(str[len]);
	return (len);
}

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

int	ft_isformatspecifier(const char f)
{
	return (f == 'c' || f == 's' || f == 'p' || f == 'd' || f == 'i'
		|| f == 'u' || f == 'x' || f == 'X' || f == '%');
}
