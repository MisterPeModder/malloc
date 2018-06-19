/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 04:04:21 by yguaye            #+#    #+#             */
/*   Updated: 2018/06/19 04:48:21 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "ft_malloc_impl.h"

static void				check_addr(char *addr, t_meminfo *info)
{
	size_t				i;

	i = 0;
	while (i < info->curr)
	{
		if (addr >= (char *)info->blocks[i].pages &&
				addr < addr + info->blocks[i].size)
		{
			if (((struct s_segment *)addr)->block_id >= info->curr)
				break ;
			return ;
		}
		++i;
	}
	ft_putendl_fd("UNMAPED MEMORY !!", STDERR_FILENO);
	abort();
}

void					ft_free(void *ptr,
		t_meminfo *info)
{
	struct s_segment	*seg;

	if (ptr == NULL)
		return ;
	seg = (struct s_segment *)((char *)ptr) - sizeof(struct s_segment);
	check_addr((char *)seg, info);
	if (seg->prev)
		seg->prev->next = seg->next;
	if (seg->next)
		seg->next->prev = seg->prev;
	if (!seg->next && !seg->prev)
		info->blocks[seg->block_id].type = EMPTY_BLOCK;
}
