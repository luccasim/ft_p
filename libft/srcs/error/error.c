/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luccasim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 18:00:34 by luccasim          #+#    #+#             */
/*   Updated: 2017/05/18 18:00:36 by luccasim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "libft.h"

static t_error		*error_sglt(int num, char *msg, int action)
{
	static t_error	sglt;
	static int		flag = 1;

	if (flag)
	{
		flag = 0;
		sglt.num = 0;
		sglt.msg[0] = 0;
	}
	if (action == 1)
	{
		sglt.num = num;
		ft_strlcpy(sglt.msg, msg, 128);
	}
	return (&sglt);
}

int					error_check(void)
{
	t_error			*error;

	error = error_sglt(0, 0, 0);
	return (error->num);
}

int					error_throw(int domain)
{
	error_sglt(domain, 0, 1);
	return (FAIL);
}

int					error_catch(t_dict_error *dic)
{
	t_error			*error;
	int				i;

	error = error_sglt(0, 0, 0);
	if (error->num == SUCCESS)
		return (SUCCESS);
	if (dic)
	{
		i = 0;
		while (dic[i].key)
		{
			if (dic[i].key == error->num)
			{
				PUTERROR(dic[i].value);
				return (error->num);
			}
			i++;
		}
	}
	return (error->num);
}

int					error_print(char *msg)
{
	PUTERROR(msg);
	return (error_throw(FAIL));
}
