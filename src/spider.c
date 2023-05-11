/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spider.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:23:46 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/05/11 12:13:21 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arachnida.h"

static int		ft_init (int argc, char **argv);
static t_list	**ft_init_cueue (void);

int	rflag = 0;
int	verbose = 0;
int	depth_level = 3;

int	main(int argc, char **argv)
{
	int 		i;
	char		*url;
	t_site		*site = NULL;
	t_list		*url_cueue;
	t_list 		**cueue_arr;

	if (ft_init(argc, argv) != 0)
	{ write(2, "ft_init failed\n", 15); return (1); }

	cueue_arr = ft_init_cueue();
	if (cueue_arr == NULL)
	{ write(2, "ft_init_cueue failed\n", 21); return (2); }

	/* set first url (user input) */
	url = argv[optind];
	cueue_arr[0] = ft_lstnew((void *) url);

	i = 0;
	while (i < depth_level)
	{
		url_cueue = cueue_arr[i];
		while (url_cueue != NULL)
		{
			url = url_cueue->content;
			if (ft_crawl (url, &site))
			{ write (2, "ft_crawl failed\n", 16); return (3); }

			ft_point_tags (&site);

			if (i < depth_level - 1)
			{
				ft_append_anchors (site, cueue_arr[i + 1]);
				//cueue_arr[i + 1] = ft_lstnew((void *) NULL);
			}

			printf("%d: ...%s\n", i, url_cueue->content);
			//ft_download_images ();
			//free(site);
			//site = NULL;
			url_cueue = url_cueue->next;
		}
		++i;
	}
	return (0);
}

static int
ft_init (int argc, char **argv)
{
	int		c = 0;
	char*lvalue = NULL;

	/* set options */
	while ((c = getopt (argc, argv, "rl:v")) != -1)
	{
		if (c == 'r')
			rflag = 1;
		else if (c == 'l')
			lvalue = optarg;
		else if (c == 'v')
			verbose = 1;
		else if (c == '?')
			return (1);
		else
			return (3);
	}
	
	if (ft_aredigits (lvalue) == 0)
	{ write(2, "invalid lvalue\n", 15); return (1); }

	if (lvalue != NULL)
		depth_level = atoi (lvalue);

	if (! argv[optind] || ft_url_isvalid (argv[optind]) == -1)
	{ write(2, "missing or invalid url...\n", 26); return (1); }

	return (0);
}

static t_list **
ft_init_cueue(void)
{
	int	i = 0;
	t_list	**list_arr;

	list_arr = (t_list **) calloc(depth_level, sizeof(t_list *));
	while (++i < depth_level)
	{
		list_arr[i] = (t_list *) calloc(1, sizeof(t_list));
		list_arr[i] = ft_lstnew((void *) NULL);
		i++;
	}
	return (list_arr);
}
