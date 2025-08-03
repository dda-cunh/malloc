/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:09:44 by dda-cunh          #+#    #+#             */
/*   Updated: 2025/08/03 18:47:25 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_malloc.h"

void	*mmap_anon_aligned(_size_t size, int prot)
{
	_size_t aligned_size;
	_size_t pagesize;

	pagesize = sysconf(_SC_PAGESIZE);
	aligned_size = ((size + pagesize - 1) / pagesize) * pagesize;

	void *ptr = mmap(NULL, aligned_size, prot, MAP_ANON | MAP_PRIVATE, -1, 0);

	if (ptr == MAP_FAILED)
		return (NULL);

	return (ptr);
}	

_size_t	block_real_len(uint8_t *chunk_bytes)
{
	_size_t	*header;
	_size_t	size;

	header = GET_HEADER(chunk_bytes);
	if (IS_FIXED(header))
	{
		if (BLOCK_SIZE(header) > TINY_BLOCK_SIZE)
			return (SMALL_BLOCK_SIZE);
		return (TINY_BLOCK_SIZE);
	}

	return (BLOCK_SIZE(header) + HEADER_SIZE);
}
