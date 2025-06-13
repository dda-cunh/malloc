/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:21:23 by dda-cunh          #+#    #+#             */
/*   Updated: 2025/06/13 20:46:41 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_malloc.h"

malloc_zones	g_malloc_zones = {
									{
										NULL,
										TINY_SIZE,
										TINY_BLOCKS
									},
									{
										NULL,
										SMALL_SIZE,
										SMALL_BLOCKS
									}
								};

void	*malloc(size_t size)
{
	return (NULL);
}
