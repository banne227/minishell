/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhauvill <jhauvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 15:16:59 by jhauvill          #+#    #+#             */
/*   Updated: 2025/10/17 12:17:35 by jhauvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len_nb( long int n)
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

static char	*fill(long int n, int s, char *str, int count)
{
	int	i;

	i = 0;
	if (s == 1)
	{
		str[i] = '-';
		i++;
	}
	while (count >= 1)
	{
		str[i] = (n / count) % 10 + '0';
		i++;
		count = count / 10;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	long int		nb;
	char			*str;
	int				s;
	long int		count;
	int				c;

	s = 0;
	nb = n;
	count = 1;
	c = ft_len_nb(nb);
	if (nb < 0)
	{
		nb *= -1;
		s++;
	}
	c = ft_len_nb(nb);
	str = malloc(sizeof(char) * (c + s) + 1);
	if (!str)
		return (NULL);
	while (c-- > 1)
		count *= 10;
	str = fill(nb, s, str, count);
	return (str);
}
//int main(void)
//{
//	int n = 0;
//	printf("%s", ft_itoa(n));
//	return (0);
//}