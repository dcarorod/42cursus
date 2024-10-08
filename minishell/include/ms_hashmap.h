/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_hashmap.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proton <proton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 17:00:40 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/09/24 17:30:15 by proton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_HASHMAP_H
# define MS_HASHMAP_H

# include <stdlib.h>

# define HM_INITIAL_BUCKET_SIZE 128
# define HM_LOAD_FACTOR_THRESHOLD 0.75

typedef struct s_indexes
{
	size_t	i;
	size_t	j;
}	t_indexes;

/*
	Environment variable types:
	- ENV: Regular environment variable
	- EXPORT: Variable marked for export
	- LOCAL: Local variable (not exported)
	- ENV_EXP: Environment variable that is also exported
*/
typedef enum s_env_type
{
	ENV,
	EXPORT,
	LOCAL,
	ENV_EXP,
	QMARK,
	ALLTYPES
}	t_env_type;

/*
	Hashmap node (env):
	- key: env variable key
	- value: env variable value
	- prev_value: previous variable value
	- type: Type of env variable
	- next: Pointer to the next node in the bucket
*/
typedef struct s_env_entry
{
	t_env_type			type;
	char				*key;
	char				*value;
	char				*prev_value;
	struct s_env_entry	*next;
}	t_env_entry;

/*
	Hashmap structure:
	- buckets: Array of buckets pointers
	- size: Number of buckets
	- num_entries: number of entries in the map
*/
typedef struct s_hashmap
{
	size_t		size;
	size_t		num_entries;
	t_env_entry	**buckets;
}	t_hashmap;

/*
	Environment List structure:
	- entries: Array of environment entries (not hashed)
	- num_entries: Total number of entries
	- env_count: Count of ENV variables
	- exp_count: Count of EXPORT variables
	- local_count: Count of LOCAL variables
	- env_exp_count: Count of ENV_EXP variables
	- qmark_count: Count of QMARK variables
*/
typedef struct s_env_vault
{
	t_env_entry	**entries;
	size_t		num_entries;
	size_t		env_count;
	size_t		exp_count;
	size_t		local_count;
	size_t		env_exp_count;
	size_t		qmark_count;
}	t_env_vault;

/* Utils */
size_t		djb2_hash(const char *key, size_t map_size);
int			hashmap_resize(t_hashmap *map);

/* Cleanup */
void		*free_env_entry(t_env_entry *entry);
void		*free_buckets(t_env_entry **buckets, size_t size);
void		*hashmap_free(t_hashmap *map);

/* Hahsmap ops */
t_hashmap	*hashmap_create(size_t size);
int			hashmap_remove(t_hashmap *map, const char *key);
const char	*hashmap_get(t_hashmap *map, const char *key);
int			hashmap_update(t_hashmap *map,
				const char *key, const char *new_value, t_env_type type);
int			hashmap_insert(t_hashmap *map,
				const char *key, const char *value, t_env_type type);
t_hashmap	*hashmap_init(char **envp);
t_hashmap	*hashmap_copy(t_hashmap *map);
void		*vault_free(t_env_vault *vault);
t_env_vault	*vault_create(size_t num_entries);
t_env_vault	*hashmap_to_vault(t_hashmap *map);
void		vault_sort(t_env_vault *vault);
void		vault_print_export(t_env_vault *sorted_vault);

/* Debug */
void		print_hashmap(t_hashmap *map);
void		vault_print_by_type(t_env_vault *sorted, t_env_type type);

#endif
