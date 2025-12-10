/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhauvill <jhauvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:22:45 by jhauvill          #+#    #+#             */
/*   Updated: 2025/10/20 12:55:11 by jhauvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *)s;
	while (i < n)
	{
		ptr[i] = c;
		i++;
	}
	return (s);
}

//int main(void)
//{
//	int i = 0;
//	char *str;
//	str = malloc(5);
//	while(i < 5)
//	{
//		str[i] = 'e';
//		i++;
//	}
//	ft_memset(str,33,2);
//	printf("%s", str);
//	return 0;
//}
