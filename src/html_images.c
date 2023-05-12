/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   html_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 10:43:12 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/05/12 11:02:55 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arachnida.h"

t_list *
html_get_images (t_site *site)
{
	char	*el;
	t_list	*elements;
	t_list	*img_list = NULL;

	elements = site->elements;
	while (elements != NULL)
	{
		el = elements->content;
		if (*(el + 1) == 'i' && *(el + 2) == 'm'
				&& *(el + 3) == 'g' && isspace (*(el + 4)) != 0)
		{
			write(1, el, 4);
			write(1, "\n", 1);
		}
		elements = elements->next;
	}
	return (img_list);
}
