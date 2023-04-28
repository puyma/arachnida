/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 18:02:38 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/04/28 14:13:02 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arachnida.h"
#include "libft.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <fcntl.h>
#include <curl/curl.h>

typedef struct s_document
{
	char		*response;
	size_t		size;
	size_t		recursion_lvl;
}				t_document;

static int		ft_crawl(char *url, t_list **documents);
static int		ft_http_get(char *url, t_document *doc);
static size_t	c_write_callback(void *data, size_t size, 
					size_t nmemb, void *userdata);

// manager struct

int	rflag = 0;
int	vflag = 0;

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
			vflag = 1;
		else if (c == '?')
			return 1;
		else
			return 3;
	}
	if (argv[optind])
		ft_crawl(argv[optind], &documents);
	return (0);
}

static size_t c_write_callback(void *data, size_t size,
		size_t nmemb, void *userdata)
{
	char	*str = (char *) data;
	size_t	realsize;
	size_t	i;
	(void) userdata;

	realsize = size * nmemb;
	i = 0;
	while (str && i < nmemb)
	{
		if (*str != '\n' && *str != 9)
		{
			if (write(1, str, 1) == -1)
				return (0);
		}
		str++;
		i++;
	}
	return (realsize);
}

static int	ft_crawl(char *url, t_list **documents)
{
	(void) documents;

	printf("crawling %s\n", url);
	ft_http_get(url, NULL);
	return (0);
}


static int	ft_http_get(char *url, t_document *doc)
{
	CURL		*curl;
	CURLcode	res;
	(void) doc;

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
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *) NULL);
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
