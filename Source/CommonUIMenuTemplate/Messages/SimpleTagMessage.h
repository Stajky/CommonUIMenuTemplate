#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "SimpleTagMessage.generated.h"


/**
 * Time Message
 */
USTRUCT(BlueprintType)
struct COMMONUIMENUTEMPLATE_API FSimpleTagMessage
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite)
	FGameplayTag Tag;

};
