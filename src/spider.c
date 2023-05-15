/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spider.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:23:46 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/05/15 16:42:54 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arachnida.h"

static int		ft_init (int argc, char **argv);
static t_list	**ft_init_cueue (char *first_item);

int		rflag = 0;
int		verbose = 0;
int		depth_level = 5;
char	*path = "./data/";

int
main (int argc, char **argv)
{
	int 		i;
	char		*url;
	t_site		*site = NULL;
	t_list		*url_cueue;
	t_list 		**cueue_arr;
	t_list		*lst;

	// Initializes program options: 
	// verbose, depth level,
	// path !? and recursive mode !?
	if (ft_init (argc, argv) != 0)
	{ write (2, "ft_init failed\n", 15); return (1); }

	// Set the first -and only- url 
	// to the first list in `cueue_arr`.
	// It's inputed by the user.
	cueue_arr = ft_init_cueue (argv[optind]);
	if (cueue_arr == NULL)
	{ write (2, "ft_init_cueue failed\n", 21); return (2); }

	i = 0;
	while (i < depth_level)
	{
		url_cueue = cueue_arr[i];
		while (url_cueue != NULL)
		{
			url = url_cueue->content;

			// Create t_site with `url`, `hostname` and `raw_html`.
			if (crawl (url, &site)) { url_cueue = url_cueue->next; continue ; }
			else { ft_printf("└ OK\n"); }

			// Find links in `site->raw_html` 
			// and add them to `cueue_arr` (t_list).
			if (i < depth_level - 1)
			{ append_anchors (site, cueue_arr, i + 1); }

			// Get list of `images` in a `site`.
			// Then, download every item in (t_list).
			// Support for base64 encoded images is not implemented as of now.
			
			// <img>
			lst = html_get_imgs(site);
			http_download_lst(lst);
			ft_lstclear(&lst, &free);
	
			// <picture>
			lst = html_get_pictures(site);
			http_download_lst(lst);
			ft_lstclear(&lst, &free);
		
			// <svg>
			lst = html_get_svgs(site);
			html_save_snippets(lst, ".svg");
			ft_lstclear(&lst, &free);

			url_cueue = url_cueue->next;
		}
		++i;
	}
	// free cueue_arr ...
	return (0);
}

static int
ft_init (int argc, char **argv)
{
	int		c = 0;
	char	*lvalue = NULL;
	char	*pvalue = NULL;

	/* set options */
	while ((c = getopt (argc, argv, "rl:vp:")) != -1)
	{
		if (c == 'r')
			rflag = 1;
		else if (c == 'l')
			lvalue = optarg;
		else if (c == 'v')
			verbose = 1;
		else if (c == 'p')
			pvalue = optarg;
		else if (c == '?')
			return (1);
		else
			return (3);
	}
	
	if (ft_aredigits (lvalue) == 0)
	{
		write (2, "invalid lvalue\n", 15);
		return (1);
	}

	if (lvalue != NULL)
	{
		depth_level = atoi (lvalue);
	}

	if (! argv[optind] || url_isvalid (argv[optind]) == -1)
	{
		write(2, "missing or invalid url...\n", 26);
		return (1);
	}

	// Make directory where files will be downloaded.
	if (mkdir (path, 0777) != 0)
	{
		// As the folder "data" may already exist, 
		// EEXIST won't be considered an error.
		if (errno != EEXIST)
		{
			fprintf(stderr, "%s\n", strerror(errno));
			exit (errno);
		}
	}
	return (0);
}

static t_list **
ft_init_cueue (char *first_item)
{
	t_list	**list_arr;

	list_arr = (t_list **) calloc (depth_level + 1, sizeof (t_list *));
	list_arr[0] = ft_lstnew ((void *) first_item);
	return (list_arr);
}
