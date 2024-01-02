// 

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CmtLibrary.generated.h"

class UEnhancedInputLocalPlayerSubsystem;
/**
 * 
 */
UCLASS()
class COMMONUIMENUTEMPLATE_API UCmtLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UCmtLibrary() {}

	/**
	 * Get the EnhancedInput LocalPlayer Subsystem for the player represented by PlayerController
	 * @param PlayerController
	 * @return nullptr, or if available, the EnhancedInput LocalPlayer Subsystem for the player
	 */
	UFUNCTION(BlueprintCallable)
	static UEnhancedInputLocalPlayerSubsystem* GetEnhancedInputLocalPlayerSubsystem(const APlayerController* PlayerController);

	UFUNCTION(BlueprintCallable)
	static void CmtSetInputMode(APlayerController* PlayerController, bool bMouseVisible, bool bIgnoreLookInput, bool bIgnoreMoveInput);
};
