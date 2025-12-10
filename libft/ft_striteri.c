/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhauvill <jhauvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 15:07:54 by jhauvill          #+#    #+#             */
/*   Updated: 2025/10/20 12:53:58 by jhauvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	i;

	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}

//void to_upper(unsigned int i, char *c)
//{
//	(void)    i;
//	*c = ft_toupper(*c);
//}

//int main()
//{
//    char s[]= "abc";
//    ft_striteri(s, to_upper);
//    printf("%s", s);
//}
