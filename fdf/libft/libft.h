/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 16:53:28 by phakakos          #+#    #+#             */
/*   Updated: 2020/02/20 16:03:28 by phakakos         ###   ########.fr       */
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

t_rgb			rgb_conv(int color);
t_rgb			rgb_calc(t_rgb color1, t_rgb color2, char type);

char			**ft_strsplit(char const *s, char c);

char			*ft_strdup(const char *s1);
char			*ft_strcpy(char *dst, const char *src);
char			*ft_strncpy(char *dst, const char *src, size_t len);
char			*ft_strcat(char *s1, const char *s2);
char			*ft_strncat(char *s1, const char *s2, size_t n);
char			*ft_strchr(const char *s, int c);
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

#endif