	
UCLASS(BlueprintType, Blueprintable, config=Engine, meta=(ShortTooltip="An Actor is an object that can be placed or spawned in the world."))
class ENGINE_API AActor : public UObject
{

	/** Return the owning UPlayer (if any) of this actor. This will be a local player, a net connection, or nullptr. */
	virtual class UPlayer* GetNetOwningPlayer()
	{
		// We can only replicate RPCs to the owning player
		if (GetLocalRole() == ROLE_Authority)
		{
			if (Owner)
			{
				return Owner->GetNetOwningPlayer();
			}
		}
		return nullptr;
	}

};