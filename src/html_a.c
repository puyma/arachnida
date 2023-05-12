/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   html_a.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 12:22:55 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/05/12 13:26:20 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arachnida.h"

int
append_anchors (t_site *site, t_list **cueue_arr, int n)
{
	char	*el;
	char	*value;
	t_list	*elements;

	elements = site->elements;
	while (elements != NULL)
	{
		el = elements->content;
		if (*(el + 1) == 'a' && isspace (*(el + 2)) != 0)
		{
			value = html_get_attr_value("href", el);
			if (*value == '/')
				url_resolve_absolute (site, &value);
			if (*value != 'h')
			{ free (value); exit (7); }
			cueue_url (value, cueue_arr, n);
		}
		elements = elements->next;
	}
	return (0);
}
