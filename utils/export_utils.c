/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 16:15:10 by banne             #+#    #+#             */
/*   Updated: 2025/12/09 16:20:37 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int get_env_size(t_env *env)
{
    int i;

    i = 0;
    while (env->envp[i])
        i++;
    return (i);
}

void write_env_var(char *dest, t_export export, int len_key)
{
    int len_value;
    int i;

    i = 0;
    if (export.value)
    {
        len_value = strlen(export.value);
        while (i < len_key)
        {
            dest[i] = export.key[i];
            i++;
        }
        dest[i++] = '=';
        while (i < len_key + 1 + len_value)
        {
            dest[i] = export.value[i - len_key - 1];
            i++;
        }
        dest[i] = '\0';
    }
    else
    {
        len_value = 0;
        while (i < len_key)
        {
            dest[i] = export.key[i];
            i++;
        }
        dest[i] = '\0';
    }
}

char **env_add(t_env *env, t_export export)
{
    char   **new_envp;
    int     len;
    int     env_size;

    if (!export.key)
        return (0);
    env_size = get_env_size(env);
    new_envp = malloc(sizeof(char *) * (env_size + 2));
    if (!new_envp)
        return (0);
    if (export.value)
        len = strlen(export.key) + strlen(export.value) + 2;
    else
        len = strlen(export.key) + 1;
    new_envp[env_size] = malloc(sizeof(char) * len);
    if (!new_envp[env_size])
    {
        free(new_envp);
        return (0);
    }
    copy_env(env, new_envp);
    write_env_var(new_envp[env_size], export, strlen(export.key));
    new_envp[env_size + 1] = NULL;
    return (new_envp);
}

char **env_remove(t_env *env, t_export export)
{
    char **new_envp;
    int   env_size;

    env_size = get_env_size(env);
    new_envp = malloc(sizeof(char *) * env_size);
    if (!new_envp)
        return (0);
    if (!env_exist(env, export.key))
    {
        free(new_envp);
        return (env->envp);
    }
    copy_remove_env(env, new_envp, env_size, export);
    return (new_envp);
}

char **env_update(t_env *env, t_export export)
{
    int     env_size;
    char  **new_envp;

    env_size = get_env_size(env);
    new_envp = malloc(sizeof(char *) * (env_size + 1));
    if (!new_envp)
        return (0);
    copy_update_env(env, new_envp, env_size, export);
    return (new_envp);
}
