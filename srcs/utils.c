/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 10:32:12 by yguaye            #+#    #+#             */
/*   Updated: 2018/06/19 16:05:13 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "ft_malloc_impl.h"

static void				print_hex(unsigned long addr, int fd, int maj)
{
	if (addr < 10)
		ft_putchar_fd(addr + '0', fd);
	else if (addr < 16)
		ft_putchar_fd(addr + (maj ? 'A' : 'a') - 10, fd);
	else
	{
		print_hex(addr / 16, fd, maj);
		print_hex(addr % 16, fd, maj);
	}
}

void					print_addr(const void *addr, int fd)
{
	ft_putstr_fd("0x", fd);
	print_hex((unsigned long)addr, fd, 0);
}

void					print_addr_maj(const void *addr)
{
	ft_putstr_fd("0x", STDOUT_FILENO);
	print_hex((unsigned long)addr, STDOUT_FILENO, 1);
}

size_t					align_size(size_t size)
{
	size_t				page_size;

	page_size = (size_t)getpagesize();
	size += sizeof(struct s_segment);
	return (size - size % page_size + page_size);
}
