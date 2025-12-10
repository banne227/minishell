/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhauvill <jhauvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 12:28:33 by jhauvill          #+#    #+#             */
/*   Updated: 2025/11/27 12:50:18 by jhauvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_len_nbr( long int n)
{
	int	p;

	p = 0;
	if (n == 0)
		p = 1;
	while (n > 0)
	{
		n = n / 10;
		p++;
	}
	return (p);
}

int	ft_puthexlow(unsigned int n)
{
	char	*base;
	int		count;

	count = 0;
	base = "0123456789abcdef";
	if (n >= 16)
		count += ft_puthexlow(n / 16);
	count += ft_putchar(base[n % 16]);
	return (count);
}

int	ft_puthexupp(unsigned int n)
{
	char	*base;
	int		count;

	count = 0;
	base = "0123456789ABCDEF";
	if (n >= 16)
		count += ft_puthexupp(n / 16);
	count += ft_putchar(base[n % 16]);
	return (count);
}

int	ft_putunbr(unsigned int n)
{
	int				count;
	unsigned int	div;

	count = 0;
	div = n;
	if (div >= 10)
	{
		div /= 10;
		count += ft_putunbr(div);
	}
	count += ft_putchar(n % 10 + '0');
	return (count);
}

int	ft_printhex(unsigned long address, char *base)
{
	int	count;

	count = 0;
	if (address >= 16)
		count += ft_printhex(address / 16, base);
	count += ft_putchar(base[address % 16]);
	return (count);
}
