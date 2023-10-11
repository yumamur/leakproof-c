#include "../lpc.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct s_struct
{
	void	**arr;
	int		size;
}	t_struct;

void	destroyer1(t_struct *ptr)
{
	int	i;

	i = 0;
	while (i < ptr->size)
	{
		free(ptr->arr[i]);
		++i;
	}
	free(ptr->arr);
	free(ptr);
}

void	destroyer2(void **ptr)
{
	free(ptr[16]);
	free(ptr);
}

void	test1(void)
{
	t_struct	*test_struct;
	void		**test_ptr;
	int			i;

	test_struct = malloc(sizeof(t_struct));
	test_struct->size = 50;
	test_struct->arr = malloc(test_struct->size * sizeof(void *));
	i = 0;
	while (i < test_struct->size)
	{
		test_struct->arr[i] = malloc(test_struct->size);
		++i;
	}
	lpc_export(test_struct, destroyer1, 5, NULL);

	test_struct = malloc(1);
	lpc_export(test_struct, free, NULL);

	test_ptr = malloc(20 * sizeof(void *));
	test_ptr[16] = malloc(100);
	lpc_export(test_ptr, destroyer2, NULL);

	test_ptr = malloc(1);
	lpc_export(test_ptr, NULL);
}

void	test2(void)
{
	t_struct	*test_struct;
	void		**test_ptr;
	int			i;

	test_struct = malloc(sizeof(t_struct));
	test_struct->size = 50;
	test_struct->arr = malloc(test_struct->size * sizeof(void *));
	i = 0;
	while (i < test_struct->size)
	{
		test_struct->arr[i] = malloc(test_struct->size);
		++i;
	}

	test_struct = malloc(1);

	test_ptr = malloc(20 * sizeof(void *));
	test_ptr[16] = malloc (100);
}

#include "../lpc_int.h"

int main(void)
{
	t_lpc_storage *ptr;
	t_uint	i = 0, k = 0;

	test1();
	ptr = *lpc_int_storage();
	printf("storage = %p\n"\
		"size    = %d\n"\
		"cap     = %d\n"\
		"load    = %p\n",
		ptr,
		ptr->size,
		ptr->cap,
		ptr->load);
	while (i < ptr->size)
	{
		printf("\tdestroyer  = %p\n"\
			"\tsize       = %d\n"\
			"\tcap        = %d\n"\
			"\taddr       = %p\n",
			ptr->load[i].destroyer,
			ptr->load[i].size,
			ptr->load[i].cap,
			ptr->load[i].addr);
		k = 0;
		while (k < ptr->load[i].size)
		{
			printf("\t\taddr     = %p\n"\
		  		"\t\tpriority = %d\n",
				ptr->load[i].addr[k].addr,
				ptr->load[i].addr[k].priority);
			++k;
		}
		++i;
	}
}
