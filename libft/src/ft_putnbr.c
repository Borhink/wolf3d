/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 15:39:51 by qhonore           #+#    #+#             */
/*   Updated: 2015/11/29 20:25:30 by qhonore          ###   ########.fr       */
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

static void	neg_to_pos(int *n)
{
	if (*n < 0)
	{
		*n = -(*n);
		ft_putchar('-');
	}
}

void		ft_putnbr(int n)
{
	int		len;
	int		div;

	div = 1;
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		return ;
	}
	neg_to_pos(&n);
	len = intlen(n);
	while (len--)
		div *= 10;
	while (div > 0)
	{
		ft_putchar((n / div) % 10 + 48);
		div /= 10;
	}
}
