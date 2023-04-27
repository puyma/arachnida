#!/usr/local/bin/python3

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    spider.py                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/27 16:05:34 by mpuig-ma          #+#    #+#              #
#    Updated: 2023/04/27 16:06:52 by mpuig-ma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import sys, getopt
import requests


if __name__ == '__main__':
    if (len(sys.argv[1:])) != 0:
        site = requests.get('https://www.42barcelona.com')
        print(site.text)
