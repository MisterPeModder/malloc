/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_impl.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 03:07:38 by yguaye            #+#    #+#             */
/*   Updated: 2018/06/19 17:44:37 by yguaye           ###   ########.fr       */
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

/*
** struct s_segment: This structure is prepended to each allocated memory.
**
** -size: the segment size (not including the s_segment struct itself).
** -block: which block this semgement is in.
** -prev: a pointer to the previous segment.
** -next: a pointer to the next segment.
*/
struct					s_segment
{
	size_t				size;
	size_t				block_id;
	struct s_segment	*next;
	struct s_segment	*prev;
};

/*
** t_memblock: A memory block. contains the memory pages.
**
** -type: its type.
** -size: the size in bytes of the total page memory.
** -pages: the memory pages returned by mmap().
** -seg_lst: a pointer to the first segment (DEPRECATED)
*/
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

/*
** t_meminfo: Contains the memory blocks and the current max block index.
**
** -curr: its value is: last_not_empty_block_index + 1
** -blocks: the memory blocks.
*/
typedef struct			s_meminfo
{
	size_t				curr;
	t_memblock			blocks[MAX_BLOCKS];
}						t_meminfo;

/*
** ft_free: The implentation function of free()
**
** -info: a (VALID) pointer to a meminfo structure.
*/
void					ft_free(void *ptr,
		t_meminfo *info);

/*
** ft_malloc: The implentation function of malloc()
**
** -info: a (VALID) pointer to a meminfo structure.
*/
void					*ft_malloc(size_t size,
		t_meminfo *info);

/*
** ft_realloc: The implentation function of realloc()
**
** -info: a (VALID) pointer to a meminfo structure.
*/
void					*ft_realloc(void *ptr, size_t size,
		t_meminfo *info);

/*
** ft_calloc: The implentation function of calloc()
**
** -info: a (VALID) pointer to a meminfo structure.
*/
void					*ft_calloc(size_t nelems, size_t size,
		t_meminfo *info);

/*
** ft_show_alloc_mem: Prints the memory blocks and segments.
**
** -info: a (VALID) pointer to a meminfo structure.
*/
void					ft_show_alloc_mem(t_meminfo *info);

/*
** print_addr: Prints the passed address using lowercase hexadecimal.
**
** -addr: the address to be printed.
** -fd: where this function should output.
*/
void					print_addr(const void *addr, int fd);

/*
** print_addr_maj: Prints the passed address using upperrcase hexadecimal.
**                 Always prints to standard output.
**
** -addr: the address to be printed.
*/
void					print_addr_maj(const void *addr);

/*
** align_size: Returns the next upper address aligned on page boundary.
**
** returns: a size_t >= (size + sizeof(struct s_segment))
*/
size_t					align_size(size_t size);

/*
** search_seg_adrr: Verifies if the passed address corresponnds to a valid
**                  segment address.
**
** returns: 1 if address valid, 0 if not.
*/
int						search_seg_adrr(char *addr, t_meminfo *info);

#endif
