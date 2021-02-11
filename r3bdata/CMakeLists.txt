##############################################################################
#   Copyright (C) 2019 GSI Helmholtzzentrum für Schwerionenforschung GmbH    #
#   Copyright (C) 2019 Members of R3B Collaboration                          #
#                                                                            #
#             This software is distributed under the terms of the            #
#                 GNU General Public Licence (GPL) version 3,                #
#                    copied verbatim in the file "LICENSE".                  #
#                                                                            #
# In applying this license GSI does not waive the privileges and immunities  #
# granted to it by virtue of its status as an Intergovernmental Organization #
# or submit itself to any jurisdiction.                                      #
##############################################################################

# Create a library called "libR3BDATA" which includes the source files given in the array . The
# extension is already found.  Any number of sources could be listed here.

# Set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-overloaded-virtual") Set(CMAKE_CXX_FLAGS
# "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wformat-security -march=native")

set(target R3BData)

set(sources
R3BMCStack.cxx
R3BMCTrack.cxx
wrData/R3BWRMasterData.cxx
wrData/R3BWRCalifaData.cxx
wrData/R3BWRAmsData.cxx
R3BHit.cxx
R3BTrack.cxx
R3BDouble.cxx
xballData/R3BXBallPoint.cxx
xballData/R3BXBallCrystalHit.cxx
xballData/R3BXBallCrystalHitSim.cxx
califaData/R3BCalifaCrystalCalData.cxx
califaData/R3BCalifaMappedData.cxx
califaData/R3BCalifaHitData.cxx
califaData/R3BCalifaPoint.cxx
dchData/R3BDchPoint.cxx
dchData/R3BDchFullPoint.cxx
gfiData/R3BGfiPoint.cxx
mtofData/R3BmTofPoint.cxx
mtofData/R3BmTofDigi.cxx
tofData/R3BTofPoint.cxx
vetoData/R3BVetoPoint.cxx
lumonData/ELILuMonPoint.cxx
trackerData/R3BTraPoint.cxx
trackerData/R3BTraHit.cxx
trackerData/R3BSitrackerHit.cxx
trackerData/R3BTrackerHit.cxx
startrackData/R3BStartrackPoint.cxx
startrackData/R3BStartrackHit.cxx
#startrackData/R3BStartrackerHit.cxx
startrackData/R3BStartrackerDigitHit.cxx
startrackData/R3BStartrackMappedData.cxx
startrackData/R3BStartrackCalData.cxx
landData/R3BLandPoint.cxx
landData/R3BLandDigi.cxx
landData/R3BLandFirstHits.cxx
landData/R3BLandHit.cxx
landData/R3BPaddleCrystalHit.cxx
landData/R3BNeutronTrack.cxx
dchData/R3BDchDigi.cxx
dchData/R3BDch2pDigi.cxx
tofData/R3BTofDigi.cxx
tofData/R3BTof2pDigi.cxx
gfiData/R3BGfiDigi.cxx
trackerData/R3BTraDigi.cxx
trackerData/R3BTra2pDigi.cxx
trackerData/R3BTraFraDigi.cxx
trackerData/R3BTargetDigi.cxx
trackerData/R3BTarget2pDigi.cxx
mfiData/R3BMfiPoint.cxx
mfiData/R3BMfiDigi.cxx
pspData/R3BPspPoint.cxx
pspData/R3BPspDigi.cxx
neulandData/R3BNeulandTacquilaMappedData.cxx
neulandData/R3BNeulandCalData.cxx
neulandData/R3BNeulandPoint.cxx
neulandData/R3BNeulandHit.cxx
neulandData/R3BNeulandMultiplicity.cxx
neulandData/R3BNeulandCluster.cxx
neulandData/R3BNeulandNeutron.cxx
pspData/R3BPspxMappedData.cxx
pspData/R3BPspxPrecalData.cxx
pspData/R3BPspxCalData.cxx
pspData/R3BPspxHitData.cxx
losData/R3BLosMappedData.cxx
losData/R3BLosCalData.cxx
losData/R3BLosHitData.cxx
roluData/R3BRoluMappedData.cxx
roluData/R3BRoluCalData.cxx
roluData/R3BRoluHitData.cxx
sci2Data/R3BSci2MappedData.cxx
sci2Data/R3BSci2CalData.cxx
sci2Data/R3BSci2HitData.cxx
sci8Data/R3BSci8MappedData.cxx
sci8Data/R3BSci8CalData.cxx
sci8Data/R3BSci8HitData.cxx
actarData/R3BActarPoint.cxx
strawtubesData/R3BStrawtubesMappedData.cxx
strawtubesData/R3BStrawtubesCalData.cxx
strawtubesData/R3BStrawtubesHitData.cxx
neulandData/R3BPaddleTamexMappedData.cxx
tofData/R3BTofdMappedData.cxx
tofData/R3BTofdCalData.cxx
tofData/R3BTofdHitData.cxx
tofData/R3BPaddleCalData.cxx
tofData/R3BTofdPoint.cxx
tofData/R3BTofdDigi.cxx
tofData/R3BPtofHit.cxx
pdcData/R3BPdcMappedData.cxx
pdcData/R3BPdcCalData.cxx
pdcData/R3BPdcHitData.cxx
fibData/R3BBunchedFiberCalData.cxx
fibData/R3BBunchedFiberHitData.cxx
fibData/R3BBunchedFiberMappedData.cxx
fibData/R3BFi4Point.cxx
fibData/R3BFi4CalItem.cxx
fibData/R3BFi4HitItem.cxx
fibData/R3BFibMappedData.cxx
fibData/R3BFibCalData.cxx
fibData/R3BFibPoint.cxx
amsData/R3BAmsMappedData.cxx
amsData/R3BAmsStripCalData.cxx
amsData/R3BAmsHitData.cxx
beammonitorData/R3BBeamMonitorMappedData.cxx
musicData/R3BMusicPoint.cxx
musicData/R3BMusicMappedData.cxx
musicData/R3BMusicCalData.cxx
musicData/R3BMusicHitData.cxx
sampData/R3BSamplerMappedData.cxx
)

fair_change_extensions_if_exists(.cxx .h FILES "${sources}" OUTVAR headers)

add_library(${target} SHARED ${sources} ${headers})
add_library(R3BRoot::${target} ALIAS ${target})
set_target_properties(${target} PROPERTIES ${FAIRROOT_LIBRARY_PROPERTIES})

target_include_directories(${target} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/xballData>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/califaData>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/wrData>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/beammonitorData>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/gfiData>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/mtofData>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/tofData>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/pdcData>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/vetoData>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lumonData>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/trackerData>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/startrackData>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/landData>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/roluData>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/losData>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/sci2Data>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/sci8Data>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/mfiData>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/fibData>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/pspData>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/neulandData>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/actarData>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/strawtubesData>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/amsData>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/musicData>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/sampData>
    
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>

  # DELETE ME ONCE USING root targets
  ${ROOT_INCLUDE_DIR}
)

target_link_libraries(${target} PUBLIC
  FairRoot::Base
  FairRoot::FairTools
)

fairroot_target_root_dictionary(${target}
  HEADERS ${headers}
  LINKDEF R3BDataLinkDef.h
)

#install(TARGETS ${target} LIBRARY DESTINATION ${PROJECT_INSTALL_LIBDIR})
#install(FILES ${headers} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
