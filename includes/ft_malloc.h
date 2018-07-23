/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 20:04:40 by yguaye            #+#    #+#             */
/*   Updated: 2018/07/23 04:00:23 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

#include <stddef.h>

void					free(void *ptr);

void					*malloc(size_t size);

void					*realloc(void *ptr, size_t size);

void					*calloc(size_t nelems, size_t size);

void					show_alloc_mem(void);

#endif
