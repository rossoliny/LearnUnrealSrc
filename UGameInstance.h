


UCLASS(config=Game, transient, BlueprintType, Blueprintable)
class ENGINE_API UGameInstance : public UObject, public FExec
{
	bool UGameInstance::EnableListenServer(bool bEnable, int32 PortOverride /*= 0*/)
	{
		WorldContext->LastURL.AddOption(TEXT("Listen"));

		if (ExistingMode == NM_Standalone)
		{
			// This actually opens the port
			FURL ListenURL = WorldContext->LastURL;
			return World->Listen(ListenURL);
		}
	}
}