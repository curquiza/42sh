#ifndef COMPLETION_H
# define COMPLETION_H

typedef struct		s_rlist
{
	char			*file;
	int				size_file;
	int				type;
	struct s_rlist	*next;
}					t_rlist;

typedef struct			s_match
{
	t_rlist				*list;
	int					i;
	int					nbr_character;
	int					size_list;
	int					j;
	int					size;
}						t_match;

typedef struct			s_completion
{
	char				*path;
	char				*string;
	char				*buff_cursor;
	char				*after_cursor;
}						t_completion;

void	clear_list_s(t_rlist **li);
//char	*ft_strndup(char *str, int size);
int		lenght_rlist_s(t_rlist *li);
void	push_back_s(t_rlist **list, const char *str, int type);
int		clear_tab(char **board);
int		ft_calc_position(t_tc *tool);
size_t	ft_rstrlen(const char *s);

void				ft_completion_romain(t_tc *tool);
int					ft_start_completion(t_completion data_compl, \
							t_tc *tool, DIR **rep);
int					ft_getdata_dir(t_completion *data_compl);
void				ft_getdata(t_completion *data_compl, t_tc *tool);
int					completion_dir(t_completion data_comple, t_tc *tool);
void				stock_completion(t_rlist *list, t_completion data_comple,\
															t_tc *tool);
char				*ft_getsmall_file(t_rlist *list);
int					countnbr_match(t_rlist *list, char *small_file);
void				stock_completion_match(t_completion data_comple, \
									int nbr, char *file, t_tc *tool);
int					ft_getbigsize_file(t_rlist *list);
void				display_all_completion(t_rlist *list, t_tc *tool, \
																int big_size);
void				display_all_current(t_tc *tool, \
													t_completion data_comple);
t_rlist				*ft_getfiles(t_completion data_comple,\
													char *temporary, int type);
t_rlist				*ft_getfiles_opt(t_completion data_comple, char *temporary,
																	int type);
int					ft_start_completion_current(t_completion data_comple, \
															t_tc *tool);
t_rlist				*ft_getfiles_curr(t_completion *data_comple,\
													char *temporary, int type);
t_rlist				*ft_getfiles_opt_curr(t_completion *data_comple,\
													char *temporary, int type);
t_rlist				*ft_getfiles_all(t_completion data_comple, char *temporary,
																	int type);
t_rlist				*ft_getfiles_all_opt(t_completion data_comple,\
												char *temporary, int type);
void				stock_comple_curr(t_completion data_comple, t_rlist *list, \
															t_tc *tool);
void				init_var(char **temporary, int *nbr);
int					completion_command(t_tc *tool, \
								t_completion data_comple);
void				ft_completion_after_command(t_tc *tool, \
													t_completion data_comple);
void				stockafter_command(t_tc *tool, \
									t_completion data_comple, t_rlist *list);
void				stock_after_match(t_tc *tool, t_completion \
											data_comple, t_rlist *list, int nbr);

#endif
