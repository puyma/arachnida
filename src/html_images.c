/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   html_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 10:43:12 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/05/12 13:34:54 by mpuig-ma         ###   ########.fr       */
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
			// relative url could also start with . .. ./
			if (*img_url == '/')
				url_resolve_absolute (site, &img_url);
			// else if img is encoded "data:image..."
			// ();
			write (1, img_url, 10);
			write (1, "\n", 1);
		}
		elements = elements->next;
	}
	return (img_list);
}
