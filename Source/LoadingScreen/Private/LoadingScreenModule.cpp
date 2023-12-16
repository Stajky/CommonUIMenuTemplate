#include "LoadingScreenModule.h"
#include "Modules/ModuleManager.h"
#include "MoviePlayer.h"
#include "LoadingScreenSettings.h"



void FLoadingScreenModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	if (!IsRunningDedicatedServer() && FSlateApplication::IsInitialized())
	{
		if (IsMoviePlayerEnabled())
		{
			GetMoviePlayer()->OnPrepareLoadingScreen().AddRaw(this, &FLoadingScreenModule::OnMoviePlayerPrepareLoadingScreen);				
		}		

		if(!bStartupLoadingScreenPrepared)
		{
			// Prepare the startup screen
			const ULoadingScreenEditorSettings* Settings = GetDefault<ULoadingScreenEditorSettings>();
			//TODO maybe move this at the end of the function call
			//guard for OnPrepareLoading so that we dont call it again since we dont have to
			bStartupLoadingScreenPrepared = true;
			SetupLoadingScreen(Settings->StartupLoadingScreen);
		}
	}	
	
	IModuleInterface::StartupModule();
}

void FLoadingScreenModule::ShutdownModule()
{
	IModuleInterface::ShutdownModule();
}

bool FLoadingScreenModule::IsGameModule() const
{
	return IModuleInterface::IsGameModule();
}

void FLoadingScreenModule::OnMoviePlayerPrepareLoadingScreen()
{
	if(bStartupLoadingScreenPrepared)
		return;
	
	GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Blue, TEXT("OnMoviePlayerPrepareLoadingScreen"));
}

void FLoadingScreenModule::SetupLoadingScreen(const FLoadingScreenSettings& LoadingScreenSettings)
{	
	GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Blue, TEXT("SetupLoadingScreen"));
}


IMPLEMENT_MODULE(FDefaultModuleImpl, LoadingScreen);
