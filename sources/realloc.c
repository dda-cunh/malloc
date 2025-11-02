/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 15:27:22 by dda-cunh          #+#    #+#             */
/*   Updated: 2025/11/02 14:27:01 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_malloc.h"

// TODO: implement logic for spliting a block into one free and one alloced
// 			when realloc results in a shrink of a fixed_zone block
static void	shrink_fixed_block(void *block)
{

}

void	*realloc(void *ptr, size_t size)
{
	_size_t	*header;
	_size_t	old_len;
	void	*new_ptr;

	if (!ptr || INVALID_SIZE(size))
		return (malloc(size));

	header = GET_HEADER(GET_BLOCK(ptr));

	old_len = BLOCK_SIZE(header);
	if (size <= old_len)
	{
		if (!IS_FIXED(header))
		{
			_size_t	old_aligned = get_aligned_size(old_len, 1);
			_size_t	new_aligned = get_aligned_size(size, 1);

			if (new_aligned < old_aligned)
				munmap((byte *)header + new_aligned,
						old_aligned - new_aligned);
		}
		else
			shrink_fixed_block(GET_BLOCK(ptr));

		*header = MAKE_HEADER(size, IS_FIXED(header), 1);
		return (ptr);
	}

	new_ptr = malloc(size);
	RET_NULL_IF(!new_ptr);

	header = GET_HEADER(GET_BLOCK(new_ptr));
	ft_memcpy(new_ptr, ptr, old_len < size ? old_len : size);
	free(ptr);
	return (new_ptr);
}
