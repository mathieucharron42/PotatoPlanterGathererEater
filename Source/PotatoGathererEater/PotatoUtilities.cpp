#include "PotatoUtilities.h"

#include "UObject/NoExportTypes.h"

void PotatoUtilities::DoSomething(float value)
{
	WasteTime(value);
}

void PotatoUtilities::DoSomethingElse(int32 value)
{
	WasteMemory(value);
}

void PotatoUtilities::WasteTime(float seconds)
{
	UE_LOG(LogTemp, Log, TEXT("Wasting %.4fs seconds"), seconds);
	const FDateTime start = FDateTime::Now();
	FTimespan span(0);
	while (span.GetTotalSeconds() <= seconds)
	{
		span = FDateTime::Now() - start;
	}
	UE_LOG(LogTemp, Log, TEXT("Wasted %.4fs seconds"), span.GetTotalSeconds());
}

void PotatoUtilities::WasteMemory(int32 bytes)
{
	static TArray<TArray<uint8>> leak;

	UE_LOG(LogTemp, Log, TEXT("Wasting %lld bytes"), bytes);
	TArray<uint8>& wastedMemory = leak.AddDefaulted_GetRef();

	wastedMemory.SetNumUninitialized(bytes);
}