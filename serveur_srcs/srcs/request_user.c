/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request_user.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luccasim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 17:08:34 by luccasim          #+#    #+#             */
/*   Updated: 2017/05/18 17:08:35 by luccasim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

static int		request_fileexist(char *path, char *file)
{
	DIR				*dir;
	struct dirent	*dp;
	char			msg[MSG_SIZE];

	if ((dir = opendir(path)) == 0)
		return (FAIL);
	while ((dp = readdir(dir)) != 0)
		if (ft_strequ(dp->d_name, file))
		{
			closedir(dir);
			if (dp->d_type == DT_REG)
				return (SUCCESS);
			else
			{
				ft_snprintf(msg, MSG_SIZE, "'%s' is not a file!\n", file);
				message(MSG_RESPONSE, FD_ERROR, msg);
				return (FAIL);
			}
		}
	message(MSG_RESPONSE, FD_ERROR, "File not found!");
	closedir(dir);
	return (FAIL);
}

int				request_prompt(t_client *c)
{
	char		res[SIZE];

	if (request_access(c, "prompt", ACCESS_USER))
		return (FAIL);
	ft_bzero(res, SIZE - 1);
	message(MSG_REQUEST, 0, "Would you change your prompt?(y/n)\n");
	recv(c->sock, &res, SIZE, 0);
	if (ft_strnequ(res, "y", 1))
	{
		message(MSG_REQUEST, 0, "Set your new prompt.\n");
		recv(c->sock, &res, SIZE, 0);
		ft_strlcpy(c->prompt, res, SIZE);
	}
	else
	{
		message(MSG_RESPONSE, FD_ERROR, "Change prompt operation cancelled\n");
		return (FAIL);
	}
	return (SUCCESS);
}

int					request_quit(t_client *client)
{
	t_env			*env;

	env = singleton();
	env->nbrclients--;
	display(env, SUCCESS, CLIENT, "DISCONNECTED!");
	message(MSG_RESPONSE, 0, "{y:1}Disconnected!{e}\n");
	message(MSG_RESPONSE, FD_SUCCESS, 0);
	close(client->sock);
	exit(SUCCESS);
}

int				request_put(t_client *c)
{
	if (request_access(c, "put", ACCESS_USER))
		return (FAIL);
	if (c->request.nb != 2)
	{
		message(MSG_RESPONSE, FD_ERROR, "put <file>");
		return (FAIL);
	}
	if ((request_fileexist(c->login.cpath, c->request.args[1])) == FAIL)
		return (FAIL);
	if ((transfert(c->login.cpath, c->login.spath, c->request.args[1]))
		== FAIL)
		return (FAIL);
	return (SUCCESS);
}

int				request_get(t_client *c)
{
	if (request_access(c, "get", ACCESS_USER))
		return (FAIL);
	if (c->request.nb != 2)
	{
		message(MSG_RESPONSE, FD_ERROR, "get <file>");
		return (FAIL);
	}
	if ((request_fileexist(".", c->request.args[1])) == FAIL)
		return (FAIL);
	if ((transfert(c->login.spath, c->login.cpath, c->request.args[1]))
		== FAIL)
		return (FAIL);
	return (SUCCESS);
}
