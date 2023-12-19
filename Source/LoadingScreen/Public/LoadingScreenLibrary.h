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

	/**
	 * Checks to see if this module is loaded and ready. It is only valid to call Get() if IsAvailable() returns true.
	 *
	 * @return True if the module is loaded and ready to use
	 */
	UFUNCTION(BlueprintCallable, Category = Loading)
	static bool IsLoadingScreenAvailable();

	UFUNCTION(BlueprintCallable, Category = Loading)
	static void StartLoadingScreen(const FLevelLoadingScreenSettings& Settings);
	
};
