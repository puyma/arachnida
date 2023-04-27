/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 18:02:38 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/04/27 19:51:02 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arachnida.h"
#include "libft.h"

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <curl/curl.h>

static int	ft_crawl(char *url, int depth_level);
static int	ft_curl_fd(char *url, int fd);
static int	ft_extract_urls(int fd);

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
	int	fd[2];
	int	err;
	int	pid;

	err = pipe(fd);
	if (err == -1)
		return (2);
	pid = fork();
	if (pid == -1)
		return (3);
	if (pid == 0)
	{
		printf("crawling %s\n", url);
		close(fd[0]);
		ft_curl_fd(url, fd[1]);
	}
	else
	{
		close(fd[1]);
		wait(NULL);
		ft_extract_urls(fd[0]);
		close(fd[0]);
	}
	return (0);
	(void) depth_level;
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
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, fdopen(fd, "w"));
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
