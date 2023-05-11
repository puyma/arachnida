/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crawl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 11:13:37 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/05/11 13:28:47 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arachnida.h"

int
ft_crawl(char *url, t_site **site)
{
	ft_printf ("crawling: %s\n", url);
	*site = ft_new_site();
	if (site == NULL)
	{ write (2, "Error. mem\n", 11); return (1); }
	if (ft_http_get (url, site) != 0)
	{ return (1); }
	(*site)->url = url;
	(*site)->host = url; /* not implemented */
	return (0);
}
