#include "leakproof_int.h"

void	**leakproof_storage(void)
{
	static void	*data;

	return (&data);
}

void	leakproof_export(void *data, void (*destroyer)(void *))
{
	int	check;

	check = leakproof_check_storage();
	if (check == -1)
		return (leakproof_errmsg());
	else if (check == 1 && leakproof_enlarge_storage())
		return (leakproof_errmsg());
	else if (leakproof_load(data, destroyer))
		return (leakproof_errmsg());
}
