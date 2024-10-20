#include "../minishell.h"

char *ft_strndup(const char *s, size_t n) 
{
    if (s == NULL) {
        return NULL; 
    }
    
    size_t len = strnlen(s, n);
    char *dup = (char *)malloc(len + 1); 

    if (dup == NULL) {
        return NULL; 
    }

    strncpy(dup, s, len);
    dup[len] = '\0';

    return dup;
}

char	*ft_strjoin_char(char *s, char c)
{
	char	*new_str;
	int		len;

	len = ft_strlen(s);
	new_str = (char *)malloc(len + 2);
	if (!new_str)
		return (NULL);
	ft_memcpy(new_str, s, len);
	new_str[len] = c;
	new_str[len + 1] = '\0';
	return (new_str);
}
