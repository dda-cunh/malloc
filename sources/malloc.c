/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:21:23 by dda-cunh          #+#    #+#             */
/*   Updated: 2025/11/02 14:30:37 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_malloc.h"
// TODO: REVIEW ALL LIB FILES FOR CONSISTENCY


// TODO: Implement logic to get a block from a fixed zone
static void	*get_fixed_zone_block(fixed_zone *zone, _size_t size)
{

	return (NULL);
}

static void	debug(_size_t size, void *ptr)
{
	static int	count = 0;

	if (!DEBUG || g_debug_fd == -1)
		return ;

	ft_putstr_fd("[libft_malloc] number ", g_debug_fd);
	ft_putnbr_fd(++count, g_debug_fd);
	ft_putstr_fd("\tAllocated ", g_debug_fd);
	ft_putnbr_fd(size, g_debug_fd);
	ft_putchar_fd('(', g_debug_fd);
	ft_putnbr_fd(get_aligned_size(size, 0) - HEADER_SIZE, g_debug_fd);
	ft_putchar_fd(')', g_debug_fd);
	ft_putstr_fd(" bytes\t at ", g_debug_fd);
	ft_putptr_fd(ptr, g_debug_fd);
	ft_putchar_fd('\n', g_debug_fd);
}

void	*malloc(size_t size)
{
	_size_t	*header;
	void	*ptr;

	MALLOC_INIT();

	if (size == 0 || INVALID_SIZE(size))
		return (NULL);


	ptr = NULL;
	if (size <= TINY_BLOCK_SIZE && g_malloc_zones.tiny.capacity
		>= get_aligned_size(size, 1))
		ptr = get_fixed_zone_block(&g_malloc_zones.tiny, size);
	else if (size <= SMALL_BLOCK_SIZE && g_malloc_zones.small.capacity
				> get_aligned_size(size, 1))
		ptr = get_fixed_zone_block(&g_malloc_zones.small, size);

	if (ptr == NULL)
	{
		ptr = mmap_anon_aligned(size, 0);
		if (ptr == NULL)
			return (NULL);

		header = GET_HEADER(ptr);
		*header = MAKE_HEADER(size, 0, 1);
	}

	if (DEBUG)
		debug(size, ptr);

	return ((byte *)ptr + HEADER_SIZE);
}
