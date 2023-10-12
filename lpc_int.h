#ifndef LPC_INT_H
# define LPC_INT_H

# include "lpc_int_structs.h"

# ifndef TYPEFT_H
#  include "typeft.h"
# endif
# ifndef LIBFT_H
#  include <string.h>
# endif

void		lpc_int_errmsg(void);

void		**lpc_int_storage(void);
int			lpc_int_check_storage(void);
int			lpc_int_enlarge_storage(void);

int			lpc_int_load(void *data, void *function, int priority);
int			lpc_int_load_init(t_lpc_load *load);
int			lpc_int_enlarge_load(t_lpc_load *load);

int			lpc_int_new_destroyer(void *destroyer);
t_lpc_load	*lpc_int_find_destroyer(void *destroyer);
void		lpc_int_destroy_p(t_lpc_load *load, int p);

void		lpc_int_add_addr(t_lpc_load *load, void *addr, int priority);
#endif
