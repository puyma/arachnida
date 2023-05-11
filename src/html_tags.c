/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   html_tags.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 11:46:47 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/05/11 13:17:45 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arachnida.h"

int
ft_point_tags (t_site **site)
{
	char	*html;

	if (site == NULL || *site == NULL)
	{ write (2, "ft_point_tags() received NULL\n", 30); exit (5); }

	html = (*site)->raw_html;
	while (*html != '\0')
	{
		if (*html == '<')
		{
			if (*html != '\0' && *(html + 1) != '\0' && *(html + 1) != '/')
				ft_lstadd_back (&(*site)->elements, 
						ft_lstnew ((void *) html));
		}
		++html;
	}
	return (0);
}

int
ft_append_anchors (t_site *site, t_list **cueue_arr)
{
	char	*el;
	char	*href;
	t_list	*elements;
	//t_list	*urls = *cueue_arr;

	elements = site->elements;
	while (elements != NULL)
	{
		el = elements->content;
		if (*(el + 1) == 'a' && isspace (*(el + 2)) != 0)
		{
			char *attr = "href";
			if (ft_get_attribute (attr, &el) == 0)
			{ fprintf (stderr, "attribute \"%s\" not found\n", attr); exit (2); }
			href = strndup (el + 1, strchr (el + 1, *el) - el - 1);
			if (*href != '#' && *href != '/' && *href == 'h') //&& ft_url_isvisited (href, urls) == 0)
			{
				ft_lstadd_front (cueue_arr, ft_lstnew ((void *) href));
			}
		}
		elements = elements->next;
	}
	return (0);
}
