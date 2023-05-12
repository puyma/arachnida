/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   html_attributes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 12:10:25 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/05/12 11:45:22 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arachnida.h"

char *
html_get_attribute (const char *attr, char *html_el)
{
	char	*attribute;
	char	*el;

	attribute = ft_strjoin(attr, "=");
	el = html_el;
	while (*el != '\0')
	{
		if (*el == *attr && strncmp (el, attribute, strlen (attribute)) == 0)
		{
			el += strlen(attribute);
			if (*el == 34 || *el == 39)
				return (el);
			else
				return (NULL);
		}
		++el;
	}
	return (NULL);
}
