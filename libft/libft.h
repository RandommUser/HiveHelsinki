/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 16:53:28 by phakakos          #+#    #+#             */
/*   Updated: 2020/02/28 19:42:44 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# define BUFF_SIZE 64
# define FD_LIMIT 4864
# include <string.h>

typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

typedef struct	s_rgb
{
	int	red;
	int	green;
	int	blue;
}				t_rgb;

typedef	struct	s_vec2
{
	float	*vec;
}				t_vec2;

typedef	struct	s_vec4
{
	long double	vec[4];
}				t_vec4;

typedef	struct	s_mat2
{
	float	**mat;
}				t_mat2;

typedef	struct	s_mat4
{
	long double	mat[4][4];
}				t_mat4;

typedef	struct	s_matn
{
	float	**mat;
}				t_matn;

typedef	struct	s_vecn
{
	float	*vec;
}				t_vecn;

/*
** DEBUG ONLY
** void    		vecn_put(t_vecn *vecn, size_t n);
** void    		matn_put(t_matn *matn, size_t n);
** void    		mat4_put(t_mat4 mat4);
** void    		vec4_put(t_vec4 vec);
*/

t_mat2			*mat2_rota(double theta);
t_mat2			*mat2_flip(void);
t_vec2			*mat2_vec(t_mat2 *mat2, t_vec2 *vec2);

t_vec4			vec4_ini(long double in[4]);
t_vec4			vec4m_vec4(t_vec4 vec1, t_vec4 vec2);
long double		vec4_ccw(t_vec4 vec1, t_vec4 vec2, t_vec4 vec3);
t_vecn			*vecn_ini(size_t n);
t_vecn			*vecn_cpy(float *vecn, size_t n);

t_mat4			mat4_rotz(double theta);
t_mat4			mat4_roty(double theta);
t_mat4			mat4_rotx(double theta);
t_mat4			mat4_trans(long double s[3]);
t_mat4			mat4_scales(long double s[4]);
t_mat4			mat4_ini(void);
t_mat4			mat4_iden(void);
t_mat4			mat4_pro(void);
t_mat4			mat4_perps(t_vec4 vec);
t_mat4			mat4_perps2(t_vec4 vec, long double ar);
t_mat4			mat4_pinhole(t_vec4 vec, long double ar);
t_mat4			mat4_mat4(t_mat4 mat1, t_mat4 mat2);
t_vec4			mat4_vec4(t_mat4 mat4, t_vec4 vec4);
t_mat4			mat4_rot_inverse(t_mat4 mat);

t_matn			*matn_cpy(float *src, size_t n);
t_matn			*matn_ini(size_t n);
t_matn			*matn_iden(size_t n);
void			matn_scale_set(t_matn *matn, float *s, size_t n);
void			matn_scale_flat(t_matn *matn, float s, size_t n);
t_matn			*matn_scale_ini(float s, size_t n);
t_matn			*matn_scale_sini(float *s, size_t n);
t_matn			*matn_matn(t_matn *mat1, t_matn *mat2, size_t n);
t_vecn			*matn_vecn(t_matn *mat, t_vecn *vec, size_t n);
void			*matn_free(t_matn *matn, size_t n);

void			ft_memdel(void **ap);
void			ft_bzero(void *s, size_t n);
void			ft_strdel(char **as);
void			ft_strclr(char *s);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
void			ft_putchar(char c);
void			ft_putstr(char const *s);
void			ft_putendl(char const *s);
void			ft_putnbr(long n);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char const *s, int fd);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_puterr(char const *s);
void			ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void			ft_lstadd(t_list **alst, t_list *new);
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
void			ft_putpointer(void *p);
void			ft_strarrdel(char **strarr);
void			ft_strlower(char **str);
void			ft_strupper(char **str);
void			ft_strrep(char **str, char c, char n);
void			ft_strnrep(char **str, char c, char n, size_t len);

void			*ft_memset(void *b, int c, size_t len);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memchr(const void *s, int c, size_t n);
void			*ft_memalloc(size_t size);

size_t			ft_strlen(const char *s);
size_t			ft_nbrlen(long n);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t			ft_strclen(const char *s, char c);
size_t			ft_strrclen(const char *s, char c);
size_t			ft_baselen(long value, int base);

t_list			*ft_lstnew(void const *content, size_t content_size);
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));

t_rgb			rgb_conv(long color);
t_rgb			rgb_calc(t_rgb color1, t_rgb color2, char type);

char			**ft_strsplit(char const *s, char c);

char			*ft_strdup(const char *s1);
char			*ft_strcpy(char *dst, const char *src);
char			*ft_strncpy(char *dst, const char *src, size_t len);
char			*ft_strcat(char *s1, const char *s2);
char			*ft_strncat(char *s1, const char *s2, size_t n);
char			*ft_strchr(const char *s, int c);
char			*ft_strnchr(const char *s, int c, size_t len);
char			*ft_strrchr(const char *s, int c);
char			*ft_strstr(const char *haystack, const char *needle);
char			*ft_strnstr(const char *haystack, const char *needle,\
				size_t len);
char			*ft_strcreate(char const *s, size_t len);
char			*ft_strnew(size_t size);
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s);
char			*ft_itoa(int n);
char			*ft_itoa_base(long value, int base);
char			*ft_hxdm(long n);

char			base_conv(long value, int base);

int				ft_memcmp(const void *s1, const void *s2, size_t n);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_strcont(const char *str1, const char *str2);
int				ft_atoi(const char *str);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);
int				ft_sizeofchar(int c);
int				ft_sizeofint(int c);
int				ft_isupper(int c);
int				ft_islower(int c);
int				ft_skipempty(char *str);
int				ft_isspace(char c);
int				ft_iswspace(char c);
int				ft_strequ(char const *s1, char const *s2);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
int				get_next_line(const int fd, char **line);
int				rgb_color(unsigned int red, unsigned int green,
				unsigned int blue);
int				trgb_conv(t_rgb color);

int				ft_isnumpad(int key);
int				ft_isfunckey(int key);
int				ft_isnavkey(int key);
int				ft_iscontkey(int key);
int				ft_isnumkey(int key);
int				ft_isalphakey(int key);
int				ft_ismisckey(int key);
int				ft_iskey(int key);

long			ft_chrcount(char *str, char c);
long			ft_abs(long c);
long			atoi_conv(char c, int base);
long			ft_atoi_base(char *str, int base);
long			ft_power_to(long num, int power);
long			ft_power_base(long num, int power, int base);

float			ft_fabs(float c);

#endif
