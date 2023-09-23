#ifndef LEAKPROOF_INT_H
# define LEAKPROOF_INT_H

typedef struct s_storage
{
	unsigned int	size;
	unsigned int	cap;
	void			**data;
	void			**destroyers;
}	t_storage;

void	leakproof_errmsg(void);
void	**leakproof_storage(void);
int		leakproof_check_storage(void);
int		leakproof_enlarge_storage(void);
int		leakproof_load(void *data, void *function);

void	leakproof_init(void) __attribute__((constructor(5)));
void	leakproof_destroy(void) __attribute__((destructor(5)));
void	leakproof_constructor(void) __attribute__((constructor(6)));
void	leakproof_destructor(void) __attribute__((destructor(6)));
#endif
