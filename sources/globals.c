/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 11:30:34 by dda-cunh          #+#    #+#             */
/*   Updated: 2025/08/03 11:42:31 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_malloc.h"

malloc_zones	g_malloc_zones = {
									{
										NULL,
										TINY_BLOCK_SIZE,
										TINY_BLOCKS
									},
									{
										NULL,
										SMALL_BLOCK_SIZE,
										SMALL_BLOCKS
									}
								};

static void	malloc_global_init(void)
{
	g_malloc_zones.small.start = NULL; //TODO: mmap here based on area size


	g_malloc_zones.tiny.start = NULL; //TODO: mmap here based on area size

}

void    malloc_global_init_once(void)
{
	static pthread_once_t once = PTHREAD_ONCE_INIT;

	pthread_once(&once, malloc_global_init);
}
