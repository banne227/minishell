#include stdbool.h

bool is_valid_identifier(char *arg)
{
    int i;

    i = 1;
    if (!arg || (!ft_isalpha(arg[0]) && arg[0] != '_'))
        return (false);
    while (arg[i])
    {
        if (!ft_isalnum(arg[i]) && arg[i] != '_')
            return (false);
        i++;
    } 
    return (true);
}

bool env_exist(t_env *env, char *arg)
{
    int i;
    int len;

    i = 0;
    len = strlen(arg);
    while (env->envp[i])
    {
        if (ft_strncmp(env->envp[i], arg, len) == 0 && env->envp[i][len] == '=')
            return (true);
        i++;
    }
    return (false);
}

void ft_unset(t_env *env, char **args)
{
    int i;

    i = 1;
    while (args[i])
    {
        if (is_valid_identifier(args[i]) && env_exist(env, args[i]))
            env_remove(env, args[i]);
        i++;
    }
}

