#include "instr.h"

void	vm_print_instr_arg(t_arg *arg)
{
	print("%s%s%s ", BLU, vm_type_name(arg->type), NRM);
	reg_print(&arg->data, NRM);
}
