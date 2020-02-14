#ifndef R3BMQSINK_H
#define R3BMQSINK_H

#include <string>
#include <map>
#include <vector>

#include <FairMQDevice.h>

class TClonesArray;
class FairRootManager;

class R3BMqSink : public FairMQDevice
{
public:
    R3BMqSink();
    virtual ~R3BMqSink();
    
protected:
    virtual void InitTask();
    bool ReceiveData(FairMQMessagePtr& msg, int index);
    virtual void PreRun();
    virtual void PostRun();
    
private:
    R3BMqSink(const R3BMqSink&);
    R3BMqSink& operator=(const R3BMqSink&);

    bool CheckIfAllInput();
    
    void FillData();

    FairRootManager* fMgr;

    std::vector<std::string> fInputBranches;
    std::vector<std::string> fInputFolders;
    std::vector<std::string> fInputClasses;
    std::vector<TClonesArray*> fInputArrays;
    bool fRequireAllBranches;
    std::map<std::string, bool> fHasData;
};

#endif
