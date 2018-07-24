/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 06:54:32 by yguaye            #+#    #+#             */
/*   Updated: 2018/07/23 22:20:49 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "libft.h"
#include "ft_malloc_impl.h"

unsigned long			djb2_hash(const unsigned char *mem, size_t size)
{
	size_t				i;
	unsigned long		hash;

	i = 0;
	hash = 5381;
	while (i < size)
		hash = ((hash << 5) + hash) + mem[i++];
	return (hash);
}

unsigned long			header_hash(const t_mb_header *h)
{
	t_mb_header			cpy;

	ft_memcpy(&cpy, h, sizeof(t_mb_header));
	cpy.hash_code = 0;
	return (djb2_hash((const unsigned char *)&cpy, sizeof(t_mb_header)));
}

size_t					size_align(size_t size, size_t alignment)
{
	if (size % alignment != 0)
		return (alignment - size % alignment + size);
	return (size);
}

void					*ptr_align(void *src, size_t offset, size_t alignment)
{
	uintptr_t			ret;

	ret = (uintptr_t)((char *)src + offset);
	if (ret % alignment != 0)
		ret += (uintptr_t)(alignment - ret % alignment);
	return ((void *)ret);
}
