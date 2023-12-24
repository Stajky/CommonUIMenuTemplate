#pragma once
#include "LoadingScreenSettings.h"

class LOADINGSCREEN_API SLevelLoadingScreen : public SCompoundWidget
{
	
public:
	SLATE_BEGIN_ARGS( SLevelLoadingScreen )
		: _Settings(FLevelLoadingScreenSettings() )
	{}
	/** Settings */
	SLATE_ATTRIBUTE(FLevelLoadingScreenSettings, Settings)
	SLATE_END_ARGS()

	/**
	 * Construct this widget
	 *
	 * @param	InArgs	The declaration data for this widget
	 */
	void Construct( const FArguments& InArgs );

private:	

	FLevelLoadingScreenSettings Settings;

};
