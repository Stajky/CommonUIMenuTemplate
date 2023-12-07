#pragma once

#include "CoreMinimal.h"
#include "GameUIManagerSubsystem.h"
#include "CmtGameUIManagerSubsystem.generated.h"


/**
*
* Manager that handles visibility of the base layer of common UI
*
* For this to work you need to connect it with YOUR Game UI policy, by setting it in config
* In this project its:
* [/Script/CommonUIMenuTemplate.CmtUIManagerSubsystem]
* DefaultUIPolicyClass=/Game/UI/BP_GameUIPolicy.BP_GameUIPolicy_C
* 
*/
UCLASS(meta=(DisplayName="Cmt UI Manager Subsystem", Category=Cmt))
class COMMONUIMENUTEMPLATE_API UCmtGameUIManagerSubsystem : public UGameUIManagerSubsystem
{
	GENERATED_BODY()
public:
	UCmtGameUIManagerSubsystem();

	//~USubsystem interface
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	//~End of USubsystem interface
	
private:
	bool Tick(float DeltaTime);
	void SyncRootLayoutVisibilityToShowHUD();

	FTSTicker::FDelegateHandle TickHandle;	
};
