/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:21:23 by dda-cunh          #+#    #+#             */
/*   Updated: 2025/08/17 13:34:30 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_malloc.h"

// #include <stdio.h>

void    loop_malloc_free(int n, _size_t size)
{
    void *pointers[n];

    for (int i = 0; i <= n; i++)
        pointers[i] = malloc(size);

    while (n-- > 0)
        free(pointers[n]);
}

int	main(void)
{
    // char *ptr = malloc(1025);

    // // malloc(20);
    // *ptr = 'Z';
    // * (ptr + 1) = '\0';

    // printf("%s\n", ptr);
    // // printf("%lu\n", *GET_HEADER(GET_BLOCK(ptr)));
    // printf("Header\t\t%p\n", GET_BLOCK(ptr) );
    // printf("After header\t%p\n", ptr);

    // free(ptr);

    loop_malloc_free(1000, 4097);


    return (0);
}
