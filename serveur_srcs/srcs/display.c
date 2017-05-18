#include "serveur.h"

int		display(t_env *env, int state, int who, char *msg)
{
	if (state == SUCCESS)
		ft_printf("{g:1:%-15s}", "SUCCESS:");
	else if (state == WARNING)
		ft_printf("{b:1:%-15s}", "WARNING:");
	else
		ft_printf("{r:1:%-15s}", "FAIL:");
	ft_printf("[{w:1:%hk}] ", TIMESTAMP);
	if (who == SERVER)
		ft_printf("{w:1:%-30s}", env->server.name);
	else
		ft_printf("{w:1:%-30s}", env->client.name);
	ft_printf("{w:1:%s}\n", msg);
	return (SUCCESS);
}