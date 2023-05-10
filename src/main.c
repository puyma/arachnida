/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 18:02:38 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/05/10 13:02:13 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arachnida.h"
#include "libft.h"

#include <fcntl.h> /* open */
#include <stdio.h> /* fprintf */
#include <unistd.h> /* write */
#include <string.h> /* memcpy */
#include <ctype.h> /* isdigit */

#include <curl/curl.h> /* libcurl C API */

typedef struct s_document
{
	char		*raw;
	char		*url;
	size_t		size;
	t_list		*elements;
}				t_document;

typedef struct s_element
{
	char		*data;
	size_t		type;
}				t_element;

static int		ft_init(int argc, char **argv);
static int		ft_crawl (char *url, t_list **documents);
static int		ft_http_get (char *url, t_document **doc);
static int		ft_new_document (t_document **document);
static int		ft_point_tags (t_document **document);
static int		ft_url_isvalid (char *url);
static int		ft_aredigits (char *str);
static int		ft_append_anchors (t_document **document, 
					t_list **url_cueue);
static size_t	c_write_callback (void *data, size_t size,
					size_t nmemb, void *userdata);
static int		ft_url_isvisited (t_list **url_cueue, char *href);
static int		ft_get_attribute(const char *attribute, 
					char **html_element);

int	rflag = 0;
int	verbose = 0;
int	depth_level = 1;

	int
	main (int argc, char **argv)
	{
		char	*url = NULL;
		t_list	*documents = NULL;
		t_list	**url_cueue = calloc(depth_level + 1, sizeof(t_list *));

		if (ft_init(argc, argv)) { return (3); }
		int i = 0;
		url_cueue[i] = ft_lstnew ((void *) argv[optind]);
		while (i < depth_level)
		{
			if (url_cueue[i] == NULL)
				fprintf(stderr, "url_cueue[%d] is NULL\n", i);
			while (url_cueue[i] != NULL)
			{
				url = url_cueue[i]->content;
				if (ft_crawl (url, &documents) == -1)
					return (1);
				t_document *d = documents->content;
				ft_point_tags (&d);
				ft_append_anchors (&d, &url_cueue[i + 1]);
				url_cueue[i] = url_cueue[i]->next;
			}
			++i;
		}
		return (0);
	}

	static int
	ft_init(int argc, char **argv)
	{
		int		c = 0;
		char	*lvalue = NULL;

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
				return 1;
			else
				return 3;
		}
		if (ft_aredigits (lvalue) == 0)
		{
			write (2, "invalid lvalue\n", 15);
			return (1);
		}
		if (lvalue != NULL)
			depth_level = atoi (lvalue);
		if (! argv[optind] || ft_url_isvalid (argv[optind]) == -1)
		{
			write (2, "missing or invalid url...\n", 26);
			return (1);
		}
		return (0);
	}

	static int
	ft_append_anchors (t_document **document, t_list **url_cueue)
	{
		char		*el = NULL;
		char		*href = NULL;
		t_document	*d = *document;
		t_list		*elements = NULL;
		t_list		*urls = *url_cueue;
	
		elements = d->elements;
		while (elements != NULL)
		{
			el = elements->content;
			if (*(el + 1) == 'a' && isspace(*(el + 2)) != 0)
			{
				char *attr = "href";
				if (ft_get_attribute(attr, &el) == 0)
				{ fprintf(stderr, "attribute \"%s\" not found\n", attr); }
				href = strndup(el + 1, strchr(el + 1, *el) - el - 1);
				if (ft_url_isvisited(&urls, href) == 0 && *href != '#')
				{
					ft_lstadd_back(&urls, ft_lstnew((void *) href));
				}
				else
					free(href);
			}
			elements = elements->next;
		}
		return (0);
	}

	static int
	ft_get_attribute(const char *attr, char **html_element)
	{
		char	*el = *html_element;
		char	*attribute = ft_strjoin(attr, "=");
	
		while (*el != '\0')
		{
			if (*el == *attr && strncmp(el, attribute, strlen(attribute)) == 0)
			{
				el += strlen(attribute);
				if (*el == 34 || *el == 39)
				{
					*html_element = el;
					return (1);
				}
				else
					return (0);
			}
			++el;
		}
		return (0);
	}

	static int
	ft_url_isvisited (t_list **url_cueue, char *href)
	{
		t_list	*urls = *url_cueue;
		int		delta_len = 0;
		int		strcmp_diff = 0;
	
		while (urls != NULL)
		{
			strcmp_diff = strcmp (urls->content, href);
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

	static int
	ft_aredigits (char *str)
	{
		char	*s = str;
	
		while (s && *s != '\0')
		{
			if (isdigit (*s) == 0)
				return (0);
			++s;
		}
		return (1);
	}

	static int
	ft_url_isvalid (char *url)
	{
		if (url == NULL || *url == '\0' || *url == ' ')
			return (-1);
		return (0);
	}

	static int
	ft_crawl (char *url, t_list **documents)
	{
		t_document	*doc = NULL;

		ft_printf ("crawling %s\n", url);
		if (ft_new_document (&doc) == -1)
		{ write (2, "error\n", 6); exit (2); }
		if (ft_http_get (url, &doc) != 0)
		{ return (1); }
		doc->url = url;
		*documents = ft_lstnew (doc);
		return (0);
	}

	static int
	ft_point_tags (t_document **document)
	{
		t_document	*d = *document;
		char		*html = d->raw;
	
		while (*html != '\0')
		{
			if (*html == '<')
			{
				if (*html != '\0' && *(html + 1) != '\0' && *(html + 1) != '/')
					ft_lstadd_back (&d->elements, ft_lstnew ((void *) html));
			}
			++html;
		}
		return (0);
	}
	
	static int
	ft_new_document (t_document **dst)
	{
		t_document	*doc;
			
		doc = calloc(1, sizeof (t_document));
		if (doc == NULL)
		{ write (1, "no allocation\n", 14); exit (2); }
		doc->size = 0;
		doc->raw = NULL;
		doc->url = NULL;
			doc->elements = NULL;
			*dst = doc;
		return (0);
	}

static int
ft_http_get (char *url, t_document **doc)
{
	CURL		*curl;
	CURLcode	res;

	curl_global_init (CURL_GLOBAL_DEFAULT);
	curl = curl_easy_init ();
	if (curl)
	{
		curl_easy_setopt (curl, CURLOPT_URL, url);
		curl_easy_setopt (curl, CURLOPT_USERAGENT, "curl/7.64.1");
		curl_easy_setopt (curl, CURLOPT_USE_SSL, (long)CURLUSESSL_ALL);
		curl_easy_setopt (curl, CURLOPT_SSL_VERIFYPEER, 0L);
		curl_easy_setopt (curl, CURLOPT_SSL_VERIFYHOST, 0L);
		curl_easy_setopt (curl, CURLOPT_FOLLOWLOCATION, 1L);
		curl_easy_setopt (curl, CURLOPT_VERBOSE, 0L);
		curl_easy_setopt (curl, CURLOPT_SSLVERSION, CURL_SSLVERSION_TLSv1_2);
		curl_easy_setopt (curl, CURLOPT_SSL_ENABLE_ALPN, 1L);
		curl_easy_setopt (curl, CURLOPT_HTTP_VERSION,
				CURL_HTTP_VERSION_NONE);
		curl_easy_setopt (curl, CURLOPT_WRITEFUNCTION, &c_write_callback);
		curl_easy_setopt (curl, CURLOPT_WRITEDATA, (void *) *doc);
		curl_easy_setopt (curl, CURLOPT_FAILONERROR, 0L);
		curl_easy_setopt (curl, CURLOPT_EXPECT_100_TIMEOUT_MS, 3000L);
		curl_easy_setopt (curl, CURLOPT_TIMEOUT, 20L);
		curl_easy_setopt (curl, CURLOPT_SERVER_RESPONSE_TIMEOUT, 22L);
		res = curl_easy_perform (curl);
		if (res != CURLE_OK)
		{
			fprintf (stderr, "curl_easy_perform() failed %s\n",
					curl_easy_strerror (res));
			return (1);
		}
		curl_easy_cleanup (curl);
	}
	curl_global_cleanup ();
	return (0);
}

static size_t
c_write_callback (void *data, size_t size, size_t nmemb, void *userdata)
{
	char		*buffer = NULL;
	size_t		realsize = size * nmemb;
t_document	*doc = (t_document *) userdata;
	
	buffer = realloc (doc->raw, doc->size + realsize + 1);
	if (buffer == NULL)
	{
	fprintf (stderr, "not enough memory (realloc returned NULL)\n");
		return (0);
	}
	doc->raw = buffer;
	memcpy (&(doc->raw[doc->size]), data, realsize);
doc->size += realsize;
	doc->raw[doc->size] = '\0';
	return (realsize);
}
