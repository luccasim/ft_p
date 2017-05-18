/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luccasim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 17:08:42 by luccasim          #+#    #+#             */
/*   Updated: 2017/05/18 17:08:44 by luccasim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

static void		signals_handle(int pid)
{
	t_env		*env;

	env = singleton();
	if (pid == SIGCHLD)
		env->connexion--;
	if (pid == SIGQUIT)
		STATE(env, "CLOSED!");
}

int				signals(void)
{
	signal(SIGCHLD, signals_handle);
	signal(SIGQUIT, signals_handle);
	return (SUCCESS);
}
