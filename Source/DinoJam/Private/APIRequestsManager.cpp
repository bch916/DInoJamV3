// Fill out your copyright notice in the Description page of Project Settings.


#include "APIRequestsManager.h"

#include "Runtime/Json/Public/Dom/JsonObject.h"
#include "Runtime/Json/Public/Serialization/JsonReader.h"
#include "Runtime/Online/HTTP/Public/Interfaces/IHttpRequest.h"
#include "Runtime/Online/HTTP/Public/Interfaces/IHttpResponse.h"
#include "Runtime/Json/Public/Serialization/JsonSerializer.h"

#include "Runtime/Engine/Classes/Engine/Engine.h" //Engine module

 UAPIRequestsManager::UAPIRequestsManager()
{
	// To initialize the Http Module
	Http = &FHttpModule::Get();
}

void UAPIRequestsManager::MakeHTTPPostRequest(const FString& pRequestUrl, const FString& pRequestContent)
{
	TSharedRef<IHttpRequest> Request = Http->CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &UAPIRequestsManager::OnHTTPPostResponseReceived);

	Request->SetURL(pRequestUrl);
	Request->SetVerb("POST");
	Request->SetContentAsString(pRequestContent);

	Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", TEXT("application/json"));
	Request->ProcessRequest();
}

void UAPIRequestsManager::MakeHTTPGetRequest(const FString& pRequestUrl)
{
	TSharedRef<IHttpRequest> Request = Http->CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &UAPIRequestsManager::OnHTTPGetResponseReceived);

	Request->SetURL(pRequestUrl);
	Request->SetVerb("GET");

	Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", TEXT("application/json"));
	Request->ProcessRequest();
}

// Callback function
void UAPIRequestsManager::OnHTTPGetResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bwasSuccessful)
{
	if (Response && Response.IsValid() && bwasSuccessful) {

		int32 ResponseCode = Response->GetResponseCode();
		UE_LOG(LogTemp, Warning, TEXT("Code: %d"), ResponseCode);
		GEngine->AddOnScreenDebugMessage(91, 100.0f, FColor::Green, "ResponseCode: ");
		GEngine->AddOnScreenDebugMessage(91, 100.0f, FColor::Green, FString::FromInt(ResponseCode));

		FString Content = Response->GetContentAsString();
		UE_LOG(LogTemp, Warning, TEXT("Content: %s"), *Content);

		GEngine->AddOnScreenDebugMessage(91, 100.0f, FColor::Green, "Content");
		GEngine->AddOnScreenDebugMessage(91, 100.0f, FColor::Green, Content);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(91, 100.0f, FColor::Red, "Response Not Valid. Check connection?");
	}
}

void UAPIRequestsManager::OnHTTPPostResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bwasSuccessful)
{
	if (Response && Response.IsValid() && bwasSuccessful) {

		int32 ResponseCode = Response->GetResponseCode();
		UE_LOG(LogTemp, Warning, TEXT("Code: %d"), ResponseCode);
		GEngine->AddOnScreenDebugMessage(91, 100.0f, FColor::Green, "ResponseCode: ");
		GEngine->AddOnScreenDebugMessage(91, 100.0f, FColor::Green, FString::FromInt(ResponseCode));

		FString Content = Response->GetContentAsString();
		UE_LOG(LogTemp, Warning, TEXT("Content: %s"), *Content);

		GEngine->AddOnScreenDebugMessage(91, 100.0f, FColor::Green, "Content");
		GEngine->AddOnScreenDebugMessage(91, 100.0f, FColor::Green, Content);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(91, 100.0f, FColor::Red, "Response Not Valid. Check connection?");
	}
}


