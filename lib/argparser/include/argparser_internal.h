#ifndef ARGPARSER_INTERNAL_H
# define ARGPARSER_INTERNAL_H

# include "argparser.h"

# define ARGP_EXIT_PARSE_ERROR		-1
# define ARGP_MAX_WIDTH				60

static const t_argparser_option	g_default_options[] = {
	{"help", 1, 0, 0, "Print this help message"},
	{"usage", 2, 0, 0, "Print a short usage message"},
	{0, 0, 0, 0, 0}
};

int							_argparser_parse_default_opt(int key, char *arg,
								t_argparser_state *state);
void						_argparser_print_usage(t_argparser_state *state);
const t_argparser_option	*_argparser_get_option(char *argument,
								const t_argparser_option *options,
								int long_option);
char						*_argparser_get_arg(t_argparser_state *state);
int							_argparser_get_short_opt(int *key,
								char **arg,
								const t_argparser *argp,
								t_argparser_state *state);
int							_argparser_get_default_opt(int *key,
								char **arg,
								t_argparser_state *state,
								int long_option);
int							_argparser_get_long_opt(int *key,
								char **arg,
								const t_argparser *argp,
								t_argparser_state *state);
void						_argparser_long_usage(t_argparser_state *state);
void						_argparser_help(t_argparser_state *state);

#endif
