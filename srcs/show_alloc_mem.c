/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 15:26:49 by yguaye            #+#    #+#             */
/*   Updated: 2018/06/19 19:34:46 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "ft_malloc_impl.h"

static void				print_size_t(size_t v)
{
	if (v < 10)
		ft_putchar(v + '0');
	else
	{
		print_size_t(v / 10);
		print_size_t(v % 10);
	}
}

static void				show_alloc_segments(t_memblock *block, size_t *total)
{
	struct s_segment	*curr;
	char				*addr;

	curr = (struct s_segment *)block->pages;
	while (curr)
	{
		addr = ((char *)curr) + sizeof(struct s_segment);
		if (curr->empty)
		{
			curr = curr->next;
			continue ;
		}
		print_addr_maj(addr);
		ft_putstr(" - ");
		print_addr_maj(addr + curr->size);
		ft_putstr(" : ");
		print_size_t(curr->size);
		ft_putendl(" octets");
		*total += curr->size;
		curr = curr->next;
	}
}

void					ft_show_alloc_mem(t_meminfo *info)
{
	size_t				i;
	size_t				total;

	i = 0;
	total = 0;
	while (i < MAX_BLOCKS)
	{
		if (info->blocks[i].type != EMPTY_BLOCK)
		{
			if (info->blocks[i].type == TINY)
				ft_putstr("TINY");
			else
				ft_putstr(info->blocks[i].type == SMALL ? "SMALL" : "LARGE");
			ft_putstr(" : ");
			print_addr_maj(info->blocks[i].pages);
			ft_putchar('\n');
			show_alloc_segments(&info->blocks[i], &total);
		}
		++i;
	}
	ft_putstr("Total : ");
	print_size_t(total);
	ft_putendl(" octets");
}
