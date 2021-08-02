#include "asm.h"
#include "ast.h"
#include "validate.h"

int	asm_validate_ast(t_output_data *data, t_astnode *tree)
{
	int	ret;

	ret = asm_visit_program(tree, &data->symbols, &data->header);
	if (ASM_PRINT_DEBUG)
		asm_print_symbol_list(&data->symbols,
			"Symbol table after first pass through AST:");
	return (ret);
}