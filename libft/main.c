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
	int  fd;
	int  test;
	struct stat st;

	fd = open("toto", O_CREAT | O_RDWR, 0777);
	write(fd, "Bonjour", 7);
	fstat(fd, &st);
	test = open("hello", O_CREAT | O_RDONLY, st.st_mode);
	PUTNBR(fd);
	close(fd);
	close(test);
	return (EXIT);
}
