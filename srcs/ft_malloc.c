/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 03:17:29 by yguaye            #+#    #+#             */
/*   Updated: 2018/06/19 04:50:59 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include "ft_malloc_impl.h"

static void				set_segment(struct s_segment *s, size_t size,
		unsigned int block_id, struct s_segment **lst)
{
	s->size = size;
	s->block_id = block_id;
	s->next = *lst;
	if (*lst)
		(*lst)->prev = s;
	*lst = s;
}

static int				get_next_block(t_memblock **block, size_t *id,
		t_meminfo *info)
{
	size_t				i;

	i = 0;
	while (i < MAX_BLOCKS)
	{
		if (info->blocks[i].type == EMPTY_BLOCK)
		{
			*block = &info->blocks[i];
			*id = i;
			if (i >= info->curr)
				++info->curr;
			return (1);
		}
	}
	return (0);
}

void					*ft_malloc(size_t size,
		t_meminfo *info)
{
	t_memblock			*block;
	size_t				id;

	if (size <= TINY_MAX_SIZE)
		return (NULL);
	else if (size <= SMALL_MAX_SIZE)
		return (NULL);
	else
	{
		if (!get_next_block(&block, &id, info))
			return (NULL);
		if ((block->pages = mmap(NULL, size, PROT_READ | PROT_WRITE,
						MAP_ANONYMOUS, -1, 0)) == MAP_FAILED)
			return (NULL);
		block->type = LARGE;
		block->size = size;
		set_segment((struct s_segment *)block->pages, size,
				id, &block->seg_lst);
		return (((char *)block->pages) + sizeof(struct s_segment));
	}
}
