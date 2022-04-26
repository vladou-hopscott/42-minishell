
#ifndef PARSING_H
# define PARSING_H

#define CHARSET_SEP "<>|"
#define CHARSET_SPACE_TABS " \n\v\t\f\r"

//enum sert à créer un index de 0 à N (ou bien à partir de la valeur ascii du caractère). https://linux.die.net/man/3/enum
//Ici on l'utilise pour chaque type de token :
// redirections
// args (tout le reste, les "littéraux")
// autres? parenthèses, single/double quotes, keywords spécifiques ?
typedef enum token_type
{
	PIPE = '|',
	RED_LEFT = '<',
	RED_RIGHT = '>',
	DOUBLE_RED_LEFT,
	DOUBLE_RED_RIGHT,
	FILEOUT, //1er token apres '>'
	FILEIN, //1er token apres '<'
	FILEOUT_APPEND, //1er token apres ">>"
	HEREDOC_LIMIT, //1er token apres "<<"
	STR,
	BUILTIN, //type a rajouter : identifier avec une fonction isbuiltin sur un token => est-ce que c'est utile ?
} t_token_type;

typedef enum quote
{
	SINGLE_QUOTE = '\'',
	DOUBLE_QUOTE = '\"',
	NO_QUOTE
} t_quote;

// liste chaînée. Chaque token représente un caractère tokenisé, chaîné au token précédent / suivant
typedef struct s_token
{
	t_token_type	type;
	char			*value;
	int				quote;
	struct s_token	*prev;
	struct s_token	*next;
} t_token;

typedef struct s_cmd_line
{
	char				*cmd;
	t_token				*token_lst;
	struct s_cmd_line	*next;
} t_cmd_line;

#endif
