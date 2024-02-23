// 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CmtHUD.generated.h"

class UCheatWindow;
class UCheatWidgetController;
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
	
	UFUNCTION(BlueprintCallable)
	UPlayerOverlayController* GetPlayerOverlayWidgetController();
	UFUNCTION(BlueprintCallable)
	UCheatWidgetController* GetCheatWidgetController();
	
protected:
	//~UObject interface
	virtual void PreInitializeComponents() override;
	//~End of UObject interface

	//~AActor interface
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	//~End of AActor interface
	

	UFUNCTION(BlueprintCallable)
	void ShowPlayerOverlay();

private:
	void SetupPlayerOverlayController(APlayerController* PC);
	void SetupCheatWidgetController(APlayerController* PC);
	
protected:
	
	/* ~Player Overlay Widget */
	UPROPERTY()
	TObjectPtr<UPlayerOverlay>  PlayerOverlayWidget;	

	UPROPERTY(EditAnywhere)
	TSubclassOf<UPlayerOverlay> PlayerOverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UPlayerOverlayController> PlayerOverlayWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UPlayerOverlayController> PlayerOverlayWidgetControllerClass;
	/* ~End of Player Overlay Widget */

	
	/* ~Cheat Widget */
	UPROPERTY()
	TObjectPtr<UCheatWindow>  CheatWidget;	

	UPROPERTY(EditAnywhere)
	TSubclassOf<UCheatWindow> CheatWidgetClass;
	
	UPROPERTY()
	TObjectPtr<UCheatWidgetController> CheatWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UCheatWidgetController> CheatWidgetControllerClass;
	/* ~End of Cheat  Widget */
	
};
