/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 18:02:38 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/04/27 23:33:51 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arachnida.h"
#include "libft.h"

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <curl/curl.h>

static int		ft_crawl(char *url, int depth_level);
static int		ft_curl_fd(char *url, int fd);
static int		ft_extract_urls(int fd);
static size_t	write_callback(char *ptr, size_t size, 
					size_t nmemb, void *userdata);

int	main(int argc, char **argv)
{
	//getopt();
	
	if (argc == 2 && argv[1])
		ft_crawl(argv[1], -1);
	return (0);
	(void) argc; (void) argv;
}

static int	ft_crawl(char *url, int depth_level)
{
	printf("crawling %s\n", url);
	ft_curl_fd(url, 0);
	return (0);
	(void) depth_level;
	(void) ft_extract_urls;
}

static size_t write_callback(char *ptr, size_t size, 
		size_t nmemb, void *userdata)
{
	write(1, "\n\noo\n\n", 6);
	write(1, ptr, nmemb);
	(void) size; (void) nmemb; (void) userdata;
	return (0);
}

static int	ft_extract_urls(int fd)
{
	char s[80];

	while (read(fd, s, 80) > 0)
		printf("%s\n", s);
	return (0);
}

static int	ft_curl_fd(char *url, int fd)
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
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 1L);
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 0L);
		curl_easy_setopt(curl, CURLOPT_SSLVERSION, CURL_SSLVERSION_TLSv1_2);
		curl_easy_setopt(curl, CURLOPT_SSL_ENABLE_ALPN, 1L);
		curl_easy_setopt(curl, CURLOPT_HTTP_VERSION, (long)CURL_HTTP_VERSION_1_1);
		//curl_easy_setopt(curl, CURLOPT_WRITEDATA, fdopen(fd, "w"));
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, (void *)NULL);
		(void) write_callback;
		curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1L);
		curl_easy_setopt(curl, CURLOPT_EXPECT_100_TIMEOUT_MS, 3000L);
		curl_easy_setopt(curl, CURLOPT_TIMEOUT, 20L);
		curl_easy_setopt(curl, CURLOPT_SERVER_RESPONSE_TIMEOUT, 22L);
		curl_easy_setopt(curl, CURLOPT_COOKIEJAR, "/tmp/cookies.txt");
		printf("writing to fd %d\n", fd);
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
