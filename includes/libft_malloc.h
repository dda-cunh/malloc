/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_malloc.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:19:06 by dda-cunh          #+#    #+#             */
/*   Updated: 2025/11/02 14:04:07 by dda-cunh         ###   ########.fr       */
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

#define DEBUG					1

#define DEBUG_PATH				"logs.txt"

#define GET_PAGE_SIZE()			sysconf(_SC_PAGESIZE)
#define COMPILE_PAGE_SIZE		4096

#define MALLOC_INIT()			malloc_global_init_once()

#define _size_t					uint64_t
#define byte					uint8_t

/*
** Block Header/Footer Layout (64 bits total, big-endian bit order):
** ------------------------------------------------------------------
** | Bits 63–2                        | Bit 1       | Bit 0 (LSB)   |
** |----------------------------------|-------------|---------------|
** | Block size in bytes (shifted)    | FIXED_FLAG  | ALLOC_FLAG    |
** ------------------------------------------------------------------
*/
#define HEADER_SIZE				sizeof(_size_t)
#define FOOTER_SIZE				HEADER_SIZE

#define GET_BLOCK(ptr)			((uint8_t *)ptr - HEADER_SIZE)
#define HEAD_TO_PTR(b_head)		((void *)((byte *)(b_head) + HEADER_SIZE))

#define ALLOC_FLAG				((_size_t)1u)
#define FIXED_FLAG				((_size_t)2u)
#define SIZE_SHIFT				2

#define BLOCK_SIZE(meta)		((*(meta)) >> SIZE_SHIFT)

#define GET_HEADER(block)		((_size_t *)block)
#define GET_FOOTER_PREV(zone_start, block) \
	(block > zone_start ? (_size_t *)((byte*)block - FOOTER_SIZE) : NULL)

#define INVALID_SIZE(size)		((size >> (8 * HEADER_SIZE - SIZE_SHIFT)) & 1)

#define MAKE_HEADER(size, is_fixed, is_alloc) \
	((((_size_t)(size)) << SIZE_SHIFT) | ((is_fixed) ? FIXED_FLAG : 0) | ((is_alloc) ? ALLOC_FLAG : 0))
#define MAKE_FOOTER			MAKE_HEADER

#define SET_ALLOC(b_head)	((*(meta)) |= ALLOC_FLAG)
#define CLR_ALLOC(meta)		((*(meta)) &= ~ALLOC_FLAG)
#define SET_FIXED(meta)		((*(meta)) |= FIXED_FLAG)
#define CLR_FIXED(meta)		((*(meta)) &= ~FIXED_FLAG)

#define IS_ALLOC(meta)		((*(meta)) & ALLOC_FLAG)
#define IS_FIXED(meta)		((*(meta)) & FIXED_FLAG)

#define SMALL_PAGES				30
#define TINY_PAGES				9

#define SMALL_BLOCK_SIZE		1024
#define TINY_BLOCK_SIZE			128

#define SMALL_BLOCKS			((SMALL_PAGES * COMPILE_PAGE_SIZE) / SMALL_BLOCK_SIZE)
#define TINY_BLOCKS				((TINY_PAGES * COMPILE_PAGE_SIZE) / TINY_BLOCK_SIZE)


#define RET_NULL_IF(bool) \
	if (bool) \
		return(NULL)

typedef struct	s_fixed_zone
{
	void	*start;
	_size_t	size;
	_size_t	capacity;
}	fixed_zone;

typedef struct s_malloc_zones
{
	fixed_zone	tiny;
	fixed_zone	small;
}	malloc_zones;

void	*realloc(void *ptr, size_t size);
void	*malloc(size_t size);
void	show_alloc_mem();
void	free(void *ptr);

/*******************************  Utils  ********************************/
_size_t	get_aligned_size(_size_t size, byte is_fixed);
void	*fixed_zone_block_minus(void *block, fixed_zone *zone);
void	*fixed_zone_block_plus(void *block, fixed_zone *zone);
void	*mmap_anon_aligned(_size_t size, byte is_fixed);


/******************************  Globals  *******************************/
extern malloc_zones	g_malloc_zones;
extern int			g_debug_fd;

void	malloc_global_init_once(void);

#endif
