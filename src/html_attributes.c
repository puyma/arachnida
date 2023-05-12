/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   html_attributes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 12:10:25 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/05/12 11:04:12 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arachnida.h"

int
html_get_attribute (const char *attr, char **html_el)
{
	char	*attribute;
	char	*el;

	attribute = ft_strjoin(attr, "=");
	el = *html_el;
	while (*el != '\0')
	{
		if (*el == *attr && strncmp (el, attribute, strlen (attribute)) == 0)
		{
			el += strlen(attribute);
			if (*el == 34 || *el == 39)
			{
				*html_el = el;
				return (1);
			}
			else
				return (0);
		}
		++el;
	}
	return (0);
}
