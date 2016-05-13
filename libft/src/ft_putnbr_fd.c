/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 16:06:28 by qhonore           #+#    #+#             */
/*   Updated: 2015/12/12 14:20:28 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	intlen(int n)
{
	int		len;

	len = 0;
	while (n >= 10)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static void	neg_to_pos(int *n, int fd)
{
	if (*n < 0)
	{
		*n = -(*n);
		ft_putchar_fd('-', fd);
	}
}

void		ft_putnbr_fd(int n, int fd)
{
	int		len;
	int		div;

	div = 1;
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	neg_to_pos(&n, fd);
	len = intlen(n);
	while (len--)
		div *= 10;
	while (div > 0)
	{
		ft_putchar_fd((n / div) % 10 + 48, fd);
		div /= 10;
	}
}
