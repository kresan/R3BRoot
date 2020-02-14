#include <TClonesArray.h>
#include <TString.h>
#include <TClass.h>

#include <FairTask.h>
#include <FairRunAna.h>
#include <FairRootManager.h>
#include <FairFileSource.h>
#include <FairLogger.h>

#include "R3BMqSampler.h"

#include <R3BMCTrack.h>
#include <R3BFi4Point.h>

#include <RootSerializer.h>

using namespace ROOT::Internal;

R3BMqSampler::R3BMqSampler()
: fEventNumber(0)
, fMaxEvents(0)
{
}

R3BMqSampler::~R3BMqSampler()
{
}

void R3BMqSampler::InitTask()
{
    std::string fileName = GetConfig()->GetValue<std::string>("file");

    fRun = new FairRunAna();
    fRun->SetSource(new FairFileSource(fileName.c_str()));

    fMgr = FairRootManager::Instance();
    
    fMgr->InitSource();
    
    fMaxEvents = fMgr->CheckMaxEventNo(0);
    //fMaxEvents = 1;

    fInputBranches = GetConfig()->GetValue<std::vector<std::string>>("branch");

    for(auto & x : fInputBranches)
    {
        auto array = static_cast<TClonesArray*>(fMgr->GetObject(x.c_str()));
        fInputArrays.push_back(array);
    }
}

void R3BMqSampler::PreRun()
{
}

void R3BMqSampler::PostRun()
{
}

bool R3BMqSampler::ConditionalRun()
{
    fMgr->ReadEvent(fEventNumber);
    
    SendOutputData();
    
    fEventNumber += 1;
    
    if(fEventNumber >= fMaxEvents)
    {
        return false;
    }
    
    return true;
}

void R3BMqSampler::SendOutputData()
{
    for(auto & x : fInputArrays)
    {
        FairMQMessagePtr message(NewMessage());
        Serialize<RootSerializer>(*message, x);
        
        for (auto& channel : fChannels)
        {
            Send(message, channel.first.data());
        }
    }
}
