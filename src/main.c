/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 18:02:38 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/05/04 22:59:58 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arachnida.h"
#include "libft.h"

#include <fcntl.h> /* open */
#include <stdio.h> /* fprintf */
#include <unistd.h> /* write */
#include <string.h> /* memcpy */

#include <curl/curl.h>

typedef struct s_document
{
	char		*raw;
	size_t		size;
	size_t		recursion_lvl;
	t_list		*el_meta;
	t_list		*el_link;
	t_list		*el_img;
	t_list		*el_a;
}				t_document;

static int		ft_crawl(char *url, t_list **documents);
static int		ft_http_get(char *url, t_document **doc);
static size_t	c_write_callback(void *data, size_t size, 
					size_t nmemb, void *userdata);
static int		ft_new_document(t_document **document);
static int		ft_find_images(t_document *document);

// manager struct

int	rflag = 0;
int	verbose = 0;

int	main(int argc, char **argv)
{
	int		c;
	char	*lvalue = NULL;
	t_list	*documents = NULL;
	
	while ((c = getopt(argc, argv, "rl:v")) != -1)
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
	if (argv[optind])
		if (ft_crawl(argv[optind], &documents) == -1)
			return (1);
	t_document *d = documents->content;
	ft_find_images(d);
	return (0);
}

static int	ft_find_images(t_document *document)
{
	char			*html = document->raw;
	//char			*tag = "meta";
	//const size_t	tag_len = strlen(tag);
	char			*html_cp = NULL;
	(void) html_cp;

	while (*html != '\0')
	{
		if (*html == '<')
		{
			++html;
			if (strncmp("meta", html, 4) == 0)
			{
				t_list *l = ft_lstnew((void *) html);
				ft_lstadd_front(&document->el_meta, l);
			}
			/*
			{
				html_cp = html;
				while (*html_cp != '>' && *html_cp != '\0')
					write(1, html_cp++, 1);
				write(1, "\n", 1);
			}
			*/
			/*
			else if (strncmp("link", html, 4) == 0)
			{
				html_cp = html;
				while (*html_cp != '>' && *html_cp != '\0')
					write(1, html_cp++, 1);
				write(1, "\n", 1);
			}
			else if (strncmp("a ", html, 2) == 0)
			{
				html_cp = html;
				while (*html_cp != '>' && *html_cp != '\0')
					write(1, html_cp++, 1);
				write(1, "\n", 1);
			}
			else if (strncmp("img", html, 3) == 0)
			{
				html_cp = html;
				while (*html_cp != '>' && *html_cp != '\0')
					write(1, html_cp++, 1);
				write(1, "\n", 1);
			}
			else if (strncmp("svg", html, 3) == 0)
			{
				html_cp = html;
				while (*html_cp != '\0')
				{
					write(1, html_cp++, 1);
					if (*html_cp == '<')
					{
						if (strncmp("</svg>", html_cp, 6) == 0)
							break ;
					}
				}
				write(1, "\n", 1);
			}
			*/
		}
		++html;
	}
	return (0);
}

static int	ft_crawl(char *url, t_list **documents)
{
	t_document	*doc;

	ft_printf("crawling %s\n", url);
	ft_new_document(&doc);
	ft_http_get(url, &doc);
	*documents = ft_lstnew(doc);
	return (0);
}

static int	ft_new_document(t_document **dst)
{
	t_document	*doc;
	
	doc = calloc(1, sizeof(doc));
	if (doc == NULL)
		return (1);
	doc->size = 0;
	doc->raw = NULL;
	doc->el_meta = NULL;
	*dst = doc;
	return (0);
}

static int	ft_http_get(char *url, t_document **doc)
{
	CURL		*curl;
	CURLcode	res;

	curl_global_init(CURL_GLOBAL_DEFAULT);
	curl = curl_easy_init();
	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_USERAGENT, "curl/7.64.1");
		curl_easy_setopt(curl, CURLOPT_USE_SSL, (long)CURLUSESSL_ALL);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 0L);
		curl_easy_setopt(curl, CURLOPT_SSLVERSION, CURL_SSLVERSION_TLSv1_2);
		curl_easy_setopt(curl, CURLOPT_SSL_ENABLE_ALPN, 1L);
		curl_easy_setopt(curl, CURLOPT_HTTP_VERSION,
				CURL_HTTP_VERSION_2_PRIOR_KNOWLEDGE);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &c_write_callback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *) *doc);
		curl_easy_setopt(curl, CURLOPT_FAILONERROR, 0L);
		curl_easy_setopt(curl, CURLOPT_EXPECT_100_TIMEOUT_MS, 3000L);
		curl_easy_setopt(curl, CURLOPT_TIMEOUT, 20L);
		curl_easy_setopt(curl, CURLOPT_SERVER_RESPONSE_TIMEOUT, 22L);
		curl_easy_setopt(curl, CURLOPT_COOKIEJAR, "/tmp/cookies.txt");
		res = curl_easy_perform(curl);
		if (res != CURLE_OK)
		{
			fprintf(stderr, "curl_easy_perform() failed %s\n",
					curl_easy_strerror(res));
			return (1);
		}
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
	return (0);
}

static size_t c_write_callback(void *data, size_t size,
		size_t nmemb, void *userdata)
{
	char		*buffer = NULL;
	size_t		realsize = size * nmemb;
	t_document	*doc = (t_document *) userdata;

	buffer = realloc(doc->raw, doc->size + realsize + 1);
	if (buffer == NULL)
	{
		fprintf(stderr, "not enough memory (realloc returned NULL)\n");
		return (0);
	}
	doc->raw = buffer;
	memcpy(&(doc->raw[doc->size]), data, realsize);
	doc->size += realsize;
	doc->raw[doc->size] = '\0';
	return (realsize);
}
