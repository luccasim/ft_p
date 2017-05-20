/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luccasim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 16:49:10 by luccasim          #+#    #+#             */
/*   Updated: 2017/05/18 16:51:06 by luccasim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static t_dict_error g_errors[] =
{
	{PROTOCOL, "invalid protocol"},
	{PORT, "invalid port range"},
	{ADDR, "invalid address"},
	{GETCWD, "getcwd() fail."},
	{SOCK, "socket() failed."},
	{CONNECT, "connect() failed."},
	{READ, "read() fail."},
	{NOERROR, 0}
};

int		errors(t_env *env)
{
	if (ERROR)
		ft_fprintf(2, "{r:1:%-10s}", "ERROR:");
	env->error = CATCH(g_errors);
	close(env->client.sock);
	return (env->error);
}
