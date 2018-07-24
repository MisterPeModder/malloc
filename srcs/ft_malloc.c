/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 03:44:52 by yguaye            #+#    #+#             */
/*   Updated: 2018/07/24 05:59:36 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include "libft.h"
#include "ft_malloc_impl.h"

static t_mchunk			*make_first_chunk(t_mb_header *header)
{
	t_mchunk			*chunk;

	chunk = ptr_align(header, sizeof(t_mb_header), 2 * sizeof(void *));
	chunk->size = (size_t)((char *)header + header->size
			- (char *)&chunk->prev_empty) | MCHK_INUSE;
	chunk->prev_empty = NULL;
	chunk->next_empty = NULL;
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
		size = size_align(TINY_MAX_SIZE, 2 * sizeof(void *)) * TINY_ALLOC_NUM;
	else if (type == MEMBLOCK_SMALL)
		size = size_align(SMALL_MAX_SIZE, 2 * sizeof(void *)) * SMALL_ALLOC_NUM;
	size = size_align(size, (size_t)getpagesize());
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

static void				release_block(t_mb_header *curr, t_mb_header **list)
{
	if (curr->prev)
		curr->prev->next = curr->next;
	if (curr->next)
		curr->next->prev = curr->prev;
	if (*list == curr)
		*list = curr->prev ? curr->prev : curr->next;
	munmap(curr, curr->size);
}

static t_mb_header		*find_or_create_block(size_t size, t_mb_header **list)
{
	enum e_mb_type		type;
	t_mb_header			*curr;

	if (size > SMALL_MAX_SIZE)
		type = MEMBLOCK_LARGE;
	else
		type = size > TINY_MAX_SIZE ? MEMBLOCK_SMALL : MEMBLOCK_LARGE;
	curr = *list;
	while (curr)
	{
		if (header_hash(curr) != curr->hash_code)
		{
			ft_putendl_fd("Malloc: heap corruption", 2);
			abort();
		}
		if (type == curr->type && size <= curr->empty_chunk->size)
			return (curr);
		curr = curr->next;
	}
	return (make_block(list, type, size));
}

void					*ft_malloc(size_t size, t_mb_header **list)
{
	t_mb_header			*block;

	if (!(block = find_or_create_block(size, list)))
		return (NULL);
	release_block(block, list);
	return (NULL);
}
