/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luccasim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 17:08:01 by luccasim          #+#    #+#             */
/*   Updated: 2017/05/18 17:08:02 by luccasim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

static t_dict_error g_errors[] =
{
	{SOCKET, "socket() fail."},
	{BIND, "bind() fail."},
	{LISTEN, "listen() fail."},
	{ACCEPT, "accept() fail."},
	{PROTOCOL, "getprotobyname() fail."},
	{RECV, "recv() fail."},
	{PWD, "getcwd() fail!"},
	{PORT, "port 0 unvalid."},
	{NOERROR, 0}
};

int		errors(t_env *env)
{
	if (ERROR)
	{
		debug(DEBUG_ALL);
		ft_printf("{r:1:%-15s}", "ERROR:");
	}
	env->error = CATCH(g_errors);
	return (SUCCESS);
}
