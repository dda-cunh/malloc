/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 15:28:15 by dda-cunh          #+#    #+#             */
/*   Updated: 2025/11/02 13:50:56 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_malloc.h"

//TODO: Implement
static void	fixed_coalesce(void *freed, fixed_zone *zone)
{

}


void	free(void *ptr)
{
	byte	*chunk_bytes;
	_size_t	*header;
	_size_t	size;

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
			fixed_coalesce(chunk_bytes, &g_malloc_zones.small);
		else
			fixed_coalesce(chunk_bytes, &g_malloc_zones.tiny);
	}
	else
		munmap(chunk_bytes, get_aligned_size(BLOCK_SIZE(header), 0));
}
