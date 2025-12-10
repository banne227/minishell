/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhauvill <jhauvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 15:58:09 by jhauvill          #+#    #+#             */
/*   Updated: 2025/10/14 18:11:16 by jhauvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*d1;
	unsigned char	*d2;
	size_t			i;

	if (n == 0)
		return (0);
	d1 = (unsigned char *)s1;
	d2 = (unsigned char *)s2;
	i = 0;
	while (d1[i] == d2[i] && i < n - 1)
	{
		i++;
	}
	return (d1[i] - d2[i]);
}

//int main (void)
//{
//	const char *s1 = "\xff\xaa\xde\x12";
//	const char *s2 = "\xff\xaa\xde\x12MACOSAAAAA";
//	size_t n = 4;
//	printf("%d", ft_memcmp(s1, s2, n));
//	return 0;
//}
