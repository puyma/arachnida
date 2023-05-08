/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 18:02:38 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/05/08 13:56:21 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arachnida.h"
#include "libft.h"

#include <fcntl.h> /* open */
#include <stdio.h> /* fprintf */
#include <unistd.h> /* write */
#include <string.h> /* memcpy */
#include <ctype.h> /* isdigit */

#include <curl/curl.h>

typedef struct s_document
{
	char		*raw;
	char		*url;
	size_t		size;
	t_list		*elements;
}				t_document;

static int		ft_crawl(char *url, t_list **documents);
static int		ft_http_get(char *url, t_document **doc);
static size_t	c_write_callback(void *data, size_t size, 
					size_t nmemb, void *userdata);
static int		ft_new_document(t_document **document);
static int		ft_point_tags(t_document **document);
static int		ft_url_isvalid(char *url);
static int		ft_aredigits(char *str);
static int		ft_append_hrefs(t_document **document, t_list **url_cueue);

int	rflag = 0;
int	verbose = 0;

int	main(int argc, char **argv)
{
	int		c;
	char	*lvalue = NULL;
	t_list	*documents = NULL;
	int		depth_level = 1;
	
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
	if (ft_aredigits(lvalue) == 0)
	{ write(2, "invalid lvalue\n", 15); exit(3); }
	if (lvalue != NULL)
		depth_level = atoi(lvalue);
	if (! argv[optind] || ft_url_isvalid(argv[optind]) == -1)
	{ write(2, "missing or invalid url...\n", 26); exit (1); }
	t_list	*url_cueue = ft_lstnew((void *) argv[optind]);
	while (depth_level > 0)
	{
		while (url_cueue != NULL)
		{
			if (ft_crawl(argv[optind], &documents) == -1)
				return (1);
			t_document *d = documents->content;
			ft_point_tags(&d);
			ft_append_hrefs(&d, &url_cueue);
			url_cueue = url_cueue->next;
		}
		--depth_level;
	}
	return (0);
}

static int	ft_append_hrefs(t_document **document, t_list **url_cueue)
{
	char		*tag = NULL;
	t_document	*d = *document;
	t_list		*elements = NULL;
	t_list		*urls = *url_cueue;

	elements = d->elements;
	while (elements != NULL)
	{
		tag = elements->content;
		if (strncmp(tag, "<a ", 3) == 0)
		{
			while (*tag != '\0' && *tag != '>')
			{
				write(1, tag, 1);
				++tag;
			}
			write(1, "\n", 1);
		}
		elements = elements->next;
	}
	(void) urls;
	return (0);
}

static int	ft_aredigits(char *str)
{
	char	*s = str;

	while (s && *s != '\0')
	{
		if (isdigit(*s) == 0)
			return (0);
		++s;
	}
	return (1);
}

static int	ft_url_isvalid(char *url)
{
	if (url == NULL || *url == '\0' || *url == ' ')
		return (-1);
	return (0);
}

static int	ft_crawl(char *url, t_list **documents)
{
	t_document	*doc;

	ft_printf("crawling %s\n", url);
	if (ft_new_document(&doc) == -1)
	{ write(2, "error\n", 6); exit(2); }
	if (ft_http_get(url, &doc) != 0)
	{ write(2, "curl failed\n", 12); exit(4); }
	doc->url = url;
	*documents = ft_lstnew(doc);
	return (0);
}

static int	ft_point_tags(t_document **document)
{
	t_document	*d = *document;
	char		*html = d->raw;

	while (*html != '\0')
	{
		if (*html == '<')
		{
			if (*html != '\0' && *(html + 1) != '\0' && *(html + 1) != '/')
				ft_lstadd_back(&d->elements, ft_lstnew((void *) html));
		}
		++html;
	}
	return (0);
}

static int	ft_new_document(t_document **dst)
{
	t_document	*doc;
	
	doc = calloc(1, sizeof(t_document));
	if (doc == NULL)
	{ write(1, "no allocation\n", 14); exit(2); }
	doc->size = 0;
	doc->raw = NULL;
	doc->url = NULL;
	doc->elements = NULL;
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
