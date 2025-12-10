/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhauvill <jhauvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 17:55:14 by jhauvill          #+#    #+#             */
/*   Updated: 2025/11/27 13:03:50 by jhauvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_check(char *tmp, char *buffer)
{
	char	*keep_tmp;
	size_t	len;

	keep_tmp = NULL;
	len = 0;
	if (tmp)
	{
		keep_tmp = ft_strdup_gnl(tmp);
		free(tmp);
		len = ft_strlen_gnl(keep_tmp) + ft_strlen_gnl(buffer);
		tmp = malloc(len + 1);
		if (!tmp)
			return (NULL);
		ft_memcpy_gnl(tmp, keep_tmp, ft_strlen_gnl(keep_tmp) + 1);
		tmp[ft_strlen_gnl(keep_tmp)] = '\0';
		ft_memcpy_gnl(ft_strchr_gnl(tmp, '\0'), buffer,
			ft_strlen_gnl(buffer) + 1);
		tmp[len] = '\0';
		free(keep_tmp);
	}
	else if (!tmp)
		tmp = ft_strdup_gnl(buffer);
	return (tmp);
}

void	ft_exchange(char **ptr)
{
	char	*keep_tmp;

	keep_tmp = NULL;
	keep_tmp = ft_strdup_gnl(ft_strchr_gnl(*ptr, '\n') + 1);
	free(*ptr);
	*ptr = keep_tmp;
}

char	*ft_extract_line(char	**ptr_tmp, char **ptr_buffer, ssize_t b)
{
	char	*line;

	line = NULL;
	if (*ptr_tmp && **ptr_tmp && b == 0)
	{
		line = ft_strdup_gnl(*ptr_tmp);
		free(*ptr_tmp);
		*ptr_tmp = NULL;
		free(*ptr_buffer);
		*ptr_buffer = NULL;
		return (line);
	}
	if (ft_strchr_gnl(*ptr_tmp, '\n') != NULL)
	{
		line = ft_substr_gnl(*ptr_tmp, 0, (ft_strlen_gnl(*ptr_tmp)
					- ft_strlen_gnl(ft_strchr_gnl(*ptr_tmp, '\n'))) + 1);
		ft_exchange(ptr_tmp);
		return (line);
	}
	free(*ptr_tmp);
	*ptr_tmp = NULL;
	free(*ptr_buffer);
	*ptr_buffer = NULL;
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*tmp;
	char		*buffer;
	ssize_t		byte;

	buffer = NULL;
	byte = 1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (byte != 0)
	{
		if (ft_strchr_gnl(tmp, '\n') != NULL)
			return (ft_extract_line(&tmp, &buffer, byte));
		buffer = malloc(BUFFER_SIZE + 1);
		if (!buffer)
			return (NULL);
		byte = read(fd, buffer, BUFFER_SIZE);
		if (byte <= 0)
			break ;
		buffer[byte] = '\0';
		tmp = ft_check(tmp, buffer);
		free(buffer);
		buffer = NULL;
	}
	return (ft_extract_line(&tmp, &buffer, byte));
}

//int	main(void)
//{
//	int		fd;
//	char	*line;
//	int		i;

//	i = 1;
//	fd = open("test.txt", O_RDONLY);
//	if (fd == -1)
//		return (1);
//	line = get_next_line(fd);
//	while (line)
//	{
//		printf("Ligne %d : %s", i, line);
//		free(line);
//		line = get_next_line(fd);
//		i++;
//	}
//	printf("\n%s", line);
//	close(fd);
//	return (0);
//}