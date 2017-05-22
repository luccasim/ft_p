/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luccasim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 16:24:37 by luccasim          #+#    #+#             */
/*   Updated: 2016/11/22 16:24:41 by luccasim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "error.h"
#include "get_next_line.h"
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int		main(int ac, char **av)
{
	char	str[128];
	char	*path;

	path = getcwd(0, 0);
	if (path && av[1])
	{
		ft_snprintf(str, 128, "%s/%s", path, av[1]);
		ft_printf("Actual path :%s\n", path);
		chdir(str);
		free(path);
		path = getcwd(0, 0);
		if (path)
		{
			ft_printf("New current directory %s\n", path);
			free(path);
		}
	}
	return (EXIT);
}
