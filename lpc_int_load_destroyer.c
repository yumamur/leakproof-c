#include "lpc_int.h"

void	lpc_int_add_addr(t_lpc_load *load, void *addr, int priority)
{
	t_uint		i;

	if (priority <= 0 || priority > 255)
		priority = 255;
	i = 0;
	while (i <= load->size)
	{
		if (load->addr[i].priority > priority)
			++i;
		else
		{
			memmove(&load->addr[i + 1], &load->addr[i],
				(load->size - i) * sizeof(t_lpc_addr));
			load->addr[i] = (t_lpc_addr){addr, priority};
			++load->size;
			return ;
		}
	}
}

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
