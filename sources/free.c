/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 15:28:15 by dda-cunh          #+#    #+#             */
/*   Updated: 2025/08/03 12:32:06 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_malloc.h"

extern malloc_zones	g_malloc_zones;

static void	free_from_fixed_zone(void *chunk_bytes, fixed_zone *zone)
{
	uint8_t	*zone_bytes;
	_size_t	header;

	if (!chunk_bytes || !zone)
		return ;

	zone_bytes = (uint8_t *)zone->start;

	for (_size_t i = 0; i < zone->block_count; i++)
	{
		if (chunk_bytes == zone_bytes)
		{
			FLIP_ALLOC(GET_HEADER(chunk_bytes));

			return ;
		}

		zone_bytes += zone->block_size;
	}
}

void	free(void *ptr)
{
	uint8_t	*chunk_bytes;
	_size_t	*header;
	_size_t	size;

	if (!ptr)
		return ;

	chunk_bytes = GET_BLOCK(ptr);
	header = GET_HEADER(chunk_bytes);
	if (!(IS_ALLOC(*header)))
		return ;

	size = BLOCK_SIZE(*header);
	if (IS_LARGE(size))
		munmap(chunk_bytes, size + HEADER_SIZE);
	else if (size > TINY_BLOCK_SIZE)
		free_from_fixed_zone(chunk_bytes, &g_malloc_zones.small);
	else
		free_from_fixed_zone(chunk_bytes, &g_malloc_zones.tiny);
}
