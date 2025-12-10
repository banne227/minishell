/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhauvill <jhauvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 15:01:17 by jhauvill          #+#    #+#             */
/*   Updated: 2025/10/15 13:41:36 by jhauvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;

	i = 0;
	while (s[i] && s[i] != (char) c)
	{
		i++;
	}
	if (s[i] == (char) c)
		return ((char *) &s[i]);
	else if ((char) c == '\0')
		return ((char *) &s[i]);
	return (NULL);
}

//int main(void)
//{
//	char *str = "abcde";
//	int c = 'd';
//	printf("%s", ft_strchr(str,c));
//	return 0;
//}
