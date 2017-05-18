#include "serveur.h"

int			request_lpwd(t_client *c)
{
	if (request_access(c, c->request.cmd, USER))
		return (FAIL);
	ft_fprintf(c->sock, "{y:1:%s}\n", c->login.cpath);
	return (SUCCESS);
}