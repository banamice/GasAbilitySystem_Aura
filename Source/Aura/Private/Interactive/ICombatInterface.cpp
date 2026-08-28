// 


#include "Interactive/ICombatInterface.h"


// Add default functionality here for any IICombatInterface functions that are not pure virtual.
uint32 IICombatInterface::GetPlayerLevel() const
{
	return 0;
}

FVector IICombatInterface::GetProjectileSpawnLocation() const
{
	return FVector::ZeroVector;
}
