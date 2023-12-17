#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "UObject/ConstructorHelpers.h"
#include "MoviePlayer.h"
#include "LoadingScreenSettings.generated.h"



USTRUCT(BlueprintType)
/**
 * These are essentialy just settings for default movie player for startup of the game
 **/
struct LOADINGSCREEN_API FStartupLoadingScreenSettings
{
	GENERATED_BODY()

	/**
	* All movie files must be locate at Content/Movies/ directory. Suggested format: MPEG-4 Movie (mp4). Enter file path/name without the extension.
	* E.g., if you have a movie name my_movie.mp4 in the 'Content/Movies' folder, then enter my_movie in the input field.
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movies Settings")
	TArray<FString> MoviePaths;
	
	/**
	 * If true, movies can be skipped by clicking the loading screen as long as loading is done.
	 **/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movies Settings")
	bool bMoviesAreSkippable = true;

};

USTRUCT(BlueprintType)
struct LOADINGSCREEN_API FDefaultLevelLoadingScreenSettings
{
	GENERATED_BODY()
	
};



UCLASS(Config = "Game", defaultconfig, meta = (DisplayName = "Loading Screen"))
class LOADINGSCREEN_API ULoadingScreenEditorSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:

	ULoadingScreenEditorSettings(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get())	
		: Super(ObjectInitializer)
	{
	}
	
	/**
	 * The startup loading screen when you first open the game. Setup any studio logo movies here.
	 */
	UPROPERTY(Config, EditAnywhere, Category = "General")
	FStartupLoadingScreenSettings StartupLoadingScreen;

	/**
	 * The default loading screen that shows up whenever you open a new level.
	 */
	UPROPERTY(Config, EditAnywhere, Category = "General")
	FDefaultLevelLoadingScreenSettings DefaultLevelLoadingScreen;
};