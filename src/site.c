/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   site.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 11:21:18 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/05/12 13:22:56 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arachnida.h"

t_site *
ft_new_site(void)
{
	t_site	*site;

	site = (t_site *) calloc (1, sizeof(t_site));
	if (site == NULL)
		return (NULL);
	site->url = NULL;
	site->hostname = NULL;
	site->raw_html = NULL;
	site->size = 0;
	site->elements = NULL;
	return (site);
}
