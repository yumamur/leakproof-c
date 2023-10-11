#include "lpc_int.h"
#include <unistd.h>

int __attribute__((aligned(16)))	lpc_export(void *addr, ...)
{
	__builtin_va_list	arg;

	if (lpc_int_check_storage() == -1)
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
