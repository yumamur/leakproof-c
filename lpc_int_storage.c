#include "lpc_int.h"
#include <stdlib.h>

void	**lpc_int_storage(void)
{
	static void	*data;

	return (&data);
}

int	lpc_int_check_storage(void)
{
	t_lpc_storage	*ptr;

	ptr = *lpc_int_storage();
	if (!ptr || ptr->cap < 2 || !ptr->load)
		return (-1);
	return (0);
}

int	lpc_int_enlarge_storage(void)
{
	t_lpc_storage	*ptr;
	void			*tmp;

	ptr = *lpc_int_storage();
	if (!ptr)
		return (-1);
	tmp = malloc((ptr->cap * 2 * sizeof(t_lpc_load)));
	if (!tmp)
		return (-1);
	memcpy(tmp, ptr->load, ptr->size * sizeof(t_lpc_load));
	memset(ptr->load, 0, ptr->cap * sizeof(t_lpc_load));
	free(ptr->load);
	ptr->load = tmp;
	return (0);
}
