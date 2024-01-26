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
	virtual void BindData() override;
	virtual void UnBindData() override;
	virtual void NativeActivateWidgetController() override;
	virtual void NativeDeactivateWidgetController() override;
	/** ~End of UCmtWidgetController functions */

	void Setup(ACmtPlayerState* PS);

	UFUNCTION(BlueprintCallable)
	FPlayerAttributes GetPlayerAttributes() const;
	
private:
	TObjectPtr<ACmtPlayerState> PlayerState;

	FDelegateHandle OnLevelChangedHandle;
	FDelegateHandle OnXPChangedHandle;
	FDelegateHandle OnHealthChangedHandle;
	FDelegateHandle OnManaChangedHandle;
};


