#include "vm.h"

t_reg_addr vm_get_reg_addr(
		t_process *p,
		t_size i)
{
	if (i < 1 || i > REG_NUMBER)
	{
		print("Reg %llu out of bounds!\n", i);
		return (NULL);
	}
	return (p->registers[i - 1]);
}