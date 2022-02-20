/// opcode:		4 (0x04)
/// mnemonic:	add
/// name:		addition
/// params:		3 : { T_REG, T_REG, T_REG }
/// acb:		true
/// ncycles:	10
/// proto:		add lhs, rhs, dst
/// descript:	Computes lhs + rhs and and stores the result in register dst. Result affects zf.

#include "vm.h"

void	vm_instr_add(t_arena *a, t_process *p)
{
	t_int8 	addr[3];
	t_int32 lhs;
	t_int32 rhs;
	t_int32 result;

	if (!a)
		return ;
	// Get lhs, rhs, dst
	vm_reg_store((t_byte *)&addr[0], &p->current_instruction.args[0].data);
	vm_reg_store((t_byte *)&addr[1], &p->current_instruction.args[1].data);
	vm_reg_store((t_byte *)&addr[2], &p->current_instruction.args[2].data);
	if (addr[0] <= 0 || addr[0] > 16
		|| addr[1] <= 0 || addr[1] > 16
		|| addr[2] <= 0 || addr[2] > 16)
	{
		print("invalid register address\n");
		return ;
	}

	// Calculate result(lhs + rhs)
	vm_reg_store((t_byte *)&lhs, &p->registers[addr[0] - 1]);
	vm_reg_store((t_byte *)&rhs, &p->registers[addr[1] - 1]);
	result = lhs + rhs;

	// Update zf
	p->zf = (result == 0);

	// Store value to register dst
	vm_reg_load(&p->registers[addr[2] - 1], (t_byte *)&result);
}
