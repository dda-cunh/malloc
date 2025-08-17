/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:09:44 by dda-cunh          #+#    #+#             */
/*   Updated: 2025/08/15 22:30:43 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_malloc.h"

_size_t	get_aligned_size(_size_t size)
{
	static _size_t pagesize;

	pagesize = sysconf(_SC_PAGESIZE);

	return (((size + pagesize - 1) / pagesize) * pagesize);
}

void	*get_fixed_zone_i(fixed_zone *zone, _size_t i)
{
	if (i < zone->block_count)
		return (zone->start + (i * (HEADER_SIZE + zone->block_size)));

	return (NULL);
}

void	*mmap_anon_aligned(_size_t size, int prot)
{
	_size_t aligned_size;

	aligned_size = get_aligned_size(size);

	void *ptr = mmap(NULL, aligned_size, prot, MAP_ANON | MAP_PRIVATE, -1, 0);

	if (ptr == MAP_FAILED)
		return (NULL);

	return (ptr);
}	
