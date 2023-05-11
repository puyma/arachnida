/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   url_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 12:08:33 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/05/11 13:20:52 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arachnida.h"

int
ft_url_isvalid (char *url)
/* returns zero if invalid */
{
	if (url == NULL || *url == '\0' || isspace(*url) != 0)
		return (0);
	return (1);
}

int
ft_url_isvisited (char *href, t_list *url_cueue)
{
	t_list	*urls; urls = url_cueue;
	int		delta_len = 0;
	int		strcmp_diff = 0;

	while (urls != NULL)
	{
		strcmp_diff = strncmp (urls->content, href, strlen(href));
		if (strcmp_diff == 0)
			return (1);
		delta_len = strlen(urls->content) - strlen(href);
		if (strcmp_diff < 0)
			strcmp_diff *= -1;
		else if ((delta_len == -1 || delta_len == 1) && strcmp_diff == 47)
			return (1);
		urls = urls->next;
	}
	return (0);
}
