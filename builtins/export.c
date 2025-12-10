/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 14:36:38 by banne             #+#    #+#             */
/*   Updated: 2025/12/09 13:46:04 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//int get_type(char *arg)
//{
//    int i;

//    i = 0;
//    if (!arg || (!ft_isalpha(arg[0]) && arg[0] != '_'))
//        return (EXPORT_INVALID);
//    while (arg[i] && arg[i] != '=' && arg[i] != '+')
//        i++;
//    if (!arg[i])
//        return (EXPORT_NO_VALUE);
//    if (arg[i] == '+' && arg[i + 1] == '=')
//        return (EXPORT_APPEND);
//    if (arg[i] == '=')
//        return (EXPORT_SET);
//    return (EXPORT_INVALID);
//}

//t_export extract_export(char *arg)
//{
//    t_export export;

//    export.type = get_type(arg);
//    if (export.type == EXPORT_INVALID)
//    {
//        export.value = NULL;
//        export.key = NULL;
//    }
//    else if (export.type == EXPORT_APPEND)
//    {
//        export.key = ft_substr(arg, 0, (size_t)(ft_strchr(arg, '+') - arg));
//        export.value = ft_strdup(ft_strchr(arg, '=') + 1);
//    }
//    else if (export.type == EXPORT_SET)
//    {
//        export.key = ft_substr(arg, 0, (size_t)(ft_strchr(arg, '=') - arg));
//        export.value = ft_strdup(ft_strchr(arg, '=') + 1);
//    }
//    else // EXPORT_NO_VALUE
//    {
//        export.key = ft_strdup(arg);
//        export.value = NULL;
//    }
//    return (export);
//}

//void get_new_env(t_env *env, t_export export)
//{
//    char **new_envp;

//    new_envp = NULL;
//    if (env_exist(env, export.key))
//    {
//        if (export.type == EXPORT_SET)
//            new_envp = env_update(env, export);
//        else if (export.type == EXPORT_APPEND)
//            new_envp = env_add(env, export);
//    }
//    else
//        new_envp = env_add(env, export);
//    if (new_envp)
//    {
//        free_envp(env->envp);
//        env->envp = new_envp;
//    }
//    free(export.key);
//    free(export.value);
//}

//int ft_export(t_env *env, char **args)
//{
//    int i;
//    t_export export;

//    i = 1;
//    if (!args[1])
//        return (0);
//    while (args[i])
//    {
//        export = extract_export(args[i]);
//        if (export.type == EXPORT_INVALID)
//        {
//            fprintf(stderr, "export: `%s': not a valid identifier\n", args[i]);
//            i++;
//            return (1);
//        }
//        get_new_env(env, export);
//        i++;
//    }
//    return (0);
//}
