/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_malloc.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:19:06 by dda-cunh          #+#    #+#             */
/*   Updated: 2025/06/13 20:56:51 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _LIBFT_MALLOC_H
# define _LIBFT_MALLOC_H

#include <sys/mman.h>
#include <stddef.h>
#include <stdint.h>
#include <unistd.h>		 

#define _size_t				uint64_t

#define HEADER_SIZE			sizeof(_size_t)

#define GET_BLOCK(ptr)		((uint8_t *)ptr - HEADER_SIZE)

#define GET_HEADER(chunk)	((_size_t *)chunk)

#define BLOCK_SIZE(b_head)	(b_head >> 1)
#define FLIP_ALLOC(b_head)	(*b_head ^= 1)
#define IS_ALLOC(b_head)	(b_head & 1)

#define ALLOC_FLAG			1
#define SIZE_SHIFT			1

#define SMALL_BLOCKS		120
#define TINY_BLOCKS			150
#define SMALL_SIZE			1024
#define TINY_SIZE			128

#define IS_LARGE(size)		((size) > SMALL_SIZE)

typedef struct s_fixed_zone
{
	void	*start;
	_size_t	block_size;
	_size_t	block_count;
}	fixed_zone;

typedef struct s_malloc_zones
{
	fixed_zone		tiny;
	fixed_zone		small;
}	malloc_zones;

void	*realloc(void *ptr, size_t size);
void	*malloc(size_t size);
void	show_alloc_mem();
void	free(void *ptr);

/********************************  Utils  *******************************/
_size_t	block_real_len(_size_t len);

#endif
