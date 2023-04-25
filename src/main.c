/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:08:21 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/04/25 19:16:37 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h> /* isdigit */
#include <stdio.h> /* fdopen, printf */
#include <stdlib.h>
#include <string.h> /* strlen, strncmp */
#include <unistd.h> /* getopt, write */

/* curl stuff */
#include <curl/curl.h> /* curl */
#include <curl/mprintf.h> /* ? */

/* arachnida stuff */
#include "arachnida.h"

static int	url_isvalid(char *url);
static int	crawl(char *start_url, int fd, int level);

int	main(int argc, char **argv)
{
	int		c = 0;
	int		rflag = 0;
	char	*lvalue = NULL;
	int		pipefd[2];

	while (c != -1)
	{
		c = getopt(argc, argv, "+rl:pS");
		if (c == 'r')
			rflag = 1;
		else if (c == 'l')
			lvalue = optarg;
		else if (c == '?')
		{
			fprintf(stderr, "usage: %s [-rpS | -l level] url\n", argv[0]);
			exit (EXIT_FAILURE);
		}
	}
	if (pipe(pipefd) == -1)
		exit (EXIT_FAILURE);
	if (url_isvalid(argv[optind])) // and lvalue isdigit(s)
		crawl(argv[optind], pipefd[1], -1);
	// img parse, read from pipefd[0]
	int i = 1;
	char s[10];
	while (i != 0)	
	{
		i = read(pipefd[0], s, 10);
		printf("-> %s\n", s);
	}
	return (0);
}

static int	crawl(char *start_url, int fd, int level)
{
	CURL		*curl;
	CURLcode	res;

	curl = curl_easy_init();
	if (curl)
	{
    	curl_easy_setopt(curl, CURLOPT_URL, start_url);
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (platform; rv:geckoversion) Gecko/geckotrail Firefox/firefoxversion");
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, fdopen(fd, "w"));
		res = curl_easy_perform(curl);
		if (res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
		curl_easy_cleanup(curl);
	}
	//close(fd);
	return 0;
	(void) level;
}

static int	url_isvalid(char *url)
{
	if (url == NULL || *url == '\0')
		return (0);
	if (strncmp(url, "https://", 8) == 0
		|| strncmp(url, "http://", 7) == 0)
		return (1);
	return (0);
}
