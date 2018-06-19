/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 17:46:07 by yguaye            #+#    #+#             */
/*   Updated: 2018/06/19 19:46:07 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc_impl.h"

int						seg_frag(struct s_segment *s, size_t size)
{
	struct s_segment	*s2;
	size_t				full_size;

	full_size = size + sizeof(struct s_segment);
	if (size > s->size - sizeof(struct s_segment))
		return (0);
	s2 = (struct s_segment *)(((char *)s) + full_size);
	s2->size = s->size - full_size;
	s->size = size;
	s2->block_id = s->block_id;
	s2->next = s->next;
	if (s2->next)
		s2->next->prev = s2;
	s->next = s2;
	s2->prev = s;
	s2->empty = 1;
	return (1);
}

void					seg_merge(struct s_segment *s2)
{
	struct s_segment	*s1;
	struct s_segment	*s3;

	s1 = (s2->prev && s2->prev->empty) ? s2->prev : s2;
	s3 = (s2->next && s2->next->empty) ? s2->next : s2;
	if (s2 == s1 && s2 == s3)
		return ;
	if (s3->next)
		s3->next->prev = s1;
	s1->next = s3->next;
	if (s1 != s2)
		s2->size += s1->size;
	if (s2 != s3)
		s2->size += s3->size;
}
