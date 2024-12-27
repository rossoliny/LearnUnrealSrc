
class UGameEngine : public UEngine 
{
	TIndirectArray<FWorldContext> WorldList;

	UPROPERTY(Config, transient)
	TArray<FNetDriverDefinition> NetDriverDefinitions;

	UPROPERTY(transient)
	TArray<FNamedNetDriver> ActiveNetDrivers;

	UNetDriver* CreateNetDriver_Local(UEngine* Engine, FWorldContext& Context, FName NetDriverDefinition, FName InNetDriverName)
	{
		UNetDriver* ReturnVal;

		Definition = Engine->NetDriverDefinitions.FindByPredicate(FindNetDriverDefPred);

		new(Context.ActiveNetDrivers) FNamedNetDriver(ReturnVal, Definition);

		return ReturnVal;
	};


	// CALL ON CLIENT TO CONNECT
	virtual EBrowseReturnVal::Type Browse( FWorldContext& WorldContext, FURL URL, FString& Error )
	{
		WorldContext.PendingNetGame = NewObject<UPendingNetGame>();
		WorldContext.PendingNetGame->Initialize(WorldContext.LastURL);
		WorldContext.PendingNetGame->InitNetDriver();
	}

	// CALL ON SERVER TO START LISTEN 
	// If has Listen option then starts listen
	virtual bool LoadMap( FWorldContext& WorldContext, FURL URL, class UPendingNetGame* Pending, FString& Error )
	{
		if (Pending == NULL && (!GIsClient || URL.HasOption(TEXT("Listen"))))
		{
			if (!WorldContext.World()->Listen(URL))
			{
				UE_LOG(LogNet, Error, TEXT("LoadMap: failed to Listen(%s)"), *URL.ToString());
			}
		}
	}




};



