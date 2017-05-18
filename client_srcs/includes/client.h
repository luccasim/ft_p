/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luccasim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 16:29:27 by luccasim          #+#    #+#             */
/*   Updated: 2017/05/18 16:44:14 by luccasim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/socket.h>
# include <netdb.h>
# include <arpa/inet.h>
# include "ft_printf.h"
# include "libft.h"
# include "error.h"
# include "get_next_line.h"

# define SIZE				128
# define IDENTIFIED			424242

/*
** Enums
*/

typedef enum				e_enum_server_access
{
	MASTER = 1,
	USER,
	GUEST
}							t_enum_server_access;

typedef enum				e_enum_client_error
{
	NOERROR = SUCCESS,
	PROTOCOL,
	ADDR,
	PORT,
	ACCESS,
	SOCK,
	CONNECT,
	READ
}							t_enum_client_error;

typedef enum				e_enum_client_debug
{
	ALL = 0,
	LOGIN = 2,
	CLIENT = 4,
}							t_enum_client_debug;

/*
** Structs
*/

typedef struct				s_login
{
	int						mask;
	int						access;
	char					name[SIZE];
	char					cpath[SIZE];
	char					spath[SIZE];
}							t_login;

typedef struct				s_client
{
	char					name[SIZE];
	char					addr[SIZE];
	int						port;
	int						access;
	int						sock;
	struct protoent			*proto;
	struct sockaddr_in		sin;
}							t_client;

typedef struct				s_env
{
	int						error;
	t_login					login;
	t_client				client;
}							t_env;

/*
** Functions
*/

t_env						*singleton(void);
int							errors(t_env *env);
int							parser(t_env *env, int ac, char **av);
int							client(t_env *env);
int							debug(int act);

#endif
