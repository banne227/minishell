/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhauvill <jhauvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 15:32:26 by jhauvill          #+#    #+#             */
/*   Updated: 2025/10/15 17:23:06 by jhauvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*ss1;
	unsigned char	*ss2;
	size_t			i;

	ss1 = (unsigned char *)s1;
	ss2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (ss1[i] == ss2[i] && i < n - 1 && (ss1[i] || ss2[i]))
		i++;
	return (ss1[i] - ss2[i]);
}
//int main(void)
//{
//	char *s1 = "abcde";
//	char *s2 = "abcde";
//	size_t n = 0;
//	printf("%d", ft_strncmp(s1,s2,n));
//	return 0;
//}