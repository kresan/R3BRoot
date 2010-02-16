//
// C++ Interface: PndTutPar
//
#ifndef R3BLANDDIGIPAR_H
#define R3BLANDDIGIPAR_H

#include <TVector3.h>
#include <TObjString.h>

#include "FairParGenericSet.h"
#include "FairParamList.h"

class R3BLandDigiPar : public FairParGenericSet
{
    public :
	R3BLandDigiPar (const char* name="R3BLandDigiParTest",
			const char* title="Tutorial  parameter",
			const char* context="TestDefaultContext");
	~R3BLandDigiPar(void){};
	void clear(void){};
	void putParams(FairParamList* list);
	Bool_t getParams(FairParamList* list);

	void Print();
	/** Accessor functions **/
	const Int_t GetMaxPaddle() { return  nMaxPaddle;}
	const Int_t GetMaxPlane() { return  nMaxPlane;}
	void SetMaxPaddle(Int_t paddle ){nMaxPaddle=paddle;}
	void SetMaxPlane(Int_t pla){nMaxPlane=pla;}

  private:
  // Digi. Parameters
  Int_t nMaxPaddle;
  Int_t nMaxPlane;


   ClassDef(R3BLandDigiPar,1); //
};

#endif /* !R3BLANDDIGIPAR_H*/
