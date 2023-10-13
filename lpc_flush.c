#include "lpc_int.h"

int	lpc_flush(void)
{
	t_lpc_storage	*ptr;
	t_uint			i;

	if (lpc_int_check_storage() == -1)
		return (-1);
	ptr = *lpc_int_storage();
	i = 0;
	while (i < ptr->size)
	{
		lpc_int_destroy_p(&ptr->load[i], -1);
		++i;
	}
	return (0);
}
