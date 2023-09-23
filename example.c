#include <stdlib.h>
#include "leakproof.h"

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
	leakproof_export(test_struct, (t_leakproof)destroyer1);

	test_struct = malloc(1);
	leakproof_export(test_struct, free);

	test_ptr = malloc(20 * sizeof(void *));
	test_ptr[16] = malloc (100);
	leakproof_export(test_ptr, (t_leakproof)destroyer2);
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

#include <stdio.h>
int	main(void)
{
#if __has_feature(address_sanitizer) | __has_feature(leak_sanitizer)
	test1(); // This will not result in leak
	test2(); // But this will
#else
	printf("Please, compile with '-fsanitize=address' or '-fsanitize=leak' flag\n");
#endif
}
