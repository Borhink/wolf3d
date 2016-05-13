/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/07 13:39:49 by qhonore           #+#    #+#             */
/*   Updated: 2015/12/07 13:41:03 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_isspace(int c)
{
	if (c == ' ' || c == '\n' || c == '\t' ||
		c == '\f' || c == '\r' || c == '\v')
		return (1);
	else
		return (0);
}