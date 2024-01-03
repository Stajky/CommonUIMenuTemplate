#pragma once


#include "CoreMinimal.h"

#define BOOL2TEXT(b) ((b) ? *TrueString : *FalseString)

EXTERN_C const FString FalseString;
EXTERN_C const FString TrueString;