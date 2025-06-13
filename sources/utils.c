/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:09:44 by dda-cunh          #+#    #+#             */
/*   Updated: 2025/06/13 19:14:38 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_malloc.h"

_size_t block_real_len(_size_t len)
{
	if (IS_LARGE(len))
		return (len + HEADER_SIZE);

	if (len > TINY_SIZE)
		return (SMALL_SIZE);
	return (TINY_SIZE);
}
