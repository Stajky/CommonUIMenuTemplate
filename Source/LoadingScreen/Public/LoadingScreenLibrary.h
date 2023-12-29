// 

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LoadingScreenSettings.h"
#include "Templates/SharedPointer.h"
#include "LoadingScreenModule.h"
#include "LoadingScreenLibrary.generated.h"

/**
 * 
 */
UCLASS()
class LOADINGSCREEN_API ULoadingScreenLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = Loading)
	static void StartLoadingScreen(const FLevelLoadingScreenSettings& Settings, float MinimumLoadingScreenDisplayTime);


	UFUNCTION(BlueprintCallable, Category = Loading)
	static void StopLoadingScreen();
};
