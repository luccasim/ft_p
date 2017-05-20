/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luccasim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 17:07:03 by luccasim          #+#    #+#             */
/*   Updated: 2017/05/18 17:07:06 by luccasim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

int			request_lpwd(t_client *c)
{
	if (request_access(c, c->request.cmd, ACCESS_USER))
		return (FAIL);
	message(MSG_RESPONSE, 0, c->login.cpath);
	return (SUCCESS);
}
