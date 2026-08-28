// 

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ICombatInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UICombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class AURA_API IICombatInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual uint32 GetPlayerLevel() const;
	
	virtual FVector GetProjectileSpawnLocation() const;
};
