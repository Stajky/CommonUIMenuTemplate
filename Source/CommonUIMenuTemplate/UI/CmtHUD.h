// 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CmtHUD.generated.h"

class APlayerController;
class UPlayerOverlay;
class UPlayerOverlayController;

/**
 * Modular HUD
 */
UCLASS()
class COMMONUIMENUTEMPLATE_API ACmtHUD : public AHUD
{
	GENERATED_BODY()
public:
	ACmtHUD(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	//~UObject interface
	virtual void PreInitializeComponents() override;
	//~End of UObject interface

	//~AActor interface
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	//~End of AActor interface

	UPlayerOverlayController* GetPlayerOverlayWidgetController();

	UFUNCTION(BlueprintCallable)
	void ShowPlayerOverlay();

private:
	void InitPlayerOverlayController(APlayerController* PC);
	
protected:
	UPROPERTY()
	TObjectPtr<UPlayerOverlay>  PlayerOverlayWidget;	

	UPROPERTY(EditAnywhere)
	TSubclassOf<UPlayerOverlay> PlayerOverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UPlayerOverlayController> PlayerOverlayWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UPlayerOverlayController> PlayerOverlayWidgetControllerClass;
};
