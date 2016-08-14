// Fill out your copyright notice in the Description page of Project Settings.

#include "Robots.h"
#include "RobotsHUD.h"
#include "Engine/Canvas.h"
#include "Engine/Font.h"
#include "RobotCharacter.h"

#include "ChatWidget.h"
#include "RobotPlayerState.h"

ARobotsHUD::ARobotsHUD()
{
	static ConstructorHelpers::FObjectFinder<UFont>HUDFontOb(TEXT("/Game/engineCont/EngineFonts/Roboto"));
	HUDFont = HUDFontOb.Object;
}

void ARobotsHUD::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (GEngine && GEngine->GameViewport) // make sure our screen is ready for the widget
	{
		SAssignNew(MyUIWidget, SChatWidget).OwnerHUD(this); // add the widget and assign it to the var
		GEngine->GameViewport->AddViewportWidgetContent(SNew(SWeakWidget).PossiblyNullContent(MyUIWidget.ToSharedRef()));
	}


}
void ARobotsHUD::DrawHUD()
{
	Super::DrawHUD();

	if (!MyPC)
	{
		MyPC = GetOwningPlayerController();
		AddMessageBP(2, TEXT(""), TEXT("Enter to chat."), false); // random Welcome message shown to the local player. To be deleted. note type 2 is system message and username is blank
		return;
	}

	if (MyPC->WasInputKeyJustPressed(EKeys::Enter))
		if (MyUIWidget.IsValid() && MyUIWidget->ChatInput.IsValid())
			FSlateApplication::Get().SetKeyboardFocus(MyUIWidget->ChatInput); // When the user presses Enter he will focus his keypresses on the chat input bar

	// basic info

	FVector2D ScreenDimensions = FVector2D(Canvas->SizeX, Canvas->SizeY);
	ARobotCharacter* myChar = Cast<ARobotCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));

	if (myChar) {
		if (myChar->canLaser)
			DrawText("Laser Avaliable (F)", FColor::White, 50, 50, HUDFont);
		if (myChar->canAssimilate)
			DrawText("Assimilate Available (G)", FColor::White, 50, 80, HUDFont);
		if (myChar->canReveal)
			DrawText("Reveal Available (H)", FColor::White, 50, 110, HUDFont);
		if (myChar->canActivate)
			DrawText("Activate (E)", FColor::White, ScreenDimensions.X / 2, ScreenDimensions.Y / 2);
	}


}

void ARobotsHUD::AddMessageBP(const int32 Type, const FString& Username, const FString& Text, const bool Replicate)
{
	if (!MyPC || !MyUIWidget.IsValid())
		return;

	FSChatMsg newmessage;
	newmessage.Init(Type, FText::FromString(Username), FText::FromString(Text)); // initialize our struct and prep the message
	if (newmessage.Type > 0)
		if (Replicate)
		{
			ARobotPlayerState* MyPS = Cast<ARobotPlayerState>(MyPC->PlayerState);
			if (MyPS)
				MyPS->UserChatRPC(newmessage); // Send the complete chat message to the PlayerState so it can be replicated then displayed
		}
		else
			MyUIWidget->AddMessage(newmessage); // Send a local message to this client only, no one else receives it
}