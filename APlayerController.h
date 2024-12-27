
UCLASS(config=Game, BlueprintType, Blueprintable, meta=(ShortTooltip="A Player Controller is an actor responsible for controlling a Pawn used by the player."))
class ENGINE_API APlayerController : public AController, public IWorldPartitionStreamingSourceProvider
{
	/** UPlayer associated with this PlayerController.  Could be a local player or a net connection. */
	UPROPERTY()
	TObjectPtr<UPlayer> Player;

	virtual class UPlayer* GetNetOwningPlayer() override
	{
		return Player;
	}
};