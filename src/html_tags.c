/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   html_tags.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:28:41 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/05/15 16:42:44 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arachnida.h"

int
html_save_snippets (t_list *lst, char *ext)
{
	char		*filename;
	static int	counter = 1;
	int			fd;

	filename = ft_strjoin (ft_itoa (counter), ext);
	char *fpath = ft_strjoin(path, filename);
	while (lst != NULL)
	{
		fd = open (fpath, O_CREAT, 0777);
		char *s = lst->content;
		while (s && *s != '\0')
		{
			if (write (fd, s, 1) == -1)
				fprintf(stderr, "error writting to fd: %d\n", fd);
			++s;
		}
		close (fd);
	}
	return (0);
}
