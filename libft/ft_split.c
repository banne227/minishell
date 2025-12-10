/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhauvill <jhauvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:09:12 by jhauvill          #+#    #+#             */
/*   Updated: 2025/12/04 15:06:49 by jhauvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_counts_words(const char *s, char c)
{
	int	i;
	int	counts;

	i = 0;
	counts = 0;
	while (s[i])
	{
		if (s[i] && s[i] != c)
		{
			counts++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return (counts);
}

static char	*ft_splitdup(const char *s, char c)
{
	int		i;
	char	*str;
	int		len;

	i = 0;
	while (s[i] && s[i] != c)
	{
		i++;
	}
	len = i;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

void	free_tab(char **tab, int size)
{
	while (size >= 0)
	{
		free(tab[size]);
		size--;
	}
	free(tab);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	char	**tab;

	i = 0;
	j = 0;
	tab = malloc(sizeof(char *) * (ft_counts_words(s, c) + 1));
	if (!tab)
		return (NULL);
	while (s[i])
	{
		if (s[i] != c)
		{
			tab[j] = ft_splitdup(&s[i], c);
			if (!tab[j])
				return (free_tab(tab, j), NULL);
			j++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	tab[j] = NULL;
	return (tab);
}
// int	main(void)
//{
// 	char **ptr;
// 	int i = -1;

// 	ptr = ft_split(abcd e f ghij ", ' ');
// 	while (ptr[++i])
// 		printf("%s\n", ptr[i]);
// 	return (0);
// 	i = -1;
// 	while (ptr[i++])
// 		free(ptr[i]);
// 	free(ptr);
//	return (0);
//}