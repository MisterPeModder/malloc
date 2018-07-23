/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 06:54:32 by yguaye            #+#    #+#             */
/*   Updated: 2018/07/23 09:39:47 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
