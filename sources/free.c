/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 15:28:15 by dda-cunh          #+#    #+#             */
/*   Updated: 2025/10/27 12:39:40 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_malloc.h"

void	free(void *ptr)
{
	byte	*chunk_bytes;
	_size_t	*header;

	if (!ptr)
		return ;

	MALLOC_INIT();

	chunk_bytes = GET_BLOCK(ptr);
	header = GET_HEADER(chunk_bytes);
	if (!(IS_ALLOC(header)))
		return ;

	if (IS_FIXED(header))
	{
		CLR_ALLOC(header);
		if (BLOCK_SIZE(header) > TINY_BLOCK_SIZE)
			g_malloc_zones.small.free_blocks++;
		else
			g_malloc_zones.tiny.free_blocks++;
	}
	else
		munmap(chunk_bytes, get_aligned_size(BLOCK_SIZE(header)));
}
