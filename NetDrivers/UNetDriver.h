
UCLASS (Abstract, CustomConstructor, Transient, MinimalAPI, Config=Engine)  
class UNetDriver : public UObject, public FExec
{
	TArray<TObjectPtr<UNetConnection>> ClientConnections;
	
	TObjectPtr<UNetConnection> ServerConnection;


	virtual bool InitConnect(FNetworkNotify* InNotify, const FURL& ConnectURL, FString& Error);

	virtual bool InitListen(FNetworkNotify* InNotify, FURL& ListenURL, bool bReuseAddressAndPort, FString& Error);


	void UNetDriver::PostInitProperties()
	{
		Super::PostInitProperties();

		// By default we're the game net driver and any child ones must override this
		NetDriverName = NAME_GameNetDriver;
	}
};