// 

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CmtLibrary.generated.h"

class UInputActionToTagMap;
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
	static void CmtSetMouseInputMode(APlayerController* PlayerController, bool bMouseVisible, bool bIgnoreLookInput, bool bIgnoreMoveInput);


	UFUNCTION(BlueprintCallable,  Meta=(DefaultToSelf="WidgetContextObject"))
	static void SendIntMessage(const UObject* WorldContextObject, FGameplayTag Tag, int32 Value);

	UFUNCTION(BlueprintCallable, Meta=(DefaultToSelf="WidgetContextObject"))
	static void SendFloatMessage(const UObject* WorldContextObject, FGameplayTag Tag, float Value);
	
	UFUNCTION(BlueprintCallable, Meta=(DefaultToSelf="WidgetContextObject"))
	static void SendChangeSettingDescriptionMessage(const UObject* WorldContextObject, FText Value);
};


