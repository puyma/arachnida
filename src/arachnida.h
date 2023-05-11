/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arachnida.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 19:37:20 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/05/11 19:36:19 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARACHNIDA_H
# define ARACHNIDA_H

# include "libft.h"

# include <string.h> /* memcpy */
# include <fcntl.h> /* open */
# include <stdio.h> /* fprintf, printf */
# include <unistd.h> /* write */
# include <ctype.h> /* isdigit */

# include <curl/curl.h> /* libcurl C API */

typedef struct s_site
{
	char		*url;
	char		*host;
	char		*raw_html;
	size_t		size;
	t_list		*elements;
}				t_site;

extern int	rflag;
extern int	verbose;
extern int	depth_level;

int		ft_crawl (char *url, t_site **site);
int		ft_http_get (char *url, t_site **site);

int		ft_point_tags (t_site **site);
int		ft_append_anchors (t_site *site, t_list **urls, int n);

int		ft_get_attribute (const char *attr, char **html_element);
int		ft_http_get_images (t_site *site);

t_site	*ft_new_site(void);
int		ft_aredigits (char *str);

int		ft_url_isvalid (char *url);
int		ft_url_isvisited (char *href, t_list **url_cueue, int n);
char	*ft_url_hostname (char *url);

#endif
