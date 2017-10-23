/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tc.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/30 16:42:46 by curquiza          #+#    #+#             */
/*   Updated: 2017/10/23 12:20:16 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TC_H
# define TC_H

/*
** init_reset.c
*/

int		ft_init_tc(void);
void	ft_reset_tc(t_tc *tool);
void	ft_init_struct_tc(t_tc *tool, int prompt_len);

/*
** insert_char.c
*/

void	ft_add_n_char(t_tc *tool, char *buff, int pos, int len);
void	ft_insert_eol(t_tc *tool);
void	ft_insert(char *buff, t_tc *tool);

/*
** delete.c
*/

void	ft_delete_n_char(t_tc *tool, int pos, int len);
void	ft_delete_back(t_tc *tool);
void	ft_delete_front(t_tc *tool);

/*
** move_left_right.c
*/

void	ft_go_to_eol(t_tc *tool);
void	ft_move_left(t_tc *tool);
void	ft_move_right(t_tc *tool);

/*
** move_up_down.c
*/

void	ft_move_up(t_tc *tool);
void	ft_move_down(t_tc *tool);

/*
** move_start_end.c
*/

void	ft_move_start(t_tc *tool);
void	ft_move_end(t_tc *tool);

/*
** move_word.c
*/

void	ft_move_word_left(t_tc *tool);
void	ft_move_word_right(t_tc *tool);

/*
** copy_cut.c
*/

void	ft_copy(t_tc *tool);
void	ft_cut(t_tc *tool);

/*
** ctrl_d.c
*/

int		ft_check_and_restore_ctrld(t_shell *shell);
void	ft_ctrl_d(t_tc *tool);

/*
** clear.c
*/

void	ft_clear_all_lines(t_tc *tool);
void	ft_clean_buff(t_tc *tool);

/*
** replace_cursor.c
*/

void	ft_replace_cursor(t_tc *tool);

/*
** completion.c
*/

void	ft_completion(t_tc *tool, t_comp_ctrl *ctrl);

/*
** compl_init_reset.c
*/

void	ft_get_comp_word(t_tc *tool, t_comp_ctrl *ctrl);
int		ft_get_comp_status(t_tc *tool, t_comp_ctrl *ctrl);
void	ft_erase_comp(t_comp_ctrl *ctrl);
void	ft_reset_compl(t_comp_ctrl *ctrl);

/*
** compl_get_all_candidates.c
*/

void	ft_complst_pushback(t_comp_ctrl *ctrl, char *word);
char	*ft_complete_name(char *word, t_comp_ctrl *ctrl);
int		ft_check_hidden_file(t_comp_ctrl *ctrl, char *name);
int		ft_get_all_candidates(t_comp_ctrl *ctrl, t_tc *tool);

/*
** compl_cmd_words.c
*/

int		ft_get_cmd_words(t_comp_ctrl *ctrl);

/*
** compl_file_words.c
*/

int		ft_get_file_words(t_comp_ctrl *ctrl);

/*
** compl_check.c
*/

int		ft_check_user_right(char *path, char *name);
int		ft_check_is_dir(char *path, char *name);

/*
** compl_matches.c
*/

void	ft_put_matched_part(t_tc *tool, char *to_find, char *match);
int		ft_check_other_words(int i, int len, t_comp *comp);
char	*ft_get_matched_part(t_comp_ctrl *ctrl);

/*
** compl_ascii_sort.c
*/

void	ft_ascii_sort_words(t_comp **comp);

/*
** compl_display.c
*/

void	ft_put_comp_prompt(t_tc *tool);
int		ft_word_len_max(t_comp *comp);
void	ft_put_all_words(t_tc *tool, t_comp *comp);

/*
** histo_add_line.c
*/

void	ft_histolst_del(t_histo **alst);
void	ft_del_old_histo(t_histo_ctrl *ctrl);
void	ft_add_histo_line(t_tc *tool, t_histo **histo, t_histo_ctrl *ctrl);

/*
** histo_up_down.c
*/

char	*ft_get_line_with_pos(t_histo *histo, int n);
void	ft_histo_up(t_tc *tool, t_histo_ctrl *ctrl);
void	ft_histo_down(t_tc *tool, t_histo_ctrl *ctrl);

/*
** histo_event.c
*/

void	ft_histo_event(t_tc *tool, t_histo_ctrl *ctrl);

/*
** ctrl_r.c
*/

void	ft_ctrl_r(t_tc *tool);
char	*ft_histo_matches(char *buff, t_histo *histo);
void	ft_put_ctrl_r_rslt(t_tc *tool, t_histo_ctrl *ctrl);

/*
** interpreter.c
*/

void	ft_interpreter(char *buff, t_tc *tool);
void	ft_eol_interpreter(char *buff, t_tc *tool);
void	ft_basic_interpreter(char *buff, t_tc *tool);
void	ft_histo_interpreter(char *buff, t_tc *tool);
void	ft_compl_interpreter(char *buff, t_tc *tool);

/*
** read_line.c
*/

int		ft_termput(int c);
void	ft_read_line(char **line, int prompt_len);

#endif
