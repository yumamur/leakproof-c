#include "../lpc.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct s_struct
{
	void	**arr;
	int		size;
}	t_struct;

// Notice how you can not notice it is called in anywhere
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
	destroyer1(test_struct);
	printf("%d\n", lpc_export(test_struct, (t_lpc_destroyer)destroyer1));
/*	After an 'addr' is loaded into the storage, as in LINE: 46,
 *	the variable 'addr' is free to use. 
 */
	test_struct = malloc(1); // Writing over a pointer to an allocated area
	free(test_struct);
	lpc_export(test_struct, free);

	test_ptr = malloc(20 * sizeof(void *));
	test_ptr[16] = malloc (100);
	lpc_export(test_ptr, (t_lpc_destroyer)destroyer2);
	destroyer2(test_ptr);

	test_ptr = malloc(1);
	lpc_export(test_ptr, free);
	free(test_ptr);
}

int main(void)
{
	test1();
}
