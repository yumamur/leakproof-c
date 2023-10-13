#include "lpc_int.h"
#include "lpc_int_structs.h"
#include "typeft.h"
#include <stdlib.h>

int	lpc_int_load_init(t_lpc_load *load)
{
	if (!load)
		return (-1);
	*load = (t_lpc_load){};
	load->addr = malloc(2 * sizeof(t_lpc_addr));
	if (!load->addr)
		return (-1);
	load->cap = 2;
	load->size = 0;
	return (0);
}

int	lpc_int_enlarge_load(t_lpc_load *load)
{
	t_lpc_addr	*tmp;
	t_uint		i;

	if (!load)
		return (-1);
	tmp = malloc(load->cap * 2 * sizeof(t_lpc_addr));
	if (!tmp)
		return (-1);
	i = 0;
	while (i < load->size)
	{
		tmp[i] = load->addr[i];
		++i;
	}
	free(load->addr);
	load->addr = tmp;
	load->cap *= 2;
	return (0);
}

int	lpc_int_load(void *addr, void *destroyer, int priority)
{
	t_lpc_storage	*ptr;
	t_lpc_load		*ld_ptr;

	ptr = *lpc_int_storage();
	if (!ptr || !addr)
		return (-1);
	if (!destroyer)
		destroyer = free;
	ld_ptr = lpc_int_find_destroyer(destroyer);
	if (!ld_ptr)
	{
		if (lpc_int_new_destroyer(destroyer))
			return (-1);
		return (lpc_int_load(addr, destroyer, priority));
	}
	if (ld_ptr->size >= ld_ptr->cap - 1
		&& lpc_int_enlarge_load(ld_ptr))
		return (-1);
	lpc_int_add_addr(ld_ptr, addr, priority);
	return (0);
}
