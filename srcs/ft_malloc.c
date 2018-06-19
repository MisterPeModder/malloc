/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 03:17:29 by yguaye            #+#    #+#             */
/*   Updated: 2018/06/19 19:43:21 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include "ft_malloc_impl.h"

#include "libft.h"
#include <stdio.h>

static void				set_segment(struct s_segment **s, size_t size,
		unsigned int block_id)
{
	(*s)->size = size;
	(*s)->block_id = block_id;
	(*s)->next = NULL;
	(*s)->prev = NULL;
	(*s)->empty = 0;
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
			(*block)->pages = NULL;
			if (i >= info->curr)
				++info->curr;
			return (1);
		}
		++i;
	}
	return (0);
}

static void				*ft_large_malloc(size_t block_size, size_t alloc_size,
		t_meminfo *info)
{
	t_memblock			*block;
	size_t				id;

	if (!get_next_block(&block, &id, info))
		return (NULL);
	if ((block->pages = mmap(NULL, block_size, PROT_READ | PROT_WRITE,
					MAP_ANONYMOUS | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
	{
		ft_putendl("[ft_malloc]: mmap failed!");
		return (NULL);
	}
	block->type = LARGE;
	block->size = block_size;
	block->filled_segments_count = 1;
	set_segment((struct s_segment **)&block->pages, block_size, id);
	seg_frag((struct s_segment *)block->pages, alloc_size);
	return (((char *)block->pages) + sizeof(struct s_segment));
}

void					*ft_malloc(size_t size, t_meminfo *info)
{

	if (size <= TINY_MAX_SIZE)
	{
		/*ft_putendl("[ft_malloc]: malloc type: TINY");*/
		return (NULL);
	}
	else if (size <= SMALL_MAX_SIZE)
	{
		/*ft_putendl("[ft_malloc]: malloc type: SMALL");*/
		return (NULL);
	}
	else
		return (ft_large_malloc(align_size(size), size, info));
}
