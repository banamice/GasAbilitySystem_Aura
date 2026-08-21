// 

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IHighLightInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UIHighLightInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class AURA_API IIHighLightInterface
{
	GENERATED_BODY()

public:
	virtual void EnableHighLight() = 0;
	virtual void DisableHighLight() = 0;
};
