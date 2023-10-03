#include "lpc_int.h"
#include <stdlib.h>
#include <unistd.h>

void	leakproof_init(void) __attribute__((constructor(5)));
void	leakproof_destroy(void) __attribute__((destructor(5)));
void	leakproof_constructor(void) __attribute__((constructor(6)));

void	leakproof_init(void)
{
	t_lp_storage	*storage;
	unsigned int	retry;

	retry = 0;
	while (++retry < 100)
	{
		storage = malloc(sizeof(t_lp_storage));
		if (storage)
			break ;
	}
	*leakproof_storage() = storage;
	*storage = (t_lp_storage){};
	while (++retry < 100)
	{
		storage->load = malloc(sizeof(t_lp_load) * 2);
		if (storage->load)
			break ;
	}
	*storage->load = (t_lp_load){};
	storage->cap = 2;
}

void	leakproof_destroy(void)
{
	t_lp_storage	*storage;

	storage = *leakproof_storage();
	if (!storage || !storage->load)
		return ;
	while (storage->size)
	{
		--storage->size;
		storage->load[storage->size].destroyer \
		(storage->load[storage->size].addr);
	}
	if (storage->load)
		free(storage->load);
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
