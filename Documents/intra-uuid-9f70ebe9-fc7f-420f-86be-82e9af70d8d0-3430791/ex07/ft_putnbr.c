/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edalmis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 20:26:23 by edalmis           #+#    #+#             */
/*   Updated: 2021/01/20 10:08:56 by edalmis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int nb)
{
	long int i;

	i = nb;
	if (i < 0)
	{
		ft_putchar('-');
		i = -i;
		if (i > 9)
			ft_putchar(i / 10 + '0');
		ft_putchar(i % 10 + '0');
	}
	else if (i > 9)
	{
		ft_putchar(i / 10 + '0');
		ft_putchar(i % 10 + '0');
	}
	else
		ft_putchar(i + '0');
}
