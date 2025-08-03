/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:09:44 by dda-cunh          #+#    #+#             */
/*   Updated: 2025/08/03 12:32:04 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_malloc.h"

_size_t block_real_len(_size_t len)
{
	if (IS_LARGE(len))
		return (len + HEADER_SIZE);

	if (len > TINY_BLOCK_SIZE)
		return (SMALL_BLOCK_SIZE);
	return (TINY_BLOCK_SIZE);
}
