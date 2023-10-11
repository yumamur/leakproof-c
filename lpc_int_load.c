#include "lpc_int.h"
#include "lpc_int_structs.h"
#include "typeft.h"
#include <stdlib.h>

t_lpc_load	*lpc_int_find_destroyer(void *destroyer)
{
	t_lpc_storage	*ptr;
	t_uint			i;

	ptr = *lpc_int_storage();
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < ptr->size)
	{
		if (ptr->load[i].destroyer == destroyer)
			return (&ptr->load[i]);
		else
			++i;
	}
	return (NULL);
}

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

int	lpc_int_new_destroyer(void *destroyer)
{
	t_lpc_storage	*ptr;

	ptr = *lpc_int_storage();
	if (!ptr)
		return (-1);
	if (ptr->size >= ptr->cap - 1)
		lpc_int_enlarge_storage();
	if (lpc_int_load_init(&ptr->load[ptr->size]))
		return (-1);
	ptr->load[ptr->size].destroyer = destroyer;
	++ptr->size;
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

void	lpc_int_add_addr(t_lpc_load *load, void *addr, int priority)
{
	t_uint		i;

	if (priority <= 0 || priority > 255)
		priority = 255;
	i = 0;
	while (i < load->size)
	{
		if (load->addr[i].priority > priority)
			++i;
		else
		{
			memmove(&load->addr[i + 1], &load->addr[i],
				(load->size - i) * sizeof(t_lpc_addr));
			load->addr[i] = (t_lpc_addr){addr, priority};
			return ;
		}
	}
}

int	lpc_int_load(void *addr, void *destroyer, int priority)
{
	t_lpc_storage	*ptr;
	t_lpc_load		*ld_ptr;

	ptr = *lpc_int_storage();
	if (!ptr || !addr)
		return (-1);
	ld_ptr = lpc_int_find_destroyer(destroyer);
	if (!ld_ptr && (lpc_int_new_destroyer(destroyer)
			|| lpc_int_load(addr, destroyer, priority)))
		return (-1);
	if (ld_ptr->size >= ld_ptr->cap - 1
		&& lpc_int_enlarge_load(ld_ptr))
		return (-1);
	lpc_int_add_addr(ld_ptr, addr, priority);
	return (0);
}

void	lpc_int_load_destroy(t_lpc_load *load)
{
	t_uint	i;

	i = 0;
	while (i < load->size)
	{
		load->destroyer(load->addr[i].addr);
		++i;
	}
	free(load->addr);
}
