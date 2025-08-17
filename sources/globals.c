/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 11:30:34 by dda-cunh          #+#    #+#             */
/*   Updated: 2025/08/17 13:49:24 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_malloc.h"
#include <fcntl.h>

malloc_zones	g_malloc_zones = {
									{
										NULL,
										TINY_BLOCK_SIZE,
										TINY_BLOCKS,
										TINY_BLOCKS
									},
									{
										NULL,
										SMALL_BLOCK_SIZE,
										SMALL_BLOCKS,
										SMALL_BLOCKS
									}
								};

int	g_debug_fd = -1;


static void	malloc_global_init(void)
{
	_size_t	*header;

	g_malloc_zones.tiny.start = mmap_anon_aligned(
			g_malloc_zones.tiny.block_count *
				(g_malloc_zones.tiny.block_size + HEADER_SIZE),
			PROT_READ | PROT_WRITE);

	for (_size_t i = 0; i < g_malloc_zones.tiny.block_count; i++)
	{
		header = GET_HEADER(get_fixed_zone_i(g_malloc_zones.tiny.start, i));
		if (!header)
			continue ;

		*header = MAKE_HEADER(0, 1, 0);
		g_malloc_zones.tiny.free_blocks--;
	}

	g_malloc_zones.small.start = mmap_anon_aligned(
			g_malloc_zones.small.block_count *
				(g_malloc_zones.small.block_size + HEADER_SIZE),
			PROT_READ | PROT_WRITE);

	for (_size_t i = 0; i < g_malloc_zones.small.block_count; i++)
	{
		header = GET_HEADER(get_fixed_zone_i(g_malloc_zones.small.start, i));
		if (!header)
			continue ;

		*header = MAKE_HEADER(0, 1, 0);
		g_malloc_zones.small.free_blocks--;
	}

	if (DEBUG)
		g_debug_fd = open(DEBUG_PATH, O_WRONLY | O_CREAT | O_TRUNC, 0644);
}

void	malloc_global_init_once(void)
{
	static pthread_once_t once = PTHREAD_ONCE_INIT;

	pthread_once(&once, malloc_global_init);
}
