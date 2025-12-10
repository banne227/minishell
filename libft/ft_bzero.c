/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhauvill <jhauvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:51:55 by jhauvill          #+#    #+#             */
/*   Updated: 2025/10/20 12:57:25 by jhauvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *) s;
	while (i < n)
	{
		ptr[i] = '\0';
		i++;
	}
}

//int main (void)
//{
//	int i = 0;
//	char *str;
//	str = malloc(3);
//	while(i < 3)
//	{
//	str[i] = 'e';
//		i++;
//	}
//	ft_bzero(str,1);
//	printf("%s", str);
//	i = 0;
//	while(i < 3)
//	{
//		write(1,&str[i],1);
//		i++;
//	}
//	return 0;
//}
