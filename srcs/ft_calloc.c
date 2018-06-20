/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 07:52:55 by yguaye            #+#    #+#             */
/*   Updated: 2018/06/20 22:08:29 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc_impl.h"

EXPORT_VOID				*ft_calloc(size_t nelems, size_t size,
		t_meminfo *info)
{
	unsigned char		*mem;
	size_t				i;

	if ((mem = (unsigned char *)ft_malloc(nelems * size, info)))
	{
		i = 0;
		while (i < size)
			mem[i] = 0;
	}
	return ((void *)mem);
}
