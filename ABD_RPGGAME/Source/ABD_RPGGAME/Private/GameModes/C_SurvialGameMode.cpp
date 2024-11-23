


#include "GameModes/C_SurvialGameMode.h"

void AC_SurvialGameMode::BeginPlay()
{
	Super::BeginPlay();

	checkf(EnemyWaveSpawnerDataTable, TEXT("Forgot to assign a valid datat table in survial game mode blueprint"));

	SetCurrentSurvialGameModeState(ESurvialGameModeState::WaitSpawnNewWave);

	TotalWavesToSpawn = EnemyWaveSpawnerDataTable->GetRowNames().Num();
	


}

void AC_SurvialGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentSurvialGameModeState == ESurvialGameModeState::WaitSpawnNewWave)
	{
		TimePassedSinceStart += DeltaTime;
		if (TimePassedSinceStart >= SpawnNewWaveWaitTime)
		{
			TimePassedSinceStart = 0.f;
			SetCurrentSurvialGameModeState(ESurvialGameModeState::SpawningNewWave);
		}
	}

	if (CurrentSurvialGameModeState == ESurvialGameModeState::SpawningNewWave)
	{
		TimePassedSinceStart += DeltaTime;
		if (TimePassedSinceStart >= SpawnEnemiesDelayTime)
		{
			//ToDo

			SetCurrentSurvialGameModeState(ESurvialGameModeState::InProgress);

		}
	}

	if (CurrentSurvialGameModeState == ESurvialGameModeState::InProgress)
	{
		TimePassedSinceStart += DeltaTime;
		if (TimePassedSinceStart >= WaveCompleteWaitTime)
		{
			TimePassedSinceStart = 0.f;
			CurrentWaveCount++;
			if (HasFinishedAllWaves())
			{
				SetCurrentSurvialGameModeState(ESurvialGameModeState::AllWavesDone);

			}
			else
			{
				SetCurrentSurvialGameModeState(ESurvialGameModeState::WaitSpawnNewWave);
			}

		}

	}


}

void AC_SurvialGameMode::SetCurrentSurvialGameModeState(ESurvialGameModeState InState)
{
	CurrentSurvialGameModeState = InState;

	OnSurvialGameModeStateChanged.Broadcast(CurrentSurvialGameModeState);

	


}

bool AC_SurvialGameMode::HasFinishedAllWaves() const
{
	return CurrentWaveCount > TotalWavesToSpawn;
}
