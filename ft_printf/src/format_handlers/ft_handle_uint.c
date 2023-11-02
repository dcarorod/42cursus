/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_uint.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 10:03:40 by dcaro-ro          #+#    #+#             */
/*   Updated: 2023/11/01 10:44:34 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

int	ft_handle_uint(unsigned int n)
{
	if (n >= 10)
		return (ft_handle_uint(n / 10) + ft_putchar(n % 10 + '0'));
	return (ft_putchar(n + '0'));
}
