/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhauvill <jhauvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 10:42:50 by jhauvill          #+#    #+#             */
/*   Updated: 2025/10/20 12:37:33 by jhauvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlist;
	t_list	*newnode;
	void	*content;

	if (!lst)
		return (NULL);
	newlist = NULL;
	while (lst)
	{
		content = f(lst->content);
		newnode = ft_lstnew(content);
		if (!newnode)
		{
			del(content);
			ft_lstclear(&newlist, del);
			return (NULL);
		}
		ft_lstadd_back(&newlist, newnode);
		lst = lst->next;
	}
	return (newlist);
}

//void print_content(void *content)
//{
//    printf("%s\n", (char *)content);
//}
//void *duplicate_upper(void *content)
//{
//    char *str = (char *)content;
//    char *dup = ft_strdup(str);
//    int i = 0;
//    while (dup[i])
//    {
//        if (dup[i] >= 'a' && dup[i] <= 'z')
//            dup[i] -= 32;
//        i++;
//    }
//    return dup;
//}
//void del(void *content)
//{
//    free(content);
//}
//int main(void)
//{
//    t_list *list = NULL;
//    t_list *new_list;  
//    ft_lstadd_back(&list, ft_lstnew("un"));
//    ft_lstadd_back(&list, ft_lstnew("deux"));
//    ft_lstadd_back(&list, ft_lstnew("trois"));  
//    new_list = ft_lstmap(list, duplicate_upper, del); 
//    printf("Liste mappee:\n");
//    ft_lstiter(new_list, print_content);    
//    return 0;
//}