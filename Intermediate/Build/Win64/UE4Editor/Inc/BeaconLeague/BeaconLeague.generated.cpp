// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Boilerplate C++ definitions for a single module.
	This is automatically generated by UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "BeaconLeague.h"
#include "BeaconLeague.generated.dep.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeBeaconLeague() {}
	void ABeaconLeagueGameMode::StaticRegisterNativesABeaconLeagueGameMode()
	{
	}
	IMPLEMENT_CLASS(ABeaconLeagueGameMode, 914483303);
#if USE_COMPILED_IN_NATIVES
// Cross Module References
	ENGINE_API class UClass* Z_Construct_UClass_AGameMode();

	BEACONLEAGUE_API class UClass* Z_Construct_UClass_ABeaconLeagueGameMode_NoRegister();
	BEACONLEAGUE_API class UClass* Z_Construct_UClass_ABeaconLeagueGameMode();
	BEACONLEAGUE_API class UPackage* Z_Construct_UPackage_BeaconLeague();
	UClass* Z_Construct_UClass_ABeaconLeagueGameMode_NoRegister()
	{
		return ABeaconLeagueGameMode::StaticClass();
	}
	UClass* Z_Construct_UClass_ABeaconLeagueGameMode()
	{
		static UClass* OuterClass = NULL;
		if (!OuterClass)
		{
			Z_Construct_UClass_AGameMode();
			Z_Construct_UPackage_BeaconLeague();
			OuterClass = ABeaconLeagueGameMode::StaticClass();
			if (!(OuterClass->ClassFlags & CLASS_Constructed))
			{
				UObjectForceRegistration(OuterClass);
				OuterClass->ClassFlags |= 0x2090028C;


				OuterClass->ClassConfigName = FName(TEXT("Game"));
				OuterClass->StaticLink();
#if WITH_METADATA
				UMetaData* MetaData = OuterClass->GetOutermost()->GetMetaData();
				MetaData->SetValue(OuterClass, TEXT("HideCategories"), TEXT("Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering Utilities|Transformation"));
				MetaData->SetValue(OuterClass, TEXT("IncludePath"), TEXT("BeaconLeagueGameMode.h"));
				MetaData->SetValue(OuterClass, TEXT("ModuleRelativePath"), TEXT("BeaconLeagueGameMode.h"));
				MetaData->SetValue(OuterClass, TEXT("ShowCategories"), TEXT("Input|MouseInput Input|TouchInput"));
#endif
			}
		}
		check(OuterClass->GetClass());
		return OuterClass;
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ABeaconLeagueGameMode(Z_Construct_UClass_ABeaconLeagueGameMode, TEXT("ABeaconLeagueGameMode"));
	DEFINE_VTABLE_PTR_HELPER_CTOR(ABeaconLeagueGameMode);
	UPackage* Z_Construct_UPackage_BeaconLeague()
	{
		static UPackage* ReturnPackage = NULL;
		if (!ReturnPackage)
		{
			ReturnPackage = CastChecked<UPackage>(StaticFindObjectFast(UPackage::StaticClass(), NULL, FName(TEXT("/Script/BeaconLeague")), false, false));
			ReturnPackage->SetPackageFlags(PKG_CompiledIn | 0x00000000);
			FGuid Guid;
			Guid.A = 0x80E42BA9;
			Guid.B = 0xCB0393F8;
			Guid.C = 0x00000000;
			Guid.D = 0x00000000;
			ReturnPackage->SetGuid(Guid);

		}
		return ReturnPackage;
	}
#endif

PRAGMA_ENABLE_DEPRECATION_WARNINGS
