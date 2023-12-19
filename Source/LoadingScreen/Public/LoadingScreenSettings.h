#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "UObject/ConstructorHelpers.h"
#include "MoviePlayer.h"
#include "Widgets/Layout/SScaleBox.h"
#include "LoadingScreenSettings.generated.h"



/**
 * Background widget for the widget loading screen
 */
USTRUCT(BlueprintType)
struct LOADINGSCREEN_API FBackgroundSettings
{
	GENERATED_BODY()

	// The images randomly display while in the loading screen on top of the movie 
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Background", meta = (AllowedClasses = "/Script/Engine.Texture2D"))
	FSoftObjectPath ImagePath;

	// The scaling type to apply to images.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Background")
	TEnumAsByte<EStretch::Type> ImageStretch = EStretch::ScaleToFit;
	
	// The border's background color if there is any image defined. If padding = 0 you will not see the border color.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Background")
	FSlateColor Tint = FLinearColor::White;
	
};

/**
 * Background widget for the widget loading screen
 */
USTRUCT(BlueprintType)
struct LOADINGSCREEN_API FImageSequenceSSettings
{
	GENERATED_BODY()

	// The images randomly display while in the loading screen on top of the movie 
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Background", meta = (AllowedClasses = "/Script/Engine.Texture2D"))
	FSoftObjectPath ImagePath;


	
};



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
struct LOADINGSCREEN_API FLevelLoadingScreenSettings
{
	GENERATED_BODY()
	
	// The scaling type to apply to images.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Level loading")
	FBackgroundSettings BackgroundSettings;
	
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
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "General")
	FStartupLoadingScreenSettings StartupLoadingScreen;

	/**
	 * The default loading screen that shows up whenever you open a new level.
	 */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "General")
	FLevelLoadingScreenSettings DefaultLevelLoadingScreen;
};