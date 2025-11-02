/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:09:44 by dda-cunh          #+#    #+#             */
/*   Updated: 2025/11/02 13:52:22 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_malloc.h"

_size_t	get_aligned_size(_size_t size, byte is_fixed)
{
	static _size_t	pagesize;

	pagesize = sysconf(_SC_PAGESIZE);

	if (is_fixed)
		size += FOOTER_SIZE;	// Dynamic blocks (large allocs) don't have footers

	size += HEADER_SIZE;

	return (((size + pagesize - 1) / pagesize) * pagesize);
}

void	*fixed_zone_block_plus(void *block, fixed_zone *zone)
{
	_size_t	*header;
	_size_t	size;

	header = GET_HEADER(block);
	size = BLOCK_SIZE(header);

	RET_NULL_IF(((byte *)block + HEADER_SIZE + size + FOOTER_SIZE) 
				>= (byte *)zone->start + zone->size);

	return ((byte *)block + HEADER_SIZE + size + FOOTER_SIZE);
}

void	*fixed_zone_block_minus(void *block, fixed_zone *zone)
{
	_size_t	*prev_footer;
	_size_t	prev_size;

	prev_footer = GET_FOOTER_PREV(block, zone->start);
	RET_NULL_IF(!prev_footer);

	if ((byte *)prev_footer - prev_size - HEADER_SIZE < (byte *)zone->start)
        return NULL;

	return ((byte *)prev_footer - prev_size - HEADER_SIZE);
}

void	*mmap_anon_aligned(_size_t size, byte is_fixed)
{
	_size_t aligned_size;

	aligned_size = get_aligned_size(size, is_fixed);

	void *ptr = mmap(NULL, aligned_size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);

	if (ptr == MAP_FAILED)
		return (NULL);

	return (ptr);
}	
