#include "vm.h"

/*
	Changed arena.all_players[] array into type t_header to
	avoid confusion with the list of processes.

	Started building VM loop. 
*/

/*
** Adds a t_process element to the end of the list of processes.
*/

t_process	*vm_free_processes(t_process **lst)
{
	t_process	*tmp;

	tmp = *lst;
	while (*lst)
	{
		tmp = *lst;
		*lst = lst[0]->next;
		mdel((void **)&tmp);
	}
	return (NULL);
}

t_process	*create_process(t_arena arena, t_process *process_lst, \
int player_id)
{
	t_process	*new_process;

	new_process = minit(sizeof(t_process));
	if (!new_process)
		vm_error("Malloc failed in create_process\n");
	new_process->id = player_id;
	new_process->pc = &arena.mem[MEM_SIZE / arena.player_count * player_id];
	new_process->next = process_lst;
	return (new_process);
}

t_process	*init_processes(t_arena arena)
{
	t_size		player_id;
	t_process	*process_lst;

	process_lst = NULL;
	player_id = 0;
	while (++player_id <= arena.player_count)
		process_lst = create_process(arena, process_lst, player_id);
	return (process_lst);
}

void	vm_init_battle(t_arena arena, t_battle *battle)
{
	mzero(battle, sizeof(t_battle));
	battle->cycle_to_die = CYCLE_TO_DIE;
	battle->last_alive = arena.player_count;
}

//
// a carriage is dead if a carriage hasn’t performed live in a long 
// time (not in one whole cycles_to_die cycle or more) or if 
// cycles_to_die is <= 0.
//

//
// If CYCLE_TO_DIE wasn’t decreased since MAX_CHECKS checkups, decrease it.
// What happens after MAX_CHECKS? If above statement is true, will CYCLE_TO_DIE
// be decreased by CYCLE_DELTA?

/*
** Cycles are executed until a live check occurs. Checks occur every
** battle.cycle_to_die cycles.
*/

void	vm_battle(t_arena arena)
{
	t_process	*process_lst;
	t_battle	battle;
	t_uint32	processes_alive;

	process_lst = init_processes(arena);
	vm_test_print_processes(process_lst);
	vm_introduce_champs(arena);
	vm_init_battle(arena, &battle);
	processes_alive = arena.player_count;
	while (process_lst)
	{
		while (battle.cycles_since_check++ < battle.cycle_to_die)
			vm_execute_cycle(process_lst, &battle);
		vm_check_live(process_lst, &battle);
	}
	process_lst = vm_free_processes(&process_lst);
}
