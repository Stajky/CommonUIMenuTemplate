#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "UObject/ConstructorHelpers.h"
#include "Widgets/Layout/SScaleBox.h"
#include "Layout/Margin.h"
#include "Templates/SharedPointer.h"
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
struct LOADINGSCREEN_API FImageSequenceSettings
{
	GENERATED_BODY()

	/** An array of images for animating the loading icon.*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowedClasses = "/Script/Engine.Texture2D"))
	TArray<UTexture2D*> Images;

	/** Scale of the images.*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector2D Scale = FVector2D(1.0f, 1.0f);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FMargin Padding = FMargin();
	
	/**
	 * Time in second to update the images, the smaller value the faster of the animation. A zero value will update the images every frame.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (UIMax = 1.00, UIMin = 0.00, ClampMin = "0", ClampMax = "1"))
	float Speed = 0.05f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bHideLoadingWidgetWhenCompletes = true;
};

/**
 * Background widget for the widget loading screen
 */
USTRUCT(BlueprintType)
struct LOADINGSCREEN_API FTipPanelSettings
{
	GENERATED_BODY()

	/** An array of images for animating the loading icon.*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowedClasses = "/Script/Engine.Texture2D"))
	UTexture2D* Image = nullptr;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FText> Tips;
	
	/** Scale of the images.*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector2D Size = FVector2D(1.0f, 1.0f);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FMargin Padding = FMargin();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FMargin TextPadding = FMargin();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FSlateFontInfo Font = FSlateFontInfo();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float TooltipChangeSpeed = 4.0f;

	
};


/**
 * These are essentialy just settings for default movie player for startup of the game
 **/
USTRUCT(BlueprintType)
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
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Level loading")
	FBackgroundSettings BackgroundSettings;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Level loading")
	FImageSequenceSettings ImageSequenceSettings;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Level loading")
	FTipPanelSettings TipPanelSettings;
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