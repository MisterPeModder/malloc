/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 07:52:55 by yguaye            #+#    #+#             */
/*   Updated: 2018/06/19 09:39:21 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc_impl.h"

void					*ft_calloc(size_t nelems, size_t size,
		t_meminfo *info)
{
	return (ft_malloc(nelems * size, info));
}
