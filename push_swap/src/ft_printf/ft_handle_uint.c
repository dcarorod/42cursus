/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_uint.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 12:21:24 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/06/01 12:21:29 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/push_swap.h"

int	ft_handle_uint(unsigned int n)
{
	if (n >= 10)
		return (ft_handle_uint(n / 10) + ft_putchar(n % 10 + '0'));
	return (ft_putchar(n + '0'));
}
