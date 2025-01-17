// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "RobotsHUD.h"
#include "SlateBasics.h"

/**
*
*/
class ROBOTS_API SChatWidget : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SChatWidget) : _OwnerHUD() {} // the OwnerHUD var is passed to the widget so the owner can be set.

	SLATE_ARGUMENT(TWeakObjectPtr<class ARobotsHUD>, OwnerHUD)

		SLATE_END_ARGS()



public:

	void Construct(const FArguments& InArgs);

	TSharedRef<ITableRow> OnGenerateRowForList(TSharedPtr<FSChatMsg> Item, const TSharedRef<STableViewBase>& OwnerTable); // the function that is called for each chat element to be displayed in the chatbox
	TArray<TSharedPtr<FSChatMsg>> Items; // array of all the current items in this players chat box
	TSharedPtr< SListView< TSharedPtr<FSChatMsg> > > ListViewWidget; // the acutall widgets for each chat element

	const FSlateFontInfo fontinfo = FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Bold.ttf"), 16); // Font, Font Size  for the chatbox

	TWeakObjectPtr<class ARobotsHUD> OwnerHUD;

	TSharedPtr< SVerticalBox > ChatBox;
	TSharedPtr< SEditableText > ChatInput;

	void OnChatTextChanged(const FText& InText);
	void OnChatTextCommitted(const FText& InText, ETextCommit::Type CommitMethod);

	void AddMessage(const FSChatMsg& newmessage); // the final stage, this function takes the input and does the final placement in the chatbox

	void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime); // The full widget ticks and deletes messages
};