#include <TClonesArray.h>
#include <TString.h>

#include <FairTask.h>
#include <FairRunAna.h>
#include <FairRootManager.h>
#include <FairLogger.h>

#include "R3BMqDevice.h"

#include <RootSerializer.h>

#include <R3BFi4Digitizer.h>
#include <R3BFragmentTracker.h>

R3BMqDevice::R3BMqDevice()
{
    InitTaskMap();
}

R3BMqDevice::~R3BMqDevice()
{
    if(fTask)
    {
        delete fTask;
    }
}

void R3BMqDevice::InitTask()
{
    OnData("data1", &R3BMqDevice::ReceiveData);
    
    FairRunAna* run = new FairRunAna();
    
    fMgr = FairRootManager::Instance();
    
    std::string taskName = GetConfig()->GetValue<std::string>("task");
    if(fTaskMap.find(taskName) != fTaskMap.end())
    {
        LOG(info) << "Creating task " << taskName;
        fTask = fTaskMap[taskName](taskName.c_str());
    }
    else
    {
        fTask = nullptr;
        // TODO Throw error
    }
    
    fRequireAllBranches = GetConfig()->GetValue<bool>("all");
    fInputBranches = GetConfig()->GetValue<std::vector<std::string>>("branch");
    fInputFolders = GetConfig()->GetValue<std::vector<std::string>>("folder");
    fInputClasses = GetConfig()->GetValue<std::vector<std::string>>("class");
    if(fInputBranches.size() != fInputFolders.size() ||
       fInputBranches.size() != fInputClasses.size())
    {
        // TODO Throw error
    }
    int i = 0;
    for(auto & x : fInputBranches)
    {
        LOG(info) << "Registering input: " << x << " " << fInputFolders.at(i)
        << " " << fInputClasses.at(i);
        auto array = new TClonesArray(fInputClasses.at(i).c_str());
        fInputArrays.push_back(array);
        //fMgr->Register(x.c_str(), fInputFolders.at(i).c_str(), array, kFALSE);
        fMgr->RegisterInputObject(x.c_str(), array);
        fHasData[fInputClasses.at(i)] = false;
        i++;
    }

    fTask->InitTask();

    fOutputBranches = GetConfig()->GetValue<std::vector<std::string>>("output");
    for(auto & x : fOutputBranches)
    {
        TClonesArray* array = static_cast<TClonesArray*>(fMgr->GetObject(x.c_str()));
        if(! array)
        {
            // TODO Throw error
        }
        fOutputArrays.push_back(array);
    }
}

void R3BMqDevice::PreRun()
{
}

void R3BMqDevice::PostRun()
{
}

bool R3BMqDevice::ReceiveData(FairMQMessagePtr& msg, int index)
{
    TObject* tempObject = nullptr;
    Deserialize<RootSerializer>(*msg, tempObject);
    
    if (TString(tempObject->ClassName()).EqualTo("TClonesArray"))
    {
        // Copy input data
        TClonesArray* input = static_cast<TClonesArray*>(tempObject);
        for(auto & x : fInputArrays)
        {
            if(input->GetClass() == x->GetClass())
            {
                x->Delete();
                *x = *input;
                fHasData[x->GetClass()->GetName()] = true;
            }
        }
        
        if(fRequireAllBranches && CheckIfAllInput())
        {
            // All arrays are there - execute
            fTask->Exec("");
            
            SendOutputData();
            
            // Reset flags
            for(auto & x : fInputClasses)
            {
                fHasData[x] = false;
            }
        }
        else
        {
            // Execute even for partial data
            fTask->Exec("");
            
            SendOutputData();
        }
        
        input->Delete();
    }
    
    delete tempObject;
    
    return true;
}

bool R3BMqDevice::CheckIfAllInput()
{
    // Check if all arrays arrived
    for(auto & x : fHasData)
    {
        if(! x.second)
        {
            return false;
        }
    }
    return true;
}

void R3BMqDevice::SendOutputData()
{
    for(auto & x : fOutputArrays)
    {
        FairMQMessagePtr message(NewMessage());
        Serialize<RootSerializer>(*message, x);
        
        Send(message, "data2");
    }
}

void R3BMqDevice::InitTaskMap()
{
    // Fill the map of known tasks
    fTaskMap["Fi4Digitizer"] = &CreateTask<R3BFi4Digitizer>;
}
