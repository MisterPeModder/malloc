/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_impl.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 03:07:38 by yguaye            #+#    #+#             */
/*   Updated: 2018/06/19 15:37:04 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_IMPL_H
# define FT_MALLOC_IMPL_H

# include <stddef.h>

# define MAX_BLOCKS 420

# define TINY_MAX_SIZE 2
# define TINY_ALLOC_NUM 100
# define SMALL_MAX_SIZE 3
# define TINY_ALLOC_NUM 100
# define SMALL_ALLOC_NUM 100

struct					s_segment
{
	size_t				size;
	size_t				block_id;
	struct s_segment	*next;
	struct s_segment	*prev;
};

typedef struct			s_memblock
{
	enum
	{
		EMPTY_BLOCK,
		TINY,
		SMALL,
		LARGE
	}					type;
	size_t				size;
	void				*pages;
	struct s_segment	*seg_lst;
}						t_memblock;

typedef struct			s_meminfo
{
	size_t				curr;
	t_memblock			blocks[MAX_BLOCKS];
}						t_meminfo;

void					ft_free(void *ptr,
		t_meminfo *info);

void					*ft_malloc(size_t size,
		t_meminfo *info);

void					*ft_realloc(void *ptr, size_t size,
		t_meminfo *info);

void					*ft_calloc(size_t nelems, size_t size,
		t_meminfo *info);

void					ft_show_alloc_mem(t_meminfo *info);

void					print_addr(const void *addr, int fd);

void					print_addr_maj(const void *addr);

size_t					align_size(size_t size);

#endif
