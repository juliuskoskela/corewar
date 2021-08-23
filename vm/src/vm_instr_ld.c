#include "vm.h"

// ld T_DIR | T_IND src, T_REG dst
// Contains ACB
// If the first argument is T_IND, it represents the memory addr % IDX_MOD.
// Loads src in the register dst. src's value affects zf.

void vm_instr_ld(
		t_arena *a,
		t_process *p)
{
	t_size		mem_i;
	t_uint8		acb;
	t_mem_addr	src;
	t_reg_addr	dst;
	t_uint64	mem_addr;

	if ((a->verbosity & VM_VERBOSE_OPS) != 0)
		print("\t%s\n", "ld src, dst");
	// acb
	mem_i = (p->pc + 1) % MEM_SIZE;
	acb = a->mem[mem_i];
	mem_i = (mem_i + 1) % MEM_SIZE;

	// arg 1
	if (vm_check_acb(acb, 0) != DIR_CODE
		&& vm_check_acb(acb, 0) != IND_CODE)
		vm_error("Error arg 1 ld!\n");
	mem_addr = vm_get_val(a, p, vm_check_acb(acb, 0), &mem_i);
	if (vm_check_acb(acb, 0) == IND_CODE)
		mem_addr = mem_addr % IDX_MOD;
	src = vm_get_mem_addr(a, mem_addr);

	// arg 2
	if (vm_check_acb(acb, 1) != REG_CODE)
		vm_error("Error arg 2 ld!\n");
	dst = vm_get_reg_addr(p, a->mem[mem_i]);
	mem_i = (mem_i + 1) % MEM_SIZE;

	// store load to register
	print("mem addr = %d\n", mem_addr);
	vm_reverse_bytes(dst, src, 2);
	p->pc = mem_i;
}
