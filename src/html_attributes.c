/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   html_attributes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 12:10:25 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/05/12 13:16:37 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arachnida.h"

char *
html_get_attr_value (char *attr, char *html_element)
{
	char	*value;
	char	*el;

	el = html_get_attr (attr, html_element);
	if (el == NULL) { return (NULL); }
	value = strndup(el + 1, strchr (el + 1, *el) - el - 1);
	return (value);
}

char *
html_get_attr (const char *attr, char *html_el)
{
	char	*el;
	char	*attribute;
	size_t	attribute_len;

	el = html_el;
	attribute = ft_strjoin(attr, "=");
	attribute_len = strlen(attribute);
	while (*el != '\0')
	{
		if (*el == *attr && strncmp (el, attribute, attribute_len) == 0)
		{
			el += attribute_len;
			if (*el == 34 || *el == 39)
			{ free (attribute); return (el); }
			else
			{ free (attribute); return (NULL); }
		}
		++el;
	}
	free (attribute);
	return (NULL);
}
