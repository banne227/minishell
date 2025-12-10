/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhauvill <jhauvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 15:33:57 by jhauvill          #+#    #+#             */
/*   Updated: 2025/10/15 15:22:28 by jhauvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const char	*ptr;
	size_t		i;

	ptr = (const char *)s;
	i = 0;
	while (i < n)
	{
		if (ptr[i] == (char) c)
			return ((void *) &ptr[i]);
		i++;
	}
	return (NULL);
}

//int main(void)
//{
//	const char *s = "abcdes";
//	int c = 'b';
//	size_t n = 6;
//	char *str = ft_memchr(s,c,n);
//	printf("%s", str);
//	return 0;
//}