/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhauvill <jhauvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 13:13:34 by jhauvill          #+#    #+#             */
/*   Updated: 2025/10/15 15:21:04 by jhauvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (little[i] == '\0')
		return ((char *)big);
	while (big[i] && i < len)
	{
		j = 0;
		while (big[i + j] == little[j] && big[i + j] && little[j]
			&& i + j < len)
			j++;
		if (j == ft_strlen(little))
			return ((char *) &big[i]);
		i++;
	}
	return (NULL);
}

//int main(void)
//{
//	char *big = "abcdef";
//	char *little = "cd";
//	size_t len = 5;
//	printf("%s", ft_strnstr(big,little,len));
//	return 0;
//}
