/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:21:23 by dda-cunh          #+#    #+#             */
/*   Updated: 2025/08/03 19:01:55 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_malloc.h"

//PAGE SIZE sysconf(_SC_PAGESIZE)

static void	*get_fixed_zone_block(fixed_zone *zone)
{
	//Loop trough blocks in zone and return first free

	return (NULL);
}

void		*malloc(size_t size)
{
	void	*ptr;
	_size_t	*header;

	MALLOC_INIT();

	ptr = NULL;
	if (size <= TINY_BLOCK_SIZE && g_malloc_zones.tiny.free_blocks > 0)
		ptr = get_fixed_zone_block(&g_malloc_zones.tiny);
	else if (size <= SMALL_BLOCK_SIZE && g_malloc_zones.small.free_blocks > 0)
		ptr = get_fixed_zone_block(&g_malloc_zones.small);

	if (ptr == NULL)
		ptr = mmap_anon_aligned(size, PROT_READ | PROT_WRITE);

	if (ptr == MAP_FAILED)
		return (NULL);

	header = GET_HEADER(ptr);
	*header = size;
	*header <<= SIZE_SHIFT;
	FLIP_ALLOC(header);

	return ((unsigned char *)ptr + HEADER_SIZE);
}
