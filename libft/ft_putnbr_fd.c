/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhauvill <jhauvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 11:09:46 by jhauvill          #+#    #+#             */
/*   Updated: 2025/10/15 14:50:29 by jhauvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int	div;
	int	mod;

	div = 0;
	mod = 0;
	if (n != -2147483648)
	{
		if (n < 0)
		{
			write(fd, "-", 1);
			n *= -1;
		}
		div = n;
		if (div >= 10)
		{
			div /= 10;
			ft_putnbr_fd(div, fd);
		}
		mod = n % 10 + '0';
		write(fd, &mod, 1);
	}
	else
		write(fd, "-2147483648", 11);
}

//int main(void)
//{
//	ft_putnbr_fd(2147483647,1);
//	return 0;
//}