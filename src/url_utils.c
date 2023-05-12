/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   url_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 12:08:33 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/05/12 11:14:26 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arachnida.h"

int
url_isvalid (char *url)
/* returns zero if invalid */
{
	if (url == NULL || *url == '\0' || isspace(*url) != 0)
		return (0);
	return (1);
}

int
url_isvisited (char *href, t_list **url_cueue, int n)
{
	t_list	*urls;
	size_t	len = 0;
	size_t	url_len = 0;
	size_t	href_len = 0;
	size_t	delta_len = 0;
	int		strncmp_diff = 0;
	int		c = '\0';

	while (n >= 0)
	{
		urls = url_cueue[n];
		while (urls != NULL)
		{
			if (urls->content == NULL)
				break ;

			url_len = strlen(urls->content);
			href_len = strlen(href);

			if (href_len >= url_len)
			{
				len = href_len;
				delta_len = href_len - url_len;
				c = href[len - 1];
			}
			else
			{
				len = url_len;
				delta_len = url_len - href_len;
				char *s = urls->content;
				c = s[len - 1];
			}

			strncmp_diff = strncmp (href, urls->content, len);
			if (strncmp_diff == 0)
				return (1);
					
			if (strncmp_diff < 0)
				strncmp_diff *= -1;

			if (delta_len == 1 && strncmp_diff == 47)
				return (1);
			else if (delta_len == 1 && strncmp_diff == 1 && c == '/')
			   return (1);	
			urls = urls->next;
		}
		--n;
	}
	return (0);
}

char *
url_hostname(char *url)
{
	char	*hostname;
	char	*colon;

	colon = strchr (url, ':') + 3;
	hostname = strndup(url, strchr(colon, '/') - url);
	return (hostname);
}
