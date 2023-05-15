/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   html_picture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 12:27:05 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/05/15 13:38:42 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arachnida.h"

t_list *
html_get_pictures (t_site *site)
{
	char	*el;
	char	*picture;
	t_list	*pictures;
	t_list	*elements;
	t_list	*picture_lst = NULL;

	if (site == NULL)
		return (NULL);

	elements = site->elements;
	while (elements != NULL)
	{
		el = elements->content;
		if (strncmp(el, "<picture ", strlen("<picture ")) == 0)
		{
			pictures = html_get_attr_values ("srcset", el);
			while (pictures != NULL)
			{
				picture = pictures->content;
				if (picture != NULL && *picture != '\0')
				{
					if (*picture == '/')
							url_resolve_absolute (site, &picture);
					ft_lstadd_back (&picture_lst, ft_lstnew ((void *) picture));
				}
				pictures = pictures->next;
			}
		}
		elements = elements->next;
	}
	return (picture_lst);
}
