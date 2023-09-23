#ifndef LEAKPROOF_INT_H
# define LEAKPROOF_INT_H

typedef struct s_lp_load
{
	unsigned int	priority;
	void			*addr;
	void			(*destroyer)(void *);
}	t_lp_load;

typedef struct s_lp_storage
{
	unsigned int	size;
	unsigned int	cap;
	t_lp_load		*load;
}	t_lp_storage;

void	leakproof_errmsg(void);
void	**leakproof_storage(void);
int		leakproof_check_storage(void);
int		leakproof_enlarge_storage(void);
int		leakproof_load(void *data, void *function);

void	leakproof_init(void) __attribute__((constructor(5)));
void	leakproof_destroy(void) __attribute__((destructor(5)));
void	leakproof_constructor(void) __attribute__((constructor(6)));
#endif
