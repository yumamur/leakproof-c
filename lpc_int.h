#ifndef LPC_INT_H
# define LPC_INT_H

# include "lpc_int_structs.h"

# ifndef TYPEFT_H
#  include "typeft.h"
# endif
# ifndef LIBFT_H
#  include <string.h>
# endif

void	lpc_int_errmsg(void);
void	**lpc_int_storage(void);
int		lpc_int_check_storage(void);
int		lpc_int_enlarge_storage(void);
int		lpc_int_load(void *data, void *function, int priority);
#endif
