#ifndef R3BMQSAMPLER_H
#define R3BMQSAMPLER_H

#include <string>
#include <vector>

#include <FairMQDevice.h>

class TClonesArray;
class FairRootManager;
class FairRunAna;

class R3BMqSampler : public FairMQDevice
{
public:
    R3BMqSampler();
    virtual ~R3BMqSampler();
    
protected:
    virtual void InitTask();
    virtual void PreRun();
    virtual void PostRun();
    virtual bool ConditionalRun();
    
private:
    R3BMqSampler(const R3BMqSampler&);
    R3BMqSampler& operator=(const R3BMqSampler&);
    
    void SendOutputData();
    
    FairRunAna* fRun;
    FairRootManager* fMgr;
    
    int fEventNumber;
    int fMaxEvents;
    
    std::vector<std::string> fInputBranches;
    std::vector<TClonesArray*> fInputArrays;
};

#endif
