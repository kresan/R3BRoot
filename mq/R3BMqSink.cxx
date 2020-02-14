#include <TClonesArray.h>
#include <TString.h>

#include <FairTask.h>
#include <FairRunAna.h>
#include <FairRootManager.h>
#include <FairLogger.h>
#include <FairRootFileSink.h>

#include "R3BMqSink.h"

#include <RootSerializer.h>

#include <R3BFi4Digitizer.h>
#include <R3BFragmentTracker.h>

R3BMqSink::R3BMqSink()
{
}

R3BMqSink::~R3BMqSink()
{
}

void R3BMqSink::InitTask()
{
    OnData("data2", &R3BMqSink::ReceiveData);
    
    std::string fileName = GetConfig()->GetValue<std::string>("file");
    
    FairRunAna* run = new FairRunAna();
    run->SetSink(new FairRootFileSink(fileName.c_str()));
    
    fMgr = FairRootManager::Instance();
    
    fMgr->InitSink();
    
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
        fMgr->Register(x.c_str(), fInputFolders.at(i).c_str(), array, kTRUE);
        fHasData[fInputClasses.at(i)] = false;
        i++;
    }
    
    fMgr->WriteFolder();
}

void R3BMqSink::PreRun()
{
}

void R3BMqSink::PostRun()
{
    fMgr->LastFill();
    fMgr->Write();
    fMgr->CloseSink();
}

bool R3BMqSink::ReceiveData(FairMQMessagePtr& msg, int index)
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
            // All arrays are there - fill
            FillData();
            
            // Reset flags
            for(auto & x : fInputClasses)
            {
                fHasData[x] = false;
            }
        }
        else
        {
            // Execute even for partial data
            FillData();
        }
        
        input->Delete();
    }
    
    delete tempObject;
    
    return true;
}

bool R3BMqSink::CheckIfAllInput()
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

void R3BMqSink::FillData()
{
    fMgr->Fill();
}
