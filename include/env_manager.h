/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vladimir <vladimir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 12:24:15 by swillis           #+#    #+#             */
/*   Updated: 2022/06/16 10:16:07 by vladimir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_MANAGER_H
# define ENV_MANAGER_H

//********** ENV_MANAGER **********//
char	**copy_environment(char **env);
char	**init_environment(void);
char	**env_getcwd(char **env);
char	**env_getpath(char **env);

//********** ENV_MANAGER_UTILS **********//
int		ft_tbllen(char **tbl);
char	**tbl_append(char **env, char *str);
int		env_findkeypos(char *key, char **env);
char	*env_findkeyvalue(char *key, char **env);
char	**env_export(char *key, char *value, char **env);

#endif
