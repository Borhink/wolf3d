/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 12:22:07 by qhonore           #+#    #+#             */
/*   Updated: 2016/03/17 04:07:12 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	intlen(long nbr)
{
	int		i;

	i = 0;
	if (nbr == 0)
		return (1);
	while (nbr)
	{
		nbr /= 10;
		i++;
	}
	return (i);
}

char		*ft_itoa(int nbr)
{
	char	*s;
	int		i;
	int		neg;
	int		div;

	if (nbr == -2147483648)
		return (ft_strdup("-2147483648"));
	div = 1;
	neg = nbr < 0 ? 1 : 0;
	nbr = nbr < 0 ? -nbr : nbr;
	i = intlen(nbr);
	s = (char*)malloc(sizeof(char) * (i + neg + 1));
	s[i + neg] = '\0';
	while (--i >= 0)
	{
		s[i + neg] = ((nbr / div) % 10) + '0';
		div *= 10;
	}
	if (neg)
		s[0] = '-';
	return (s);
}

char		*ft_ltoa(long nbr)
{
	char	*s;
	int		i;
	int		neg;
	long	div;

	if (nbr == -9223372036854775807)
		return (ft_strdup("-9223372036854775807"));
	div = 1;
	neg = nbr < 0 ? 1 : 0;
	nbr = nbr < 0 ? -nbr : nbr;
	i = intlen(nbr);
	s = (char*)malloc(sizeof(char) * (i + neg + 1));
	s[i + neg] = '\0';
	while (--i >= 0)
	{
		s[i + neg] = ((nbr / div) % 10) + '0';
		div *= 10;
	}
	if (neg)
		s[0] = '-';
	return (s);
}

char		*ft_dtoa(double nbr, unsigned int acc)
{
	char	*s;
	char	*tmp;

	if (nbr < 0.000000000000000001)
	{
		nbr = -nbr;
		s = ft_strjoin(ft_ltoa((int)nbr), ".");
		tmp = ft_strjoin("-", s);
		if (s)
			free(s);
	}
	else
		tmp = ft_strjoin(ft_ltoa((int)nbr), ".");
	nbr = nbr - (int)nbr;
	if (acc > 18)
		acc = 18;
	s = ft_strjoin(tmp, ft_ltoa((int)(nbr * ft_pow(10, acc))));
	if (tmp)
		free(tmp);
	return (s);
}
