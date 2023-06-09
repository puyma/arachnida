/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 11:12:24 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/05/12 13:15:11 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arachnida.h"

int
ft_aredigits (char *str)
{
	char	*s = str;

	while (s && *s != '\0')
	{
		if (isdigit (*s) == 0)
			return (0);
		++s;
	}
	return (1);
}
