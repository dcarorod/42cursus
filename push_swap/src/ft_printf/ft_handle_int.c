/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 12:19:30 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/06/01 12:19:35 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/push_swap.h"

int	ft_handle_int(int n)
{
	unsigned int	nbr;
	int				len;

	len = 0;
	if (n < 0)
	{
		len += ft_putchar('-');
		nbr = -n;
	}
	else
		nbr = n;
	if (nbr >= 10)
	{
		len += ft_handle_int(nbr / 10);
		nbr %= 10;
	}
	len += ft_putchar(nbr + '0');
	return (len);
}
