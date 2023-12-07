#include "CmtGameMode.h"

#include "CmtGameState.h"
#include "../Player/CmtPlayerController.h"
#include "../Player/CmtPlayerPawn.h"
#include "../UI/CmtHUD.h"
#include "../Player/CmtPlayerState.h"

    
ACmtGameMode::ACmtGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	GameStateClass = ACmtGameState::StaticClass();
	PlayerControllerClass = ACmtPlayerController::StaticClass();
	DefaultPawnClass = ACmtPlayerPawn::StaticClass();
	HUDClass = ACmtHUD::StaticClass();
	PlayerStateClass = ACmtPlayerState::StaticClass();
}


void ACmtGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
}


void ACmtGameMode::InitGameState()
{
	Super::InitGameState();
}
