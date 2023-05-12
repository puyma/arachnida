/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   http.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 11:31:21 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/05/12 11:26:49 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arachnida.h"

static size_t	c_write_callback (void *data, size_t size, 
					size_t nmemb, void *userdata);
static size_t	c_writefd_callback (void *data, size_t size, 
					size_t nmemb, void *userdata);

// change ft_hht_get as base function, http_download passes url, userdata pointer and pointer to function callback.
int
http_get(char *url, void *userdata, 
		size_t (*func)(void *data, size_t size, size_t nmemb, void *userdata))
{
	CURL		*curl;
	CURLcode	res;

	if (func == NULL)
		func = &c_write_callback;
	curl_global_init (CURL_GLOBAL_DEFAULT);
	curl = curl_easy_init ();
	if (curl)
	{
		curl_easy_setopt (curl, CURLOPT_URL, url);
		//curl_easy_setopt (curl, CURLOPT_USERAGENT, "curl/7.64.1");
		curl_easy_setopt (curl, CURLOPT_USERAGENT, "Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:109.0) Gecko/20100101 Firefox/114.0");
		curl_easy_setopt (curl, CURLOPT_USE_SSL, (long)CURLUSESSL_ALL);
		curl_easy_setopt (curl, CURLOPT_SSL_VERIFYPEER, 0L);
		curl_easy_setopt (curl, CURLOPT_SSL_VERIFYHOST, 0L);
		curl_easy_setopt (curl, CURLOPT_FOLLOWLOCATION, 1L);
		if (verbose != 0)
			curl_easy_setopt (curl, CURLOPT_VERBOSE, 1L);
		curl_easy_setopt (curl, CURLOPT_SSLVERSION, CURL_SSLVERSION_TLSv1_2);
		curl_easy_setopt (curl, CURLOPT_SSL_ENABLE_ALPN, 1L);
		curl_easy_setopt (curl, CURLOPT_HTTP_VERSION,
				CURL_HTTP_VERSION_NONE);
		curl_easy_setopt (curl, CURLOPT_WRITEFUNCTION, func);
		//curl_easy_setopt (curl, CURLOPT_WRITEFUNCTION, &c_write_callback);
		curl_easy_setopt (curl, CURLOPT_WRITEDATA, (void *) userdata);
		curl_easy_setopt (curl, CURLOPT_FAILONERROR, 1L);
		curl_easy_setopt (curl, CURLOPT_EXPECT_100_TIMEOUT_MS, 3000L);
		curl_easy_setopt (curl, CURLOPT_TIMEOUT, 20L);
		curl_easy_setopt (curl, CURLOPT_SERVER_RESPONSE_TIMEOUT, 22L);
		curl_easy_setopt (curl, CURLOPT_MAXREDIRS, 50L);
		curl_easy_setopt (curl, CURLOPT_ACCEPT_ENCODING, "");
		curl_easy_setopt (curl, CURLOPT_TRANSFER_ENCODING, 1L);
		curl_easy_setopt (curl, CURLOPT_HTTP_TRANSFER_DECODING, 1L);
		curl_easy_setopt (curl, CURLOPT_HTTP_CONTENT_DECODING, 1L);
		curl_easy_setopt (curl, CURLOPT_DNS_SERVERS, "1.1.1.1,8.8.8.8");
		curl_easy_setopt (curl, CURLOPT_COOKIEFILE, "cookies.txt");
		curl_easy_setopt (curl, CURLOPT_COOKIEJAR, "cookies.txt");
		res = curl_easy_perform (curl);
		if (res != CURLE_OK)
		{
			fprintf (stderr, "└ %s\n", 
					curl_easy_strerror (res));
			return (1);
	   	}
		curl_easy_cleanup (curl);
	}
	curl_global_cleanup ();
	return (0);
}

int
http_download(char *url, char *filename)
{
	int	fd;
	int	*fd_ptr;

	fd = open(filename, O_CREAT);
	fd_ptr = &fd;
	http_get(url, (void *) fd_ptr, &c_writefd_callback);
	close(fd);
	return (0);
}

static size_t
c_write_callback (void *data, size_t size, size_t nmemb, void *userdata)
{
	char		*buffer = NULL;
	size_t		realsize = size * nmemb;
	t_site		*site = (t_site *) userdata;

	buffer = realloc (site->raw_html, site->size + realsize + 1);
	if (buffer == NULL)
	{
	fprintf (stderr, "not enough memory (realloc returned NULL)\n");
		return (0);
	}
	site->raw_html = buffer;
	memcpy (&(site->raw_html[site->size]), data, realsize);
	site->size += realsize;
	site->raw_html[site->size] = '\0';
	return (realsize);
}

static size_t
c_writefd_callback (void *data, size_t size, size_t nmemb, void *userdata)
{
	size_t	realsize = size * nmemb;
	int		fd = (int) &userdata;

	if (write(fd, data, realsize) == -1)
		exit (99);
	return (realsize);
}
