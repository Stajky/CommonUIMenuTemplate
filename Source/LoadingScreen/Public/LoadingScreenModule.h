#pragma once

#include "Modules/ModuleManager.h"

struct FLoadingScreenSettings;

class FLoadingScreenModule : public IModuleInterface
{
public:
	/** IModuleInterface implementation */

	/**
	 * Called right after the module DLL has been loaded and the module object has been created
	 */
	virtual void StartupModule() override;
	
	/**
	 * Called before the module is unloaded, right before the module object is destroyed.
	 */
	virtual void ShutdownModule() override;

	/**
	 * Returns true if this module hosts gameplay code 
	 * 
	 * @return True for "gameplay modules", or false for engine code modules, plugins, etc.
	 */
	virtual bool IsGameModule() const override;

private:
	/**
	 * Movie Player callback, it won't be called if we've already setup the loading screen
	 */
	void OnMoviePlayerPrepareLoadingScreen();


	void SetupLoadingScreen(const FLoadingScreenSettings& LoadingScreenSettings);
	
	
	bool bStartupLoadingScreenPrepared = false;
};
