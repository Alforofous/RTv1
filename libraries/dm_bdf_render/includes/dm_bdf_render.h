/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dm_bdf_render.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 13:06:54 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/16 13:47:15 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DM_BDF_RENDER_H
# define DM_BDF_RENDER_H

# include "libft.h"
# include <fcntl.h>

typedef unsigned int	t_uint;

# ifndef S_2I
#  define S_2I

typedef struct s_2i
{
	int	x;
	int	y;
}				t_2i;
# endif

typedef struct s_glyph
{
	t_uint	unicode;
	int		encoding;
	t_uint	swidth[2];
	t_uint	dwidth[2];
	t_uint	bound_box[2];
	int		offset[2];
	t_uint	*bitmap;
	size_t	bitmap_line;
	size_t	bitmap_size;
}				t_glyph;

typedef struct s_prop
{
	int	ascent;
	int	descent;
	int	default_char;
}				t_prop;

typedef struct s_font
{
	t_prop	properties;
	t_glyph	*glyphs;
	t_uint	bound_box[2];
	int		offset[2];
	size_t	glyph_i;
	size_t	glyph_count;
}				t_font;

typedef struct s_pxl
{
	t_font	*font;
	void	(*f)(t_2i coords, t_uint color, void *param);
	void	*param;
}				t_pxl;

/*File loading functions*/
t_font	*load_font(char *path);

/*Font rendering functions*/
t_2i	render_glyph(int encoding, t_pxl *pxl, t_2i *crds, t_uint color);
t_2i	render_str(char *str, t_pxl *pxl, t_2i *crds, t_uint color);

/*Struct freeing function*/
t_font	*free_font(t_font **font);

/*Utility functions*/
t_glyph	*find_encoding(int encoding, t_font *font);

/*Debug functions*/
void	print_font_info(t_font *font);
void	print_glyph_info(t_glyph *glyph);
void	print_glyphs_bitmap(t_glyph *glyph);
void	print_font_params(t_font *font);
void	print_font_properties(t_prop *properties);

/*Font branch functions*/
int		params_branch(char *line, t_font *font);
int		properties_branch(char *line, t_font *font);
int		glyphs_branch(char *line, t_font *font);
int		glyphs_branch2(char *line, t_font *font);
int		bitmap_branch(char *line, t_font *font);

#endif
