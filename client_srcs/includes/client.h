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
# define MSG_SIZE			2048
# define IDENTIFIED			424242

/*
** Enums
*/

typedef enum				e_enum_access
{
	ACCESS_MASTER = 1,
	ACCESS_USER,
	ACCESS_GUEST
}							t_enum_access;

typedef enum				e_enum_errors
{
	NOERROR = SUCCESS,
	PROTOCOL,
	ADDR,
	PORT,
	ACCESS,
	SOCK,
	CONNECT,
	READ,
	GETCWD
}							t_enum_errors;

typedef enum				e_enum_debug
{
	DEBUG_ALL = 6,
	DEBUG_LOGIN = 2,
	DEBUG_CLIENT = 4,
}							t_enum_debug;

typedef enum				e_enum_fd
{
	FD_SUCCESS = 1,
	FD_ERROR = 2
}							t_enum_fd;

typedef enum				e_enum_msg
{
	MSG_RESPONSE,
	MSG_REQUEST
}							t_enum_msg;

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

typedef struct				s_message
{
	char					msg[MSG_SIZE];
	int						fd;
	t_enum_msg				type;
	int						receipt;
}							t_message;

typedef struct				s_client
{
	char					name[SIZE];
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
** Dictionary
*/

typedef struct				s_dict_option
{
	char					*key;
	int						(*function)(t_client *, char*);
}							t_dict_option;

/*
** Functions
*/

t_env						*singleton(void);
int							errors(t_env *env);
int							parser(t_env *env, int ac, char **av);
int							client(t_env *env);
int							debug(int act);
int							option_name(t_client *c, char *str);
int							option_access(t_client *c, char *str);

#endif
