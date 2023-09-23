#ifndef LEAKPROOF_H
# define LEAKPROOF_H

/*	Include this file and compile the .c files along with your program.
*	The rest is handled.
*/

/*  Type-casting for 'destroyer'. You won't, but might need it.
 */
typedef void	(*t_leakproof)(void *);
//	Example: leakproof_export(addr, (t_leakproof)destroyer);

/* 'addr' should be a dynamically allocated data.
*  'destroyer' is a function, which de-allocates 'addr'.
*/
void	leakproof_export(void *addr, void (*destroyer)(void *));

/* 'addr' can refer to any type of data, as long as 'destroyer' is a function,
*  which can take 'addr' as the only parameter and successfully de-allocate it.
*  You may find the example.c file quite elucidative.
*/
#endif
