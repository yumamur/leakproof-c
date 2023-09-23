#include "leakproof_int.h"
#include <stdlib.h>
#include <unistd.h>

#ifndef LIBFT_H
# include <string.h>
#endif

int	leakproof_check_storage(void)
{
	t_lp_storage	*ptr;

	ptr = *leakproof_storage();
	if (!ptr || ptr->cap < 2 || !ptr->load)
		return (-1);
	if (ptr->size == ptr->cap - 1)
		return (1);
	return (0);
}

int	leakproof_enlarge_storage(void)
{
	t_lp_storage	*ptr;
	void			*tmp;

	ptr = *leakproof_storage();
	if (!ptr)
		return (-1);
	tmp = malloc((ptr->cap * 2 * sizeof(t_lp_load)));
	if (!tmp)
		return (-1);
	memcpy(tmp, ptr->load, ptr->cap * sizeof(t_lp_load));
	memset(ptr->load, 0, ptr->cap * sizeof(t_lp_load));
	free(ptr->load);
	ptr->load = tmp;
	return (0);
}

int	leakproof_load(void *addr, void *destroyer)
{
	t_lp_storage	*ptr;

	ptr = *leakproof_storage();
	if (!ptr)
		return (-1);
	ptr->load[ptr->size].addr = addr;
	ptr->load[ptr->size].destroyer = destroyer;
	ptr->load[ptr->size].priority = -1;
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
