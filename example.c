#include <stdlib.h>
#include "leakproof.h"

typedef struct s_struct
{
	void	**arr;
	int		size;
}	t_struct;

// Notice how you can not notice it is called in anywhere
void	destroyer(t_struct *test)
{
	int	i;

	i = 0;
	while (i < test->size)
	{
		free(test->arr[i]);
		++i;
	}
	free(test->arr);
	free(test);
}

void	test1(void)
{
	t_struct	*test;
	int			i;

	test = malloc(sizeof(t_struct));
	test->size = 50;
	test->arr = malloc(test->size * sizeof(void *));
	i = 0;
	while (i < test->size)
	{
		test->arr[i] = malloc(test->size);
		++i;
	}
	leakproof_export(test, (t_leakproof)destroyer);
	test = malloc(1);
	free(test);
}

void	test2(void)
{
	t_struct	*test;
	int			i;

	test = malloc(sizeof(t_struct));
	test->size = 50;
	test->arr = malloc(test->size * sizeof(void *));
	i = 0;
	while (i < test->size)
	{
		test->arr[i] = malloc(test->size);
		++i;
	}
	test = malloc(1);
	free(test);
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
