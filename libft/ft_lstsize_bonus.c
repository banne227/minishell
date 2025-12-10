/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhauvill <jhauvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 15:07:02 by jhauvill          #+#    #+#             */
/*   Updated: 2025/10/17 16:05:47 by jhauvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	struct s_list	*current;
	int				i;

	i = 0;
	current = lst;
	if (current == NULL)
		return (0);
	while (current->next != NULL)
	{
		i++;
		current = current->next;
	}
	return (i + 1);
}
