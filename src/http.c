/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   http.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 11:31:21 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/05/11 11:44:45 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arachnida.h"

static size_t	c_write_callback (void *data, size_t size, 
					size_t nmemb, void *userdata);

int
ft_http_get(char *url, t_site **site)
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
		curl_easy_setopt (curl, CURLOPT_WRITEDATA, (void *) *site);
		curl_easy_setopt (curl, CURLOPT_FAILONERROR, 0L);
		curl_easy_setopt (curl, CURLOPT_EXPECT_100_TIMEOUT_MS, 3000L);
		curl_easy_setopt (curl, CURLOPT_TIMEOUT, 20L);
		curl_easy_setopt (curl, CURLOPT_SERVER_RESPONSE_TIMEOUT, 22L);
		res = curl_easy_perform (curl);
		if (res != CURLE_OK)
		{
			fprintf (stderr, "curl_easy_perform() failed: %s\n", 
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
