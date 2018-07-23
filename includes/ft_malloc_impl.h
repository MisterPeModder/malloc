/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_impl.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 03:07:38 by yguaye            #+#    #+#             */
/*   Updated: 2018/07/23 09:40:20 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_IMPL_H
# define FT_MALLOC_IMPL_H

# include <stddef.h>

# define MAX_BLOCKS 420

# define TINY_MAX_SIZE 64
# define TINY_ALLOC_NUM 100
# define SMALL_MAX_SIZE 1024
# define SMALL_ALLOC_NUM 100

# define MCHK_INUSE 1
# define MCHK_ALLOC 2

/*
** t_mchunk: defines a single memory allocation's data
**
** -prev_size: size of the previous chunk
** -size: the size of the current chuck, in bytes.
**        Since the size has to be >= to sizeof(void *), the first two bits
**        of this field can be set as follows:
**
** > MCHK_INUSE: if set, the 'prev_size' field holds data of the previous
**               chunk, not the size. It is always set for the first allocation
**               to prevent from accessing header data or unmapped data.
** > MCHK_ALLOC: always set when the chunk is not free.
**
** -next_empty: if this chunk is free, it is set the next free block location.
**              When there is no other free block, it is set to NULL.
** -prev_empty: if this chunk is free, it is set the previous free block loc.
**              When there is no other free block, it is set to NULL.
**
** When the chunk is in use, 'next_empty' and 'prev_empty'
** are part of user data.
*/
typedef struct			s_mchunk
{
	size_t				prev_size;
	size_t				size;
	struct s_mchunk		*prev_empty;
	struct s_mchunk		*next_empty;
}						t_mchunk;

enum					e_mb_type
{
	MEMBLOCK_TINY = 0,
	MEMBLOCK_SMALL,
	MEMBLOCK_LARGE
};

/*
** t_mb_header: this structure is located in the begining of each block.
*/
typedef struct			s_mb_header
{
	struct s_mb_header	*prev;
	struct s_mb_header	*next;
	t_mchunk			*empty_chunk;
	size_t				size;
	unsigned long		hash_code;
	enum e_mb_type		type;
}						t_mb_header;

void					ft_free(void *ptr, t_mb_header **first);

void					*ft_malloc(size_t size, t_mb_header **first);

unsigned long			djb2_hash(const unsigned char *mem, size_t size);

unsigned long			header_hash(const t_mb_header *h);

#define EXPORT __attribute__ ((visibility("default")))
#define EXPORT_VOID void EXPORT

#endif
