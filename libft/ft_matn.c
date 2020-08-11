/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 13:52:54 by phakakos          #+#    #+#             */
/*   Updated: 2020/08/11 13:52:55 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>


#include <stdio.h>
void    matn_put(t_matn *matn, size_t n)
{
    size_t  row;
    size_t  col;

    row = -1;
    while (++row < n && (col = -1))
    {
        while (++col < n)
            printf("[%f]", matn->mat[row][col]);
        printf("\n");
    }
    printf("\n");
}

void    *matn_free(t_matn *matn, size_t n)
{
    while (n-- > 0)
        free (matn->mat[n]);
    if (n == 0)
        free (matn->mat);
    ft_memdel((void**)matn);
    return (NULL);
}


// NOT WORKING AS I THOUGHT
t_matn  *matn_cpy(float **src, size_t n)
{
    t_matn  *ret;
    size_t  row;
    size_t  col;
    float   **arr;

    arr = src;
    if (!(ret = (t_matn*)malloc(sizeof(t_matn*))))
        return (NULL);
    if (!(ret->mat = (float**)malloc(sizeof(float*) * n)))
        return (matn_free(ret, -1));
    row = -1;
    while (++row < n && (col = -1))
    {
        printf("hello\n");
        if (!(ret->mat[row] = (float*)malloc(sizeof(float) * n)))
            return (matn_free(ret, row));
        printf("there\n");

        while (++col < n)
        {
                    printf("%ld %ld\n", row, col);
                    printf("%f\n", arr[row][col]);
            ret->mat[row][col] = arr[row][col];
        }
    }
    return (ret);
}

t_matn  *matn_ini(size_t n)
{
    t_matn  *ret;
    size_t  row;

    if (!(ret = (t_matn*)malloc(sizeof(t_matn*))))
        return (NULL);
    if (!(ret->mat = (float**)malloc(sizeof(float*) * n)))
        return (matn_free(ret, -1));
    row = -1;
    while (++row < n)
    {
        if (!(ret->mat[row] = (float*)malloc(sizeof(float) * n)))
            return (matn_free(ret, row));
        ft_memset(ret->mat[row], 0, sizeof(float) * n);
    }
    return (ret);
}

void    matn_scale_cha(t_matn *matn, float s, size_t n)
{
    size_t  i;

    i = -1;
    while (++i< n)
        matn->mat[i][i] = s;
}

t_matn  *matn_scale_ini(float s, size_t n)
{
    t_matn  *ret;
    size_t  i;

    if (!(ret = matn_ini(n)))
        return (NULL);
    i = -1;
    while (++i < n)
        ret->mat[i][i] = s;
    return (ret);
}