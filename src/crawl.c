/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crawl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 11:13:37 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/05/15 12:23:38 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arachnida.h"

static int	point_tags (t_site **site);

int
crawl(char *url, t_site **site)
	// This function 
{
	ft_printf ("crawling: %s\n", url);

	*site = ft_new_site ();
	if (site == NULL) { return (1); }
	(*site)->url = url;
	(*site)->hostname = url_hostname(url);
	
	if (http_get (url, (void *) *site, NULL) != 0)
		return (1);
	
	if (point_tags (site) != 0) { return (3); }
	return (0);
}

static int
point_tags (t_site **site)
{
	char	*html;

	if (site == NULL || *site == NULL)
		exit (5);
	html = (*site)->raw_html;
	while (*html != '\0')
	{
		if (*html == '<')
		{
			if (*(html + 1) != '\0' && *(html + 1) != '/')
				ft_lstadd_back (&(*site)->elements,
						ft_lstnew ((void *) html));
		}
		++html;
	}
	return (0);
}
