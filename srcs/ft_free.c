/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 04:04:21 by yguaye            #+#    #+#             */
/*   Updated: 2018/06/19 16:16:23 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include "libft.h"
#include "ft_malloc_impl.h"

static int				search_seg_adrr(char *addr, t_meminfo *info)
{
	size_t				i;
	struct s_segment	*curr;

	i = 0;
	/*ft_putstr("[search_seg_adrr]: searching for address ");
	  print_addr(addr, 0);
	  ft_putchar('\n');*/
	while (i < info->curr)
	{
		/*ft_putstr("[search_seg_adrr]: boundary check in block #");
		  ft_putnbr((int)i);
		  ft_putstr(" in [");
		  print_addr(info->blocks[i].pages, 1);
		  ft_putstr(", ");
		  print_addr(((char *)info->blocks[i].pages) + info->blocks[i].size, 1);
		  ft_putendl("[");*/
		if (addr >= (char *)info->blocks[i].pages &&
				addr < ((char *)info->blocks[i].pages) + info->blocks[i].size)
		{
			/*ft_putendl("[search_seg_adrr]: searching for segment...");*/
			curr = info->blocks[i].seg_lst;
			while (curr)
			{
				if (curr == (void *)addr)
					return (info->blocks[i].type != EMPTY_BLOCK);
				curr = curr->next;
			}
			break ;
		}
		++i;
	}
	return (0);
}

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

	if (ptr == NULL)
		return ;
	/*ft_putendl("[ft_free]: freeing...");*/
	seg = (struct s_segment *)((char *)ptr - sizeof(struct s_segment));
	/*ft_putendl("[ft_free]: checking address...");*/
	check_seg_addr((char *)seg, info);
	/*ft_putendl("[ft_free]: removing link...");*/
	if (seg->prev)
		seg->prev->next = seg->next;
	if (seg->next)
		seg->next->prev = seg->prev;
	if (!seg->next && !seg->prev)
	{
		/*ft_putendl("[ft_free]: unmapping block...");*/
		info->blocks[seg->block_id].type = EMPTY_BLOCK;
		info->blocks[seg->block_id].seg_lst = NULL;
		munmap(info->blocks[seg->block_id].pages,
				info->blocks[seg->block_id].size);
	}
}
