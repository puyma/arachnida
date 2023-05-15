/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   html_svg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 12:26:57 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/05/15 16:29:17 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arachnida.h"

t_list *
html_get_svgs (t_site *site)
{
	char	*el;
	char	*svg;
	t_list	*elements;
	t_list	*svg_lst = NULL;
	size_t	n_depth = 0;

	char	*start = NULL;
	char	*end = NULL;

	if (site == NULL)
		return (NULL);

	elements = site->elements;
	while (elements != NULL)
	{
		el = elements->content;
		if (strncmp(el, "<svg ", strlen("<svg ")) == 0)
		{
			start = el;
			end = start;
			while (*end != '\0')
			{
				if (strncmp(end + 1, "<svg ", strlen("<svg ")) == 0)
					++n_depth;
				else if (n_depth != 0 && strncmp(end, "</svg>", strlen("</svg>")) == 0)
					--n_depth;
				if (strncmp(end, "</svg>", strlen("</svg>")) == 0)
					break ;
				++end;
			}
			if (start != NULL && end != NULL)
			{
				svg = strndup (start, end - start + strlen("</svg>"));
				ft_lstadd_back (&svg_lst, ft_lstnew ((void *) svg));
				start = NULL;
				end = NULL;
			}
		}
		elements = elements->next;
	}
	return (svg_lst);
}

/*
t_list *
html_get_svgs (t_site *site)
{
	char	*el;
	char	*svg;
	t_list	*elements;
	t_list	*svg_lst = NULL;

	if (site == NULL)
		return (NULL);

	elements = site->elements;
	while (elements != NULL)
	{
		el = elements->content;
		if (*(el + 1) == 's' && *(el + 2) == 'v'
				&& *(el + 3) == 'g' && isspace (*(el + 4)) != 0)
		{
			// consider <svg><svg></svg></svg>
			svg = NULL; // html_get_attr_value NOT OK FOR THIS CASE
			if (svg == NULL || *svg == '\0')
			{ elements = elements->next; continue; }
			// ft_lstadd_back (*svg_lst, ft_lstnew ((void *) svg));
		}
		elements = elements->next;
	}

	svg_lst = NULL;
	return (svg_lst);
}
*/
