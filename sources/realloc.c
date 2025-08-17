/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 15:27:22 by dda-cunh          #+#    #+#             */
/*   Updated: 2025/08/16 17:02:59 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_malloc.h"

void	*realloc(void *ptr, size_t size)
{
	_size_t	*header;
	_size_t	old_len;
	void	*new_ptr;


	if (!ptr)
		return (malloc(size));

	header = GET_HEADER(GET_BLOCK(ptr));

	old_len = BLOCK_SIZE(header);
	if (size <= old_len)
	{
		if (!IS_FIXED(header))
		{
			_size_t	old_aligned = get_aligned_size(old_len + HEADER_SIZE);
			_size_t	new_aligned = get_aligned_size(size + HEADER_SIZE);

			if (new_aligned < old_aligned)
				munmap((byte *)header + new_aligned,
						old_aligned - new_aligned);
		}
		*header = MAKE_HEADER(size, IS_FIXED(header), 1);
		return (ptr);
	}

	new_ptr = malloc(size);
	if (!new_ptr)
		return (NULL);
	header = GET_HEADER(GET_BLOCK(new_ptr));
	ft_memcpy(new_ptr, ptr, old_len < size ? old_len : size);
	free(ptr);
	return (new_ptr);
}
