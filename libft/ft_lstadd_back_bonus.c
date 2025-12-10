/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhauvill <jhauvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 15:37:59 by jhauvill          #+#    #+#             */
/*   Updated: 2025/10/20 12:34:56 by jhauvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new;
}

//void print_content(void *content)
//{
//    printf("%s\n", (char *)content);
//}

//void free_content(void *content)
//{
//    free(content);
//}

//int main(void)
//{
//    t_list *list = NULL;
//    printf("=== Test des fonctions bonus de liste ===\n\n");  
//    ft_lstadd_front(&list, ft_lstnew(strdup("Deuxième")));
//    ft_lstadd_front(&list, ft_lstnew(strdup("Premier")));  
//    ft_lstiter(list, print_content);   
//    printf(" Taille de la liste (ft_lstsize): %d\n", ft_lstsize(list)); 
//    printf(" Dernier élément (ft_lstlast): %s\n\n\n", 
//           (char *)ft_lstlast(list)->content);
//    printf("\n --Ajout en fin avec ft_lstadd_back:\n\n");
//    ft_lstadd_back(&list, ft_lstnew(strdup("Troisieme")));
//    ft_lstiter(list, print_content); 
//    ft_lstadd_front(&list, ft_lstnew(strdup("toto")));
//    printf("\n  --Liste avant suppression:\n");
//    ft_lstiter(list, print_content);
//    t_list *to_delete = list;
//    list = list->next; 
//    ft_lstdelone(to_delete, free_content);
//    printf("  --Liste après suppression:\n");
//    ft_lstiter(list, print_content);    
//    printf("\n Nettoyage complet avec ft_lstclear:\n");
//    ft_lstclear(&list, free_content);
//    printf("   Listes vidées. Taille: %d\n", ft_lstsize(list));  
//    printf("\n=== Tests terminés ===\n");  
//    return 0;
//}