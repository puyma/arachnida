/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   url_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 12:08:33 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/05/16 12:58:35 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arachnida.h"

int
url_isvalid (char *url)
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

int
cueue_url (char *url, t_list **url_cueue, int n)
{
	if (url_isvisited (url, url_cueue, n) == 0)
		ft_lstadd_back (&url_cueue[n], ft_lstnew ((void *) url));
	else
		return (1);
	return (0);
}

int
url_resolve_absolute (t_site *site, char **url)
	// falta comprovar si host acaba amb / o directament amb something/
	// inversa de htts://; if not schema
{
	char	*relative_url;
	char	*absolute_url;
	
	relative_url = *url;
	absolute_url = ft_strjoin(site->hostname, relative_url);
	if (relative_url)
		free (relative_url);
	*url = absolute_url;
	return (0);
}

char *
url_path_to_file (char *url)
{
	char	*file;
	char	*start;
	char	*end;

	start = strrchr (url, '/') + 1;
	end = strchr (url, '&');
	// 2f or 2F == '/'
	file = strndup (start, end - start);
	return (file);
}

int
url_decode (char **url)
{
	char	*s;
	char	*new_url;
	size_t	amp_counter = 0;
	size_t	total_len;
	size_t	i = 0;

	s = strstr (*url, "&amp;");
	if (s == NULL)
		return (0);
	while (s && *s != '\0')
	{
		++amp_counter;
		++s;
		s = strstr (s, "&amp;");
	}
	
	total_len = strlen (*url) - (amp_counter * 4);
	new_url = (char *) calloc (total_len, sizeof (char));
	if (new_url == NULL) { exit (78); }

	s = *url;
	while (i < total_len - 1)
	{
		if (s && s == strstr(s, "&amp;"))
		{
			new_url[i] = *s;
			s += 5;
		}
		else
		{
			new_url[i] = *s;
			++s;
		}
		++i;
	}
	*url = new_url;
	return (0);
}
