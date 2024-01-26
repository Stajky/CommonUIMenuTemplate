// 

#pragma once

#include "CoreMinimal.h"
#include "CmtWidgetController.h"
#include "CommonUIMenuTemplate/Data/PlayerAttributes.h"
#include "PlayerOverlayController.generated.h"

class ACmtPlayerState;
class ACmtPlayerController;
struct FGameplayTag;
struct FSimpleTagMessage;
struct FSimpleTagMessage_Float;
struct FSimpleTagMessage_Int;
/**
 * 
 */
UCLASS()
class COMMONUIMENUTEMPLATE_API UPlayerOverlayController : public UCmtWidgetController
{
	GENERATED_BODY()

public:

	UPlayerOverlayController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	/** ~UCmtWidgetController functions */
	virtual void BindDataGenerators() override;
	/** ~End of UCmtWidgetController functions */

	void SetDataGeneratorsPointers(ACmtPlayerState* PS);

	UFUNCTION(BlueprintCallable)
	FPlayerAttributes GetPlayerAttributes() const;
	
protected:

	FORCEINLINE void SendIntMessage(FGameplayTag Tag, int32 Value) const;
	FORCEINLINE void SendFloatMessage(FGameplayTag Tag, float Value) const;

private:
	TObjectPtr<ACmtPlayerState> PlayerState;
};


