// Fill out your copyright notice in the Description page of Project Settings.


#include "Simulation/ILLVMSimulationSettings.h"

//////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////

const UILLVMSimulationSettings& UILLVMSimulationSettings::Get()
{
    return *CastChecked<UILLVMSimulationSettings>(UILLVMSimulationSettings::StaticClass()->GetDefaultObject());
}
