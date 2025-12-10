/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhauvill <jhauvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 13:42:34 by jhauvill          #+#    #+#             */
/*   Updated: 2025/10/15 15:24:32 by jhauvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = NULL;
	while (s[i])
	{
		if (s[i] == (char) c)
			ptr = (char *) &s[i];
		i++;
	}
	if ((char)c == '\0')
		return ((char *) &s[i]);
	return (ptr);
}

//int main(void)
//{
//	char *s = "abbcd";
//	int c = 'b';
//	printf("%s", ft_strrchr(s,c));
//	return 0;
//}
