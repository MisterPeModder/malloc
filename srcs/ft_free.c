/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 04:04:21 by yguaye            #+#    #+#             */
/*   Updated: 2018/06/19 19:31:33 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include "libft.h"
#include "ft_malloc_impl.h"

static void				check_seg_addr(char *addr, t_meminfo *info)
{
	if (search_seg_adrr(addr, info))
		return ;
	ft_putstr_fd("ft_malloc: *** error for object ", STDERR_FILENO);
	print_addr(addr, STDERR_FILENO);
	ft_putendl_fd(": pointer being freed was not allocated", STDERR_FILENO);
	abort();
}

void					ft_free(void *ptr,
		t_meminfo *info)
{
	struct s_segment	*seg;
	t_memblock			*block;

	if (ptr == NULL)
		return ;
	seg = (struct s_segment *)((char *)ptr - sizeof(struct s_segment));
	check_seg_addr((char *)seg, info);
	seg->empty = 1;
	block = &info->blocks[seg->block_id];
	if (--block->filled_segments_count == 0)
	{
		block->type = EMPTY_BLOCK;
		munmap(block->pages, block->size);
		block->pages = NULL;
	}
	else
		seg_merge(seg);
}
