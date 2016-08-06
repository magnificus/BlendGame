// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "RobotCharacter.generated.h"


UCLASS(config = Game)
class ARobotCharacter : public ACharacter
{
	GENERATED_BODY()

		/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;
public:
	ARobotCharacter();


	// health
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay, Replicated)
		float health;
	void SetHealth(float health);
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerSetHealth(float newHealth);
	virtual void ServerSetHealth_Implementation(float newHealth);
	virtual bool ServerSetHealth_Validate(float newHealth);


	// speed

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay, Replicated)
		float speed;
	void SetSpeed(float speed);
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerSetSpeed(float newSpeed);
	virtual void ServerSetSpeed_Implementation(float newSpeed);
	virtual bool ServerSetSpeed_Validate(float newSpeed);

	// ispunching

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay, Replicated)
		bool isPunching;
	void SetIsPunching(bool newIsPunching);
	UFUNCTION(Reliable, Server, WidthValidation)
	void ServerSetIsPunching(bool newIsPunching);
	virtual void ServerSetIsPunching_Implementation(bool newIsPunching);
	virtual bool ServerSetIsPunching_Validate(bool newIsPunching);

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

	//UFUNCTION(Reliable, Server, WithValidation)
	//void changeMaxSpeedTo(float newSpeed);


protected:

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/**
	* Called via input to turn at a given rate.
	* @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	*/
	void TurnAtRate(float Rate);

	/**
	* Called via input to turn look up/down at a given rate.
	* @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	*/
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

	void FirePressed();
	void FireReleased();

	void SprintPressed();
	void SprintReleased();



protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

