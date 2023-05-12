/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   html_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 10:43:12 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/05/12 17:07:05 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arachnida.h"

t_list *
html_get_images (t_site *site)
{
	char	*el;
	char	*img_url;
	t_list	*elements;
	t_list	*img_list = NULL;

	elements = site->elements;
	while (elements != NULL)
	{
		el = elements->content;
		if (*(el + 1) == 'i' && *(el + 2) == 'm'
				&& *(el + 3) == 'g' && isspace (*(el + 4)) != 0)
		{
			img_url = html_get_attr_value ("src", el);
			if (img_url == NULL || *img_url == '\0')
			{ elements = elements->next; continue ; }
			// relative url could also start with . .. ./
			if (img_url && *img_url == '/')
				url_resolve_absolute (site, &img_url);
			// if img is encoded "data:image..."
			//if (img_url && *img_url == 'h')
			ft_lstadd_back (&img_list, ft_lstnew ((void *) img_url));
			//write (1, img_url, strlen(img_url));
			//write (1, "\n", 1);
		}
		elements = elements->next;
	}
	return (img_list);
}
