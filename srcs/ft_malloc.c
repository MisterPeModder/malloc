/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 03:44:52 by yguaye            #+#    #+#             */
/*   Updated: 2018/07/23 09:40:31 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/mman.h>
#include "libft.h"
#include "ft_malloc_impl.h"

static inline size_t	size_align(size_t size, size_t alignment)
{
	if (size % alignment != 0)
		return (alignment - size % alignment + size);
	return (size);
}

static t_mchunk			*make_first_chunk(t_mb_header *header)
{
	t_mchunk			*chunk;

	chunk = (t_mchunk *)((char *)header + size_align(
				sizeof(t_mb_header), 2 * sizeof(void *)));
	chunk->size = (size_t)((char *)header + header->size
			- (char *)&chunk->prev_empty);
	return (chunk);
}

/*
** make_block: Alloctes a new memory block using mmap() and adds it to the list.
**
** -list: the memory block list.
** -type: the type of the block to be created.
** -size: the size of the block if the type is MEMBLOCK_LARGE.
**        if not, this parameter will be ignored.
**
** the block size is computed to be a multiple a 2 * sizeof(void *) and
** aligned on page-size boundary
**
** returns: A pointer to the header of the allocated block.
*/

static t_mb_header		*make_block(t_mb_header **list, enum e_mb_type type,
		size_t size)
{
	t_mb_header			*header;

	if (type == MEMBLOCK_TINY)
		size = TINY_MAX_SIZE * TINY_ALLOC_NUM;
	else if (type == MEMBLOCK_SMALL)
		size = SMALL_MAX_SIZE * SMALL_ALLOC_NUM;
	size = size_align(size_align(size, 2 * sizeof(void *)),
			(size_t)getpagesize());
	if ((header = mmap(NULL, size, PROT_READ | PROT_WRITE,
					MAP_ANONYMOUS | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
		return (NULL);
	ft_bzero(header, sizeof(t_mb_header));
	header->prev = NULL;
	header->next = *list;
	header->size = size;
	header->type = type;
	header->empty_chunk = make_first_chunk(header);
	if (*list)
		(*list)->prev = header;
	else
		*list = header;
	header->hash_code = header_hash(header);
	return (header);
}

void					*ft_malloc(size_t size, t_mb_header **first)
{
	if (size > SMALL_MAX_SIZE)
		return (NULL);
	if (!*first)
		*first = make_block(first, MEMBLOCK_SMALL, 0);
	return (*first ? (*first)->empty_chunk : NULL);
}
