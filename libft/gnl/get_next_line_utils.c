/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhauvill <jhauvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 17:59:16 by jhauvill          #+#    #+#             */
/*   Updated: 2025/11/27 13:00:51 by jhauvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_gnl(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup_gnl(const char *s)
{
	char	*d;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	d = malloc(sizeof(char) * (ft_strlen_gnl(s) + 1));
	if (!d)
		return (NULL);
	while (s[i])
	{
		d[i] = s[i];
		i++;
	}
	d[i] = '\0';
	return (d);
}

char	*ft_substr_gnl(char const *s, unsigned int start, size_t len)
{
	char			*substring;
	unsigned int	i;

	i = -1;
	if (!s)
		return (NULL);
	if (start >= ft_strlen_gnl(s))
		return (ft_strdup_gnl(""));
	if (len > ft_strlen_gnl(s) -start)
		len = ft_strlen_gnl(s) - start;
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

void	*ft_memcpy_gnl(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*s;
	unsigned char	*d;

	s = (unsigned char *)src;
	d = (unsigned char *)dest;
	i = 0;
	if (dest == NULL && src == NULL)
		return (NULL);
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

char	*ft_strchr_gnl(const char *s, int c)
{
	int		i;

	if (!s)
		return (NULL);
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
