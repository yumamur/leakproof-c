#include "leakproof_int.h"
#include <stdlib.h>
#include <unistd.h>

void	leakproof_init(void)
{
	t_storage		*storage;
	unsigned int	retry;

	retry = 0;
	while (++retry < 100)
	{
		storage = malloc(sizeof(t_storage));
		if (storage)
			break ;
	}
	*leakproof_storage() = storage;
	*storage = (t_storage){};
	while (++retry < 100)
	{
		storage->data = malloc(sizeof(void *) * 2);
		if (storage->data)
			break ;
	}
	while (++retry < 100)
	{
		storage->destroyers = malloc(sizeof(void *) * 2);
		if (storage->destroyers)
			break ;
	}
	storage->cap = 2;
}

void	leakproof_destroy(void)
{
	t_storage	*storage;

	storage = *leakproof_storage();
	if (!storage)
		return ;
	while (storage->size)
	{
		--storage->size;
		((void (*)(void *))storage->destroyers[storage->size]) \
		(storage->data[storage->size]);
	}
	if (storage->data)
		free(storage->data);
	if (storage->destroyers)
		free(storage->destroyers);
	free(storage);
}

void	leakproof_constructor(void)
{
	if (leakproof_check_storage() == -1)
	{
		write(2, "Leakproof seems not working, the rest is up to you!\n", 52);
		write(2, "You can make it\n", 16);
		return ;
	}
}
