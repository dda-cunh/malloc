/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 11:30:34 by dda-cunh          #+#    #+#             */
/*   Updated: 2025/11/02 14:32:33 by dda-cunh         ###   ########.fr       */
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

	g_malloc_zones.tiny.start = mmap_anon_aligned(TINY_BLOCKS * TINY_BLOCK_SIZE, 1);
	g_malloc_zones.tiny.size = get_aligned_size(TINY_BLOCKS * TINY_BLOCK_SIZE, 1);
	// TODO: Populate initian HEADER and FOOTER for the whole fixed_zone
	//			and set capacity (should it consider meta sizes?????)


	g_malloc_zones.small.start = mmap_anon_aligned(SMALL_BLOCKS * SMALL_BLOCK_SIZE, 1);
	g_malloc_zones.tiny.size = get_aligned_size(SMALL_BLOCKS * SMALL_BLOCK_SIZE, 1);
	// TODO: Populate initian HEADER and FOOTER for the whole fixed_zone
	//			and set capacity (should it consider meta sizes?????)


	// TODO: Figure out how LARGE zones bookkeeping should work


	if (DEBUG)
		g_debug_fd = open(DEBUG_PATH, O_WRONLY | O_CREAT | O_TRUNC, 0644);
}

void	malloc_global_init_once(void)
{
	static pthread_once_t once = PTHREAD_ONCE_INIT;

	pthread_once(&once, malloc_global_init);
}
