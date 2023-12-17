#include "LoadingScreenModule.h"
#include "Modules/ModuleManager.h"
#include "MoviePlayer.h"
#include "LoadingScreenSettings.h"


void FLoadingScreenModule::StartupModule()
{
	if (IsMoviePlayerEnabled())
	{
		const ULoadingScreenEditorSettings* Settings = GetDefault<ULoadingScreenEditorSettings>();
		SetupStartupLoadingScreen(Settings->StartupLoadingScreen);
	}
}

void FLoadingScreenModule::ShutdownModule()
{
}

bool FLoadingScreenModule::IsGameModule() const
{
	return true;
}

void FLoadingScreenModule::SetupStartupLoadingScreen(const FStartupLoadingScreenSettings& StartupLoadingScreenSettings)
{
	// In this project for startup we only consider using the movies so no widget is set for the Movie Player
	FLoadingScreenAttributes LSAttributes;
	LSAttributes.bMoviesAreSkippable = StartupLoadingScreenSettings.bMoviesAreSkippable;
	LSAttributes.MoviePaths = StartupLoadingScreenSettings.MoviePaths;
	
	GetMoviePlayer()->SetupLoadingScreen(LSAttributes);
}


IMPLEMENT_GAME_MODULE(FLoadingScreenModule, LoadingScreen);
