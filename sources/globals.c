/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 11:30:34 by dda-cunh          #+#    #+#             */
/*   Updated: 2025/08/03 19:03:41 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_malloc.h"

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

static void	malloc_global_init(void)
{
	g_malloc_zones.small.start = mmap_anon_aligned(
			g_malloc_zones.small.block_count *
				(g_malloc_zones.small.block_size + HEADER_SIZE),
			PROT_READ | PROT_WRITE);

	g_malloc_zones.tiny.start = mmap_anon_aligned(
			g_malloc_zones.tiny.block_count *
				(g_malloc_zones.tiny.block_size + HEADER_SIZE),
			PROT_READ | PROT_WRITE);
}

void	malloc_global_init_once(void)
{
	static pthread_once_t once = PTHREAD_ONCE_INIT;

	pthread_once(&once, malloc_global_init);
}
