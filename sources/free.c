/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 15:28:15 by dda-cunh          #+#    #+#             */
/*   Updated: 2025/08/15 22:47:42 by dda-cunh         ###   ########.fr       */
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
		munmap(chunk_bytes, get_aligned_size(HEADER_SIZE + BLOCK_SIZE(header)));
}
