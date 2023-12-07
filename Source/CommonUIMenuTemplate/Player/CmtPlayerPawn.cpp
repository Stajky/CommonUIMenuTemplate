// 


#include "CmtPlayerPawn.h"


// Sets default values
ACmtPlayerPawn::ACmtPlayerPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACmtPlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACmtPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACmtPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

