void copy_env(t_env *env, char **new_envp)
{
    int i;

    i = 0;
    while (env->envp[i])
    {
        new_envp[i] = ft_strdup(env->envp[i]);
        i++;
    }
}

void copy_update_env(t_env *env, char **new_envp, int env_size, t_export export)
{
    int i;
    char *new_var;

    i = 0;
    new_var = malloc(sizeof(char) * (strlen(export.key) + 1 + strlen(export.value) + 1));
    if (!new_var)
        return ;
    write_env_var(new_var, export, strlen(export.key));
    while (i < env_size)
    {
        if (ft_strncmp(env->envp[i], export.key, strlen(export.key)) != 0 
                || env->envp[i][strlen(export.key)] != '=')
                new_envp[i] = ft_strdup(env->envp[i]);
        else
            new_envp[i] = new_var;
        i++;
    }
    new_envp[env_size] = NULL;
}

// void copy_remove_env(t_env *env, char **new_envp, int env_size, t_export export)
// {
//     int i;
//     int j;

//     j = 0;
//     i = 0;
//     while (i < env_size)
//     {
//         if (ft_strncmp(env->envp[i], export.key, strlen(export.key)) != 0 
//                 || env->envp[i][strlen(export.key)] != '=')
//         {
//             new_envp[j] = ft_strdup(env->envp[i]);
//             j++;
//         }
//         i++;
//     }
//     new_envp[j] = NULL;
// }