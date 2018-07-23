/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 05:43:29 by yguaye            #+#    #+#             */
/*   Updated: 2018/07/23 09:40:53 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "ft_malloc_impl.h"

void					ft_free(void *ptr, t_mb_header **first)
{
	t_mb_header			*curr;
	curr = *first;
	while (curr)
	{
		if (header_hash(curr) != curr->hash_code)
		{
			ft_putendl_fd("heap corruption detected: code 1", 2);
			abort();
		}
		if (ptr > (void *)curr && (char *)ptr < ((char *)curr + curr->size))
		{

			return ;
		}
		curr = curr->next;
	}
	ft_putendl_fd("pointer being freed was not allocated!", 2);
	abort();
}
