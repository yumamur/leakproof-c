#ifndef LPC_INT_STRUCTS_H
# define LPC_INT_STRUCTS_H

# ifndef TYPEFT_H
#  include "typeft.h"
# endif

typedef void	(*t_ptr_destroyer)(void *);

typedef struct s_lpc_addr
{
	void	*addr;
	t_uchar	priority;
}	t_lpc_addr;

typedef struct s_lpc_load
{
	t_uint			cap;
	t_uint			size;
	t_lpc_addr		*addr;
	t_ptr_destroyer	destroyer;
}	t_lpc_load;

typedef struct s_lpc_storage
{
	t_ulong		threshhold;
	t_uint		cap;
	t_uint		size;
	t_lpc_load	*load;
}	t_lpc_storage;

#endif
