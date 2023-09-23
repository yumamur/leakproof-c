/*	MIT License

 *	Copyright (c) 2023	Yusuf S. Mamur
 *	Version: v0.1.0-alpha
 
 *	Permission is hereby granted, free of charge, to any person obtaining a copy
 *	of this software and associated documentation files (the "Software"), to deal
 *	in the Software without restriction, including without limitation the rights
 *	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *	copies of the Software, and to permit persons to whom the Software is
 *	furnished to do so, subject to the following conditions:
 
 *	The above copyright notice and this permission notice shall be included in all
 *	copies or substantial portions of the Software.
 
 *	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *	SOFTWARE.
 */

/*  	Simple (for now) tool of auto-freeing allocated areas.
 *
 *  	The tool is initialized before 'main()' function call. It loads every
 *  'addr'-'destroyer' pair into its internal structure. After 'main()' returns,
 *  the tool calls 'destroyer(addr)' for each pair.
 *
 *  	It is made to be compatible with 42schools projects, the only external
 *  functions needed are:
 *   - malloc();
 *   - free();
 *   - write();
 *   - memcpy();
 *   - memset();
 *  So, they can easily be implemented for projects.
 *
 *	'addr' can refer to any type of data, as long as 'destroyer' is a function,
 * 	which can take 'addr' as the only parameter and successfully de-allocate it.
 * 	You may find the example.c file quite elucidative.
 */

#ifndef LEAKPROOF_H
# define LEAKPROOF_H

/*  Type-casting for 'destroyer'. You won't, but might need it.
 */
typedef void	(*t_leakproof)(void *);
//	leakproof_export(addr, (t_leakproof)destroyer);

void	leakproof_export(void *addr, void (*destroyer)(void *));
/*	'addr' : The address to a dynamically allocated area.
 *	'destroyer' : A function, which can be used to de-allocate 'addr'.
 */

/* void	leakproof_export_priority(int priority, void *addr, void (*destroyer)(void *));
 */
#endif /* LEAKPROOF_H */
