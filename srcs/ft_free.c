/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 05:43:29 by yguaye            #+#    #+#             */
/*   Updated: 2018/07/24 05:25:04 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "ft_malloc_impl.h"

/*
** get_chunk_overhead: Returns the overhead address of a given (allocated)
** pointer in a portable way.
*/



static inline int		check_header_ptr(t_mb_header *curr)
{
	if (header_hash(curr) != curr->hash_code)
	{
		ft_putendl_fd("Heap corruption: block header was modified", 2);
		abort();
		return (0);
	}
	return (1);
}

static inline int		ptr_in_bounds(void *ptr, t_mb_header *curr, int ncheck)
{
	return ((ncheck && !ptr)
			|| (ptr >= ptr_align(curr, sizeof(t_mb_header), 2 * sizeof(void *))
				&& ptr <= (char *)curr + curr->size - sizeof(t_mchunk)));
}

static int				check_chunk_ptr(char *ptr, t_mb_header *curr,
		t_mchunk **chunk)
{
	const t_mchunk		t;
	ptrdiff_t			offset;
	const char			*msg;

	offset = (char *)&t.prev_empty - (char *)&t.prev_size;
	if (!ptr_in_bounds((*chunk = (t_mchunk *)(ptr - offset)), curr, 0))
		msg = "pointer being freed was not allocated!";
	else if (!((*chunk)->size & MCHK_ALLOC))
		msg = "pointer being freed was not allocated!";
	else if (ptr + ((*chunk)->size & ~MCHK_SMASK) > curr + curr->size)
		msg = "Heap corruption: invalid allocation size";
	else if (!((*chunk)->size & MCHK_INUSE)
			&& !ptr_in_bounds((char *)*chunk - (*chunk)->prev_size, curr, 0))
		msg = "Heap corruption: invalid previous chunk size";
	else
		return (1);
	ft_putendl_fd(msg, 2);
	abort();
	return (0);
}

void					ft_free(void *ptr, t_mb_header **first)
{
	t_mb_header			*curr;
	t_mchunk			*chunk;

	curr = *first;
	if ((uintptr_t)ptr % (2 * sizeof(void *)))
	{
		ft_putendl_fd("pointer being freed was not allocated!", 2);
		abort();
		return ;
	}
	while (curr)
	{
		if (!check_header_ptr(curr))
			return ;
		if (ptr >= curr && ptr < (char *)curr + curr->size)
		{
			if (!check_chunk_ptr(ptr, curr, &chunk))
				return ;
			return ;
		}
		curr = curr->next;
	}
	ft_putendl_fd("pointer being freed was not allocated!", 2);
	abort();
}
