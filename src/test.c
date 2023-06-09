#include <stdio.h>
#include <string.h>

int	main(void)
{
	const char	*href = "https://nja.la";
	const char	*url = "https://nja.la/";
	size_t	len;
	size_t	url_len;
	size_t	href_len;
	size_t	delta_len;
	int		strncmp_diff;

	url_len = strlen(url);
	href_len = strlen(href);
	if (href_len >= url_len)
	{
		len = strlen(href);
		delta_len = href_len - url_len;
	}	
	else
	{
		len = strlen(url);
		delta_len = url_len - href_len;
	}
	strncmp_diff = strncmp(href, url, len);
	if (strncmp_diff < 0)
		strncmp_diff *= -1;
	printf("strncmp: %d\n", strncmp_diff);
	printf("delta_len: %zu\n", delta_len);
	return (0);
}
