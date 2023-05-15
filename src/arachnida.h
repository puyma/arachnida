/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arachnida.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 19:37:20 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/05/15 16:42:16 by mpuig-ma         ###   ########.fr       */
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
# include <sys/stat.h> /* mkdir */
# include <errno.h>

# include <curl/curl.h> /* libcurl C API */

# define RED		"\033[0;31m"
# define NOSTYLE	"\033[0m"

typedef struct s_site
{
	char		*url;
	char		*hostname;
	char		*raw_html;
	size_t		size;
	t_list		*elements;
}				t_site;

extern int	rflag;
extern int	verbose;
extern int	depth_level;
extern char	*path;

int		crawl (char *url, t_site **site);
int		http_get (char *url, void *userdata, FILE *file);
int		http_download(char *url, char *filename);
int		http_download_lst (t_list *url_list);

char	*html_get_attr_value (char *attr, char *html_element);
t_list	*html_get_attr_values (char *attr, char *html_element);
char	*html_get_attr (const char *attr, char *html_element);

t_list	*html_get_imgs (t_site *site);
t_list	*html_get_pictures (t_site *site);
t_list	*html_get_svgs (t_site *site);
int		html_save_snippets (t_list *lst, char *ext);

int		url_isvalid (char *url);
int		url_isvisited (char *href, t_list **url_cueue, int n);
int		url_resolve_absolute (t_site *site, char **url);
char	*url_path_to_file (char *url);
char	*url_hostname (char *url);
int		cueue_url (char *url, t_list **url_cueue, int n);

int		append_anchors (t_site *site, t_list **urls, int n);

t_site	*ft_new_site (void);
int		ft_aredigits (char *str);

#endif
