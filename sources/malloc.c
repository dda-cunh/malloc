/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:21:23 by dda-cunh          #+#    #+#             */
/*   Updated: 2025/08/17 13:48:00 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_malloc.h"
#include <unistd.h>


static void	*get_fixed_zone_block(fixed_zone *zone, _size_t size)
{
	_size_t	*header;

	for (_size_t i = 0; i < zone->block_count; i++)
	{
		header = GET_HEADER(get_fixed_zone_i(zone, i));
		if (!IS_ALLOC(header))
		{
			*header = MAKE_HEADER(size, 1, 1);
			zone->free_blocks--;
			return (header);
		}
	}

	return (NULL);
}

static void		debug(_size_t size, void *ptr)
{
	static int	count = 0;

	if (!DEBUG || g_debug_fd == -1)
		return ;

	ft_putstr_fd("[libft_malloc] number ", g_debug_fd);
	ft_putnbr_fd(++count, g_debug_fd);
	ft_putstr_fd("\tAllocated ", g_debug_fd);
	ft_putnbr_fd(size, g_debug_fd);
	ft_putchar_fd('(', g_debug_fd);
	ft_putnbr_fd(get_aligned_size(size), g_debug_fd);
	ft_putchar_fd(')', g_debug_fd);
	ft_putstr_fd(" bytes\t at ", g_debug_fd);
	ft_putptr_fd(ptr, g_debug_fd);
	ft_putchar_fd('\n', g_debug_fd);
}

void		*malloc(size_t size)
{
	_size_t		*header;
	void		*ptr;

	MALLOC_INIT();

	ptr = NULL;
	if (size <= TINY_BLOCK_SIZE && g_malloc_zones.tiny.free_blocks > 0)
		ptr = get_fixed_zone_block(&g_malloc_zones.tiny, size);
	else if (size <= SMALL_BLOCK_SIZE && g_malloc_zones.small.free_blocks > 0)
		ptr = get_fixed_zone_block(&g_malloc_zones.small, size);

	if (ptr == NULL)
	{
		ptr = mmap_anon_aligned(HEADER_SIZE + size, PROT_READ | PROT_WRITE);
		if (ptr == NULL)
			return (NULL);

		header = GET_HEADER(ptr);
		*header = MAKE_HEADER(size, 0, 1);
	}

	if (DEBUG)
		debug(size, ptr);

	return ((byte *)ptr + HEADER_SIZE);
}
