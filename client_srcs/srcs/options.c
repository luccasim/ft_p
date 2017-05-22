/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luccasim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 15:26:25 by luccasim          #+#    #+#             */
/*   Updated: 2017/05/22 15:26:27 by luccasim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int				option_access(t_client *c, char *str)
{
	int		nb;
	t_env	*env;

	nb = ft_atoi(str);
	if (nb >= 1 && nb <= 3)
	{
		env = singleton();
		env->login.access = nb;
		c->access = nb;
	}
	else
		return (PERROR("<access?> = {1-3} ; Default : access=2"));
	return (SUCCESS);
}

int				option_name(t_client *c, char *str)
{
	t_env		*env;

	env = singleton();
	ft_strlcpy(env->login.name, str, SIZE);
	ft_strlcpy(c->name, str, SIZE);
	return (SUCCESS);
}
