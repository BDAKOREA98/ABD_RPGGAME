#pragma once
UENUM()
enum class EWarriorConfirmType : uint8
{
	YES,
	NO
};

UENUM()
enum class EWarriorValidType : uint8
{
	Valid,
	InValid
};
UENUM()
enum class EWarriorSuccessType : uint8
{
	Succesful,
	Failed
};
UENUM()
enum class EWarriorCountDownActionInput : uint8
{
	Start,
	Cancel
};
UENUM()
enum class EWarriorCountDownActionOutput : uint8
{
	Updated,
	Completed,
	Cancelled
};

UENUM(BlueprintType)
enum class EGameDifficulty : uint8
{
	Easy,
	Normal,
	Hard,
	Hell
};
UENUM(BlueprintType)
enum class EInputMode :uint8
{
	GameOnly,
	UIOnly
};



