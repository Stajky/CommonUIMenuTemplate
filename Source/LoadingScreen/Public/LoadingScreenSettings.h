#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "UObject/ConstructorHelpers.h"
#include "LoadingScreenSettings.generated.h"

USTRUCT(BlueprintType)
struct LOADINGSCREEN_API FLoadingScreenSettings
{
	GENERATED_BODY()

	/**
	* All movie files must be locate at Content/Movies/ directory. Suggested format: MPEG-4 Movie (mp4). Enter file path/name without the extension.
	* E.g., if you have a movie name my_movie.mp4 in the 'Content/Movies' folder, then enter my_movie in the input field.
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FString> MoviePaths;
};



UCLASS(Config = "Game", defaultconfig, meta = (DisplayName = "Loading Screen"))
class LOADINGSCREEN_API ULoadingScreenEditorSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:

	ULoadingScreenEditorSettings(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	/**
	 * The startup loading screen when you first open the game. Setup any studio logo movies here.
	 */
	UPROPERTY(Config, EditAnywhere, Category = "General")
	FLoadingScreenSettings StartupLoadingScreen;

	/**
	 * The default loading screen that shows up whenever you open a new level.
	 */
	UPROPERTY(Config, EditAnywhere, Category = "General")
	FLoadingScreenSettings LevelLoadingScreen;
};