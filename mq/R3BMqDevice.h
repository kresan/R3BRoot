#ifndef R3BMQDEVICE_H
#define R3BMQDEVICE_H

#include <string>
#include <map>
#include <vector>

#include <FairMQDevice.h>

class TClonesArray;
class FairTask;
class FairRootManager;

class R3BMqDevice : public FairMQDevice
{
public:
    R3BMqDevice();
    virtual ~R3BMqDevice();
    
protected:
    virtual void InitTask();
    bool ReceiveData(FairMQMessagePtr& msg, int index);
    virtual void PreRun();
    virtual void PostRun();
    
private:
    R3BMqDevice(const R3BMqDevice&);
    R3BMqDevice& operator=(const R3BMqDevice&);
    
    std::map<std::string, FairTask* (*)(const char*)> fTaskMap;
    
    void InitTaskMap();
    
    bool CheckIfAllInput();
    
    void SendOutputData();
    
    FairRootManager* fMgr;
    FairTask* fTask;
    
    std::vector<std::string> fInputBranches;
    std::vector<std::string> fInputFolders;
    std::vector<std::string> fInputClasses;
    std::vector<TClonesArray*> fInputArrays;
    bool fRequireAllBranches;
    std::map<std::string, bool> fHasData;
    
    std::vector<std::string> fOutputBranches;
    std::vector<TClonesArray*> fOutputArrays;
};

template<typename T> FairTask* CreateTask(const char* name) { return new T(name); }

#endif
