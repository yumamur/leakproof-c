#include "lpc_int.h"
#include <stdlib.h>

void	lpc_int_destroy(void) __attribute__((destructor(101)));
void	lpc_int_constructor(void) __attribute__((constructor(101)));

static int inline	try_malloc(void **var, t_ulong size)
{
	static int	i;

	i = 0;
	while (i++ < 100)
	{
		*var = malloc(size);
		if (*var)
			break ;
	}
	if (i == 100)
		return (-1);
	return (0);
}

void	lpc_int_constructor(void)
{
	t_lpc_storage	*storage;

	if (try_malloc((void **)&storage, sizeof(*storage)))
		return ;
	*lpc_int_storage() = storage;
	*storage = (t_lpc_storage){};
	if (try_malloc((void **)&storage->load, sizeof(*storage->load) * 2))
	{
		free(storage);
		return ;
	}
	*storage->load = (t_lpc_load){};
	storage->cap = 2;
}

void	lpc_int_destroy(void)
{
	t_lpc_storage	*storage;

	storage = *lpc_int_storage();
	if (!storage || !storage->load)
		return ;
	while (storage->size--)
	{
		while (storage->load[storage->size].size--)
		{
			storage->load[storage->size].destroyer
				(storage->load[storage->size].addr
					[storage->load[storage->size].size].addr);
		}
		free(storage->load[storage->size].addr);
	}
	if (storage->load)
		free(storage->load);
	free(storage);
}
