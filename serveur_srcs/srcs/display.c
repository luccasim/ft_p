/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luccasim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 17:06:50 by luccasim          #+#    #+#             */
/*   Updated: 2017/05/18 17:06:52 by luccasim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

int				message(int type, int fd, char *msg)
{
	t_env		*env;
	t_message	message;

	env = singleton();
	message.type = type;
	message.fd = (fd == FD_ERROR) ? 2 : 1;
	if (fd == FD_SUCCESS)
		ft_snprintf(message.msg, MSG_SIZE, "{g:1}SUCCESS{e}\n");
	else if (fd == FD_ERROR)
		ft_snprintf(message.msg, MSG_SIZE, "{r:1}ERROR:{e} %s\n", msg);
	else
		ft_strncpy(message.msg, msg, MSG_SIZE - 1);
	if (env->client.login.access == ACCESS_GUEST)
		ft_fprintf(env->client.sock, message.msg);
	else
		send(env->client.sock, &message, sizeof(t_message), 0);
	return (SUCCESS);
}

static int		display_state(int state, char *buf)
{
	if (state == SUCCESS)
		ft_strlcpy(buf, "{g:1}SUCCESS{e}", 16);
	else if (state == WARNING)
		ft_strlcpy(buf, "{b:1}WARNING{e}", 16);
	else
		ft_strlcpy(buf, "{r:1}ERROR{e}", 16);
	return (SUCCESS);
}

int				display(t_env *env, int state, int who, char *msg)
{
	char		st[16];
	char		*name;
	char		*format;
	char		f[128];

	display_state(state, st);
	name = (who == SERVER) ? env->server.name : env->client.name;
	format = "{w:1}[%hk] %-16.15s[{c:1:%d}/{g:1:%d}{w:1}] %s{e}\n";
	ft_snprintf(f, 128, "%-16.15s%s", st, format);
	ft_printf(f, TIMESTAMP, name, env->nbrclients, env->server.limit, msg);
	return (SUCCESS);
}
