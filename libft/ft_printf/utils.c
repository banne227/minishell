/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhauvill <jhauvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 09:36:13 by jhauvill          #+#    #+#             */
/*   Updated: 2025/11/27 12:57:11 by jhauvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_strlen_printf(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_printadress(unsigned long address)
{
	int		count;
	char	*base;

	count = 0;
	base = "0123456789abcdef";
	if (address == 0)
	{
		ft_putstr("(nil)");
		return (5);
	}
	count += ft_putstr("0x");
	count += ft_printhex(address, base);
	return (count);
}

int	ft_putstr(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (ft_putstr("(null)"));
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
	return (i);
}

int	ft_putnbr(int n)
{
	int	div;
	int	count;

	div = 0;
	count = 0;
	if (n == -2147483648)
		count += (write(1, "-2147483648", 11));
	else
	{
		if (n < 0)
		{
			count += write(1, "-", 1);
			n *= -1;
		}
		div = n;
		if (div >= 10)
		{
			div /= 10;
			count += ft_putnbr(div);
		}
		count += ft_putchar(n % 10 + '0');
	}
	return (count);
}
