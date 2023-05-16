/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   html_tags.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:28:41 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/05/16 10:46:09 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arachnida.h"

int
html_save_snippets (t_list *lst, char *ext)
{
	FILE		*file;
	char		*filename = NULL;
	static int	counter = 0;

	while (lst != NULL)
	{
		++counter;
		asprintf(&filename, "%s%03d%s", path, counter, ext);
		
		file = fopen(filename, "w");
		fprintf(file, "%s", lst->content);
		printf(" %03d%s\n", counter, ext);
		fclose(file);

		if (filename) { free (filename); }
		lst = lst->next;
	}
	return (0);
}
