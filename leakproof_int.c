#include "leakproof_int.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int	leakproof_check_storage(void)
{
	t_storage	*ptr;

	ptr = *leakproof_storage();
	if (!ptr || ptr->cap < 2 || !ptr->data || !ptr->destroyers)
		return (-1);
	if (ptr->size == ptr->cap - 1)
		return (1);
	return (0);
}

int	leakproof_enlarge_storage(void)
{
	t_storage	*ptr;
	void		*tmp;

	ptr = *leakproof_storage();
	if (!ptr)
		return (-1);
	tmp = malloc(ptr->cap * 2 * sizeof(void *));
	if (!tmp)
		return (-1);
	memcpy(tmp, ptr->data, ptr->cap * sizeof(void *));
	memset(ptr->data, 0, ptr->cap * sizeof(void *));
	free(ptr->data);
	ptr->data = tmp;
	tmp = malloc(ptr->cap * 2 * sizeof(void *));
	if (!tmp)
		return (-1);
	memcpy(tmp, ptr->destroyers, ptr->cap * sizeof(void *));
	memset(ptr->destroyers, 0, ptr->cap * sizeof(void *));
	free(ptr->destroyers);
	ptr->destroyers = tmp;
	return (0);
}

int	leakproof_load(void *data, void *destroyer)
{
	t_storage	*ptr;

	ptr = *leakproof_storage();
	if (!ptr)
		return (-1);
	ptr->data[ptr->size] = data;
	ptr->destroyers[ptr->size] = destroyer;
	++ptr->size;
	if (leakproof_check_storage() == 1 && leakproof_enlarge_storage())
		return (-1);
	return (0);
}

void	leakproof_errmsg(void)
{
	write(2, "The function you have called is having no memory at the moment.",
		53);
	write(2, "Please hold the addresses\n", 26);
}
