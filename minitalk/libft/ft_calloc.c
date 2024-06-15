/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:42:48 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/06/02 12:46:43 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, (count * size));
	return (ptr);
}
/*
#include <stdio.h>

int main(void)
{
	size_t count = 5;
	size_t size = sizeof(int);
	int *arr = (int *)ft_calloc(count, size);

	if (arr != NULL)
	{
		// Check if memory is initialized to 0
		for (size_t i = 0; i < count; i++)
		{
			printf("arr[%zu] = %d\n", i, arr[i]);
		}
		// free allocated memory
		free(arr);
	}
	else
		printf("Memory allocation failed.\n");
	return 0;
}
*/
