// Fill out your copyright notice in the Description page of Project Settings.


#include "JumpyUI.h"
#define LOCTEXT_NAMESPACE "mynamespace"

void UJumpyUI::SetText(int32 Height)
{
	FText HeightFText = FText::Format(LOCTEXT("ShowHeight", "{0}"), Height / 100);
	HeightText->SetText(HeightFText);

	MaxHeightProgressBar->SetPercent(static_cast<float>(Height) / MaxHeight);

	if (Height > MaxHeight)
	{
		MaxHeight = Height;
		FText MaxHeightFText = FText::Format(LOCTEXT("ShowMaxHeight", "{0}"), MaxHeight / 100);
		MaxHeightTextBox->SetText(MaxHeightFText);
	}
}

void UJumpyUI::SetCoin(int32 Amount)
{
	FText CoinFText = FText::AsCurrency(Amount, "$");
	CoinText->SetText(CoinFText);
}

void UJumpyUI::InCreaseCoin(int32 Amount)
{
	CoinAmount = CoinAmount + Amount;
	SetCoin(CoinAmount);
}
