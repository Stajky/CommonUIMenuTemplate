// 


#include "SettingsTab.h"

#include "SettingsEditor.h"
#include "Components/ScrollBox.h"

void USettingsTab::CommitValues()
{
	TArray<UWidget*> Settings = SettingsScrollBox->GetAllChildren();
	for(auto Setting: Settings)
	{
		if(USettingsEditor* SettingsEditor = Cast<USettingsEditor>(Setting))
		{
			SettingsEditor->SetCurrentAsDefaultOption();
		}
	}
}

void USettingsTab::ResetToDefaults()
{
	TArray<UWidget*> Settings = SettingsScrollBox->GetAllChildren();
	for(auto Setting: Settings)
	{
		if(USettingsEditor* SettingsEditor = Cast<USettingsEditor>(Setting))
		{
			SettingsEditor->ResetToDefaultOption();
		}
	}
}
