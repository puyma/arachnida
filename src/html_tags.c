/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   html_tags.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 11:46:47 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/05/12 11:44:35 by mpuig-ma         ###   ########.fr       */
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
ft_append_anchors (t_site *site, t_list **cueue_arr, int n)
{
	char	*el;
	char	*href;
	char	*hostname;
	t_list	*elements;

	elements = site->elements;
	while (elements != NULL)
	{
		el = elements->content;
		if (*(el + 1) == 'a' && isspace (*(el + 2)) != 0)
		{
			char *attr = "href";
			el = html_get_attribute (attr, el);
			if (el == NULL)
			{
				fprintf (stderr, "attribute \"%s\" not found\n", attr);
				return (2);
			}
			href = strndup (el + 1, strchr (el + 1, *el) - el - 1);
			if (*href == 'h' && url_isvisited (href, cueue_arr, n + 1) == 0)
				ft_lstadd_back (&cueue_arr[n + 1], 
						ft_lstnew ((void *) href));
			else if (*href == '/')
			{
				hostname = url_hostname(site->url);
				href = ft_strjoin(hostname, href);
				if (url_isvisited (href, cueue_arr, n + 1) == 0)
					ft_lstadd_back (&cueue_arr[n + 1], 
							ft_lstnew ((void *) href));
			}
		}
		elements = elements->next;
	}
	return (0);
}
