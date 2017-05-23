/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luccasim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 17:07:03 by luccasim          #+#    #+#             */
/*   Updated: 2017/05/22 15:54:21 by luccasim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

int				request_lcd(t_client *c)
{
	ft_strlcpy(c->old, c->pwd, SIZE);
	ft_strlcpy(c->pwd, c->login.cpath, SIZE);
	if (chdir(c->pwd))
		return (SUCCESS);
	else
		return (FAIL);
}

int				request_lls(t_client *c)
{
	char	new[SIZE];
	char	*arg;

	arg = c->request.request;
	arg++;
	ft_snprintf(new, SIZE, "%s %s", arg, c->login.cpath);
	ft_strdelsplit(c->request.args);
	c->request.args = ft_strsplit(new, ' ');
	return (request_system(c));
}

int				request_lpwd(t_client *c)
{
	char	m[MSG_SIZE];

	if (request_access(c, c->request.cmd, ACCESS_USER))
		return (FAIL);
	ft_snprintf(m, MSG_SIZE, "{y:1}%s\n{e}", c->login.cpath);
	message(MSG_RESPONSE, 0, m);
	return (SUCCESS);
}
