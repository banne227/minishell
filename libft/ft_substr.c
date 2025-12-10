/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhauvill <jhauvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 10:15:56 by jhauvill          #+#    #+#             */
/*   Updated: 2025/10/16 11:00:26 by jhauvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substring;
	unsigned int	i;

	i = -1;
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s) -start)
		len = ft_strlen(s) - start;
	substring = (char *) malloc(sizeof(char) * (len + 1));
	if (substring == NULL)
		return (NULL);
	while (++i < len)
	{
		substring[i] = s[start + i];
	}
	substring[i] = '\0';
	return (substring);
}

//int main (void)
//{
//	char * s = "abcdefghijk";
//	unsigned int start = 3;
//	size_t len = 3;
//	printf("%s", ft_substr(s,start,len));
//	return 0;
//}