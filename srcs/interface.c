/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 03:06:40 by yguaye            #+#    #+#             */
/*   Updated: 2018/06/19 04:51:31 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include "ft_malloc_impl.h"

static t_meminfo		g_meminfo;

void					free(void *ptr)
{
	ft_free(ptr, &g_meminfo);
}

void					*malloc(size_t size)
{
	return (ft_malloc(size, &g_meminfo));
}

void					*realloc(void *ptr, size_t size)
{
	return (ft_realloc(ptr, size, &g_meminfo));
}

void					*calloc(size_t nelems, size_t size)
{
	return (ft_calloc(nelems, size, &g_meminfo));
}
