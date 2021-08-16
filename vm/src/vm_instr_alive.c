#include "vm.h"

void vm_instr_alive(
		t_arena *a,
		t_process *p)
{
	t_process	*cur;
	t_size		mem_i;
	t_uint64	id;

	mem_i = p->pc;
	mem_i = (mem_i + 1) % MEM_SIZE;
	id = vm_get_val(a, p, T_DIR, &mem_i);
	cur = a->processes;
	while (cur && cur->id != id)
		cur = cur->next;
	if (!cur)
		vm_error("Process with id not found!\n");
	cur->last_live = a->battle.cycles_executed;
	p->pc = mem_i;
}