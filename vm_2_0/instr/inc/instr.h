#ifndef INSTR_H
# define INSTR_H

# include "vm.h"
# include "corewar.h"

typedef struct s_arena t_arena;
typedef struct s_process t_process;
typedef struct s_instr t_instr;
typedef void (*t_exec)(t_arena *, t_process *);

void	vm_instr_ld(t_arena *a, t_process *p);
void	vm_instr_null(t_arena *a, t_process *p);
t_size	vm_instr_size(t_instr *src);

static const t_exec g_instr_funcs[] =
{
	vm_instr_null,
	vm_instr_null,
	vm_instr_null,
	vm_instr_null,
	vm_instr_null,
	vm_instr_null,
	vm_instr_null,
	vm_instr_null,
	vm_instr_null,
	vm_instr_null,
	vm_instr_null,
	vm_instr_null,
	vm_instr_null,
	vm_instr_null,
	vm_instr_null,
	vm_instr_null,
};

#endif