/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   html_attributes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 12:10:25 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/05/15 13:43:27 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arachnida.h"

char *
html_get_attr_value (char *attr, char *html_element)
{
	char		*value;
	char		*el;
	long int	len;

	el = html_get_attr (attr, html_element);
	if (el == NULL) { return (NULL); }
	len = strchr (el + 1, *el) - el - 1;
	if (len == 0)
		return (NULL);
	value = strndup(el + 1, len);
	return (value);
}

t_list *
html_get_attr_values (char *attr, char *html_element)
{
	char		*el;
	t_list		*values = NULL;
	char		*attribute = ft_strjoin(attr, "=");
	size_t		attribute_len = strlen(attribute);

	el = html_get_attr (attr, html_element);
	while (*el != '\0')
	{
		if (strncmp (el, "</picture>", strlen ("</picture>")) == 0)
			break ;
		else if (strncmp (el, attribute, attribute_len) == 0)
		{
			char *value = html_get_attr_value (attr, el);
			ft_lstadd_back (&values, ft_lstnew ((void *) value));
		}
		++el;
	}	
	return (values);
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
