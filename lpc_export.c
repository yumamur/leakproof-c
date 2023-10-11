#include "lpc_int.h"

int	lpc_export(void *addr, ...)
{
	__builtin_va_list	arg;
	int					i;

	i = lpc_int_check_storage();
	if (i == -1)
		return (-1);
	else if (i == 1 && lpc_int_enlarge_storage())
		return (-1);
	else if (!addr)
		return (0);
	__builtin_va_start(arg, addr);
	if (lpc_int_load(addr, __builtin_va_arg(arg, void *),
			__builtin_va_arg(arg, int)))
	{
		__builtin_va_end(arg);
		return (-1);
	}
	__builtin_va_end(arg);
	return (0);
}
