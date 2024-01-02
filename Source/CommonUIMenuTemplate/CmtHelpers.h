// 

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CmtHelpers.generated.h"

class UEnhancedInputLocalPlayerSubsystem;
/**
 * 
 */
UCLASS()
class COMMONUIMENUTEMPLATE_API UCmtHelpers : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UCmtHelpers() {}

	/**
	 * Get the EnhancedInput LocalPlayer Subsystem for the player represented by PlayerController
	 * @param PlayerController
	 * @return nullptr, or if available, the EnhancedInput LocalPlayer Subsystem for the player
	 */
	UFUNCTION(BlueprintCallable)
	static UEnhancedInputLocalPlayerSubsystem* GetEnhancedInputLocalPlayerSubsystem(const APlayerController* PlayerController);
};
