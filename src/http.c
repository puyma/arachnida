/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   http.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 11:31:21 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/05/16 12:51:32 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arachnida.h"

static size_t	c_write_callback (void *data, size_t size, 
					size_t nmemb, void *userdata);

int
http_get(char *url, void *userdata, FILE *file)
{
	CURL		*curl;
	CURLcode	res;

	(void) file;
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

		curl_easy_setopt (curl, CURLOPT_WRITEFUNCTION, &c_write_callback);
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
			fprintf (stderr, "└ %s%s%s\n", RED,
					curl_easy_strerror (res), NOSTYLE);
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
	CURL		*curl;
	CURLcode	res;
	FILE		*file;

	file = fopen (filename, "w");
	if (file == NULL)
	{
		fprintf (stderr, "%s\n", strerror (errno));
		exit (99);
	}
	url_decode (&url);
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
		curl_easy_setopt (curl, CURLOPT_WRITEDATA, (void *) file);
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
	fclose(file);
	return (0);
}

int
http_download_lst (t_list *url_list)
{
	char	*url;
	char	*filename;
	char	*save_to;

	while (url_list != NULL)
	{
		url = url_list->content;

		// check if scheme is http(s)://
		if (url && *url != 'h' && *(url + 1) != 't') // needs to be better implemented
		{ url_list = url_list->next; continue ; }

		filename = url_path_to_file(url); // filename fallback should be plain url
		if (filename)
		{
			printf(" %s\n", filename);

			save_to = ft_strjoin(path, filename);
			http_download(url, save_to);
			
			free(filename);
			free(save_to);
		}
		url_list = url_list->next;
	}
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
	{ fprintf (stderr, "not enough memory (realloc returned NULL)\n"); return (0); }
	site->raw_html = buffer;
	memcpy (&(site->raw_html[site->size]), data, realsize);
	site->size += realsize;
	site->raw_html[site->size] = '\0';
	return (realsize);
}
