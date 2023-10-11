/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typeft.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumamur <yumamur@student.42istanbul.com.t  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:44:12 by yumamur           #+#    #+#             */
/*   Updated: 2023/08/26 14:06:31 by yumamur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEFT_H
# define TYPEFT_H

typedef signed char				t_int8;
typedef signed short			t_int16;
typedef signed int				t_int32;
typedef signed long int			t_int64;

typedef unsigned char			t_uint8;
typedef unsigned short			t_uint16;
typedef unsigned int			t_uint32;
typedef unsigned long int		t_uint64;

typedef unsigned char			t_uchar;
typedef unsigned short			t_ushort;
typedef unsigned int			t_uint;
typedef unsigned long			t_ulong;
typedef unsigned long long		t_ullong;

typedef const void				t_c_void;
typedef const char				t_c_char;
typedef const short				t_c_short;
typedef const int				t_c_int;
typedef const long				t_c_long;
typedef const long long			t_c_llong;

typedef const t_uchar			t_c_uchar;
typedef const t_ushort			t_c_ushort;
typedef const t_uint			t_c_uint;
typedef const t_ulong			t_c_ulong;
typedef const t_ullong			t_c_ullong;

typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1
}	t_bool;
#endif /* TYPEFT_H */
