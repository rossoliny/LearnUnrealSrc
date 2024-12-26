UCLASS(customConstructor, config=Engine)
class ENGINE_API UWorld final : public UObject, public FNetworkNotify
{
	/** The NAME_GameNetDriver game connection(s) for client/server communication */
	UPROPERTY(Transient)
	TObjectPtr<class UNetDriver>							NetDriver;
};