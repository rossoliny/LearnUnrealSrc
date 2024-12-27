

UCLASS(MinimalAPI, transient, config=Engine)
class UPlayer : public UObject, public FExec
{
	/** The actor this player controls. */
	UPROPERTY(transient)
	TObjectPtr<class APlayerController> PlayerController;
};