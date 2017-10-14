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
char	*ft_strndup(char *str, int size);
int		lenght_list_s(t_rlist *li);
void	push_back_s(t_rlist **list, const char *str, int type);
int		clear_tab(char **board);

void				ft_completion(t_line_edit *line, t_control_env *env);
int					ft_start_completion(t_completion data_compl, \
							t_line_edit *line, t_control_env *env, DIR **rep);
int					ft_getdata_dir(t_completion *data_compl);
void				ft_getdata(t_completion *data_compl, t_line_edit *line);
int					completion_dir(t_completion data_comple, t_line_edit *line);
void				stock_completion(t_list *list, t_completion data_comple,\
															t_line_edit *line);
char				*ft_getsmall_file(t_list *list);
int					countnbr_match(t_list *list, char *small_file);
void				stock_completion_match(t_completion data_comple, \
									int nbr, char *file, t_line_edit *line);
int					ft_getbigsize_file(t_list *list);
void				display_all_completion(t_list *list, t_line_edit *line, \
																int big_size);
void				display_all_current(t_line_edit *line, \
													t_completion data_comple);
t_list				*ft_getfiles(t_completion data_comple,\
													char *temporary, int type);
t_list				*ft_getfiles_opt(t_completion data_comple, char *temporary,
																	int type);
int					ft_start_completion_current(t_completion data_comple, \
															t_line_edit *line);
t_list				*ft_getfiles_curr(t_completion *data_comple,\
													char *temporary, int type);
t_list				*ft_getfiles_opt_curr(t_completion *data_comple,\
													char *temporary, int type);
t_list				*ft_getfiles_all(t_completion data_comple, char *temporary,
																	int type);
t_list				*ft_getfiles_all_opt(t_completion data_comple,\
												char *temporary, int type);
void				stock_comple_curr(t_completion data_comple, t_list *list, \
															t_line_edit *line);
void				init_var(char **temporary, int *nbr);
int					completion_command(t_line_edit *line, \
								t_completion data_comple, t_control_env *env);
void				ft_completion_after_command(t_line_edit *line, \
													t_completion data_comple);
void				stockafter_command(t_line_edit *line, \
									t_completion data_comple, t_list *list);
void				stock_after_match(t_line_edit *line, t_completion \
											data_comple, t_list *list, int nbr);

#endif
