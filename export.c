typedef enum e_export_type
{
    EXPORT_INVALID,
    EXPORT_NO_VALUE,     // VAR
    EXPORT_SET,          // VAR=value
    EXPORT_APPEND        // VAR+=value
}   t_export_type;

typedef struct s_export
{
    char                *key;
    char                *value;
    t_export_type       type;
}   t_export;

int get_type(char *arg)
{
    int i;

    i = 0;
    if (!arg || (!ft_isalpha(arg[0]) && arg[0] != '_'))
        return (EXPORT_INVALID);
    while (arg[i] && arg[i] != '=' && arg[i] != '+')
        i++;
    if (!arg[i])
        return (EXPORT_NO_VALUE);
    if (arg[i] == '+' && arg[i + 1] == '=')
        return (EXPORT_APPEND);
    if (arg[i] == '=')
        return (EXPORT_SET);
    return (EXPORT_INVALID);
}

t_export extract_export(char *arg)
{
    t_export export;

    export.type = get_type(arg);
    if (export.type == EXPORT_INVALID)
    {
        export.value = NULL;
        export.key = NULL;
    }
    else if (export.type == EXPORT_APPEND)
    {
        export.key = ft_substr(arg, 0, ft_strchr(arg, '+') - arg);
        export.value = ft_strdup(ft_strchr(arg, '=') + 1);
    }
    else if (export.type == EXPORT_SET)
    {
        export.key = ft_substr(arg, 0, ft_strchr(arg, '=') - arg);
        export.value = ft_strdup(ft_strchr(arg, '=') + 1);
    }
    else // EXPORT_NO_VALUE
    {
        export.key = ft_strdup(arg);
        export.value = NULL;
    }
    return (export);
}

void get_new_env(t_env *env, t_export export)
{
    if (env_exist(env, export.key))
    {
        if (export.type == EXPORT_SET)
            env_update(env, export);
        else if (export.type == EXPORT_APPEND)
            env_append(env, export);
    }
    else
        env_add(env, export);
    free(export.key);
    free(export.value);
}

int ft_export(t_env *env, char **args)
{
    int i;
    t_export export;

    i = 1;
    if (!args[1])
    {
        print_sorted_env(env);
        return (0);
    }
    while (args[i])
    {
        export = extract_export(args[i]);
        if (export.type == EXPORT_INVALID)
        {
            fprintf(stderr, "export: `%s': not a valid identifier\n", args[i]);
            i++;
            return (1);
        }
        get_new_env(env, export);
        i++;
    }
    return (0);
}
