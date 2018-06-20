/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 09:42:17 by yguaye            #+#    #+#             */
/*   Updated: 2018/06/20 22:09:07 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "ft_malloc_impl.h"

static void				realloc_check_addr(void *ptr, t_meminfo *info)
{
	if (!search_seg_adrr(ptr, info))
	{
		ft_putstr_fd("ft_malloc: *** error for object ", STDERR_FILENO);
		print_addr(ptr, STDERR_FILENO);
		ft_putendl_fd(": pointer being realloc'd was not allocated",
				STDERR_FILENO);
		abort();
	}
}

/*TODO WIP*/
EXPORT_VOID				*ft_realloc(void *ptr, size_t size,
		t_meminfo *info)
{
	struct s_segment	*seg;

	seg = (struct s_segment *)((char *)ptr - sizeof(struct s_segment));
	realloc_check_addr(seg, info);
	(void)size;
	return (NULL);
}
