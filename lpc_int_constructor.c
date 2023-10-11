#include "lpc_int.h"
#include <stdlib.h>
#include <stdio.h>

void	lpc_int_destroy(void) __attribute__((destructor(101)));
void	lpc_int_constructor(void) __attribute__((constructor(101)));
void	lpc_int_load_destroy(t_lpc_load *load);

void	lpc_int_constructor(void)
{
	t_lpc_storage	*storage;

	storage = malloc(sizeof(t_lpc_storage));
	if (!storage)
		return ;
	*lpc_int_storage() = storage;
	*storage = (t_lpc_storage){};
	storage->load = malloc(sizeof(t_lpc_load) * 2);
	if (!storage->load)
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
		lpc_int_load_destroy(&storage->load[storage->size]);
	if (storage->load)
		free(storage->load);
	free(storage);
}
