/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 13:06:55 by dda-cunh          #+#    #+#             */
/*   Updated: 2025/08/17 13:15:55 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_put_ptr(uintptr_t num, int fd)
{
	if (num >= 16)
	{
		ft_put_ptr(num / 16, fd);
		ft_put_ptr(num % 16, fd);
	}
	else
	{
		if (num <= 9)
			ft_putchar_fd((num + '0'), fd);
		else
			ft_putchar_fd((num - 10 + 'a'), fd);
	}
}

void	ft_putptr_fd(void *ptr, int fd)
{
	uintptr_t	ptr_num;

	ptr_num = (uintptr_t)ptr;

	ft_putstr_fd("0x", fd);
	if (ptr == 0)
		ft_putchar_fd('0', fd);
	else
		ft_put_ptr(ptr_num, fd);
}
