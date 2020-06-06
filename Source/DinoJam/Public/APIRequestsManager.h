// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "APIRequestsManager.generated.h"

/**
 * 
 */

UCLASS(BlueprintType, Config = Game)
class DINOJAM_API UAPIRequestsManager : public UObject
{
	GENERATED_BODY()

	UAPIRequestsManager();

public:
	class FHttpModule* Http;

	UFUNCTION(BlueprintCallable)
	void MakeHTTPPostRequest(const FString& pRequestUrl, const FString& pRequestContent);

	UFUNCTION(BlueprintCallable)
	void MakeHTTPGetRequest(const FString& pRequestUrl);

	// Callback functions
	void OnHTTPPostResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bwasSuccessful);
	void OnHTTPGetResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bwasSuccessful);
};
