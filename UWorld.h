

UCLASS(customConstructor, config=Engine)
class ENGINE_API UWorld final : public UObject, public FNetworkNotify
{
	/** The NAME_GameNetDriver game connection(s) for client/server communication */
	UPROPERTY(Transient)
	TObjectPtr<class UNetDriver> NetDriver;

	bool UWorld::Listen(FURL& InURL)
	{
#if WITH_SERVER_CODE
		if (GEngine->CreateNamedNetDriver(this, NAME_GameNetDriver, NAME_GameNetDriver))
		{
			NetDriver = GEngine->FindNamedNetDriver(this, NAME_GameNetDriver);
		}

		NetDriver->InitListen(this, InURL, false, Error);
#endif
	}
};