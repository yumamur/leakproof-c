#ifndef LEAKPROOF_H
# define LEAKPROOF_H

/*  Simple tool of auto-freeing allocated areas.
 *
 *  The tool is initialized before 'main()' function call. It loads every
 *  'addr'-'destroyer' pair into its internal structure. After 'main()'
 *  returns, the tool calls 'destroyer(addr)' for each pair.
 *
 *
 *  It is made to be compatible with 42schools projects, used external
 *  functions are:
 *   - malloc();
 *   - free();
 *   - write();
 *   - memmove();
 *   - memcpy();
 *   - memset();
 *  So, they can easily be changed.
 */

/*  Type-casting for 'destroyer'. You won't, but might need it.
 */
typedef void	(*t_leakproof)(void *);
//	leakproof_export(addr, (t_leakproof)destroyer);

void	leakproof_export(void *addr, void (*destroyer)(void *));
/*	'addr' : The address to a dynamically allocated area.
 *	'destroyer' : A function, which can be used to de-allocate 'addr'.
 *
 *	'addr' can refer to any type of data, as long as 'destroyer' is a function,
 * 	which can take 'addr' as the only parameter and successfully de-allocate it.
 * 	You may find the example.c file quite elucidative.
 */

/*	Include this file and compile the .c files along with your program.
 *	Load the tool with the required data, the rest is handled internally.
 */

#endif
