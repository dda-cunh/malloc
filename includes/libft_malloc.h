/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_malloc.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:19:06 by dda-cunh          #+#    #+#             */
/*   Updated: 2025/08/17 13:52:10 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _LIBFT_MALLOC_H
# define _LIBFT_MALLOC_H


# include <sys/mman.h>
# include <pthread.h>
# include <stddef.h>
# include <stdint.h>
# include <unistd.h>
# include <fcntl.h>

#include "../lib/libft/libft.h"

//TODO: Maybe instead of having the alloc bit use a stack to track free blocks in fixed zones

#define DEBUG				1

#define DEBUG_PATH			"logs.txt"

#define GET_PAGE_SIZE()		sysconf(_SC_PAGESIZE)
#define COMPILE_PAGE_SIZE	4096

#define MALLOC_INIT()		malloc_global_init_once()

#define _size_t				uint64_t
#define byte				uint8_t

/*
** Block Header Layout (64 bits total, big-endian bit order):
** ------------------------------------------------------------------
** | Bits 63–2                        | Bit 1       | Bit 0 (LSB)   |
** |----------------------------------|-------------|---------------|
** | Block size in bytes (shifted)    | FIXED_FLAG  | ALLOC_FLAG    |
** ------------------------------------------------------------------
*/
#define HEADER_SIZE			sizeof(_size_t)

#define GET_BLOCK(ptr)		((uint8_t *)ptr - HEADER_SIZE)

#define GET_HEADER(chunk)	((_size_t *)chunk)

#define ALLOC_FLAG			((_size_t)1u)
#define FIXED_FLAG			((_size_t)2u)
#define SIZE_SHIFT			2

#define MAKE_HEADER(size, is_fixed, is_alloc) \
	((((_size_t)(size)) << SIZE_SHIFT) | ((is_fixed) ? FIXED_FLAG : 0) | ((is_alloc) ? ALLOC_FLAG : 0))

#define SET_ALLOC(b_head)	((*(b_head)) |= ALLOC_FLAG)
#define CLR_ALLOC(b_head)	((*(b_head)) &= ~ALLOC_FLAG)
#define SET_FIXED(b_head)	((*(b_head)) |= FIXED_FLAG)
#define CLR_FIXED(b_head)	((*(b_head)) &= ~FIXED_FLAG)

#define IS_ALLOC(b_head)	((*(b_head)) & ALLOC_FLAG)
#define IS_FIXED(b_head)	((*(b_head)) & FIXED_FLAG)
#define BLOCK_SIZE(b_head)	((*(b_head)) >> SIZE_SHIFT)

#define SMALL_PAGES			30
#define TINY_PAGES			9

#define SMALL_BLOCK_SIZE	1024
#define TINY_BLOCK_SIZE		128

#define SMALL_BLOCKS		((SMALL_PAGES * COMPILE_PAGE_SIZE) / SMALL_BLOCK_SIZE)
#define TINY_BLOCKS			((TINY_PAGES * COMPILE_PAGE_SIZE) / TINY_BLOCK_SIZE)


typedef struct s_fixed_zone
{
	void	*start;
	_size_t	block_size;
	_size_t	block_count;
	_size_t	free_blocks;
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

/*******************************  Utils  ********************************/
_size_t	get_aligned_size(_size_t size);
void	*get_fixed_zone_i(fixed_zone *zone, _size_t i);
void	*mmap_anon_aligned(_size_t size, int prot);


/******************************  Globals  *******************************/
extern malloc_zones	g_malloc_zones;
extern int			g_debug_fd;

void	malloc_global_init_once(void);

#endif
