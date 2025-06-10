/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_malloc.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:19:06 by dda-cunh          #+#    #+#             */
/*   Updated: 2025/06/09 15:30:54 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _LIBFT_MALLOC_H
# define _LIBFT_MALLOC_H

#include <stddef.h>

void	*realloc(void *ptr, size_t size);
void	*malloc(size_t size);
void	show_alloc_mem();
void	free(void *ptr);

#endif
