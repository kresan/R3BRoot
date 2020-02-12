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

Set(SYSTEM_INCLUDE_DIRECTORIES
${SYSTEM_INCLUDE_DIRECTORIES}
${BASE_INCLUDE_DIRECTORIES}
${FairMQ_INCDIR}
${FairMQ_INCDIR}/fairmq
)

set(INCLUDE_DIRECTORIES
#put here all directories where header files are located
${R3BROOT_SOURCE_DIR}/mq
${R3BROOT_SOURCE_DIR}/r3bbase
${R3BROOT_SOURCE_DIR}/fi4
${R3BROOT_SOURCE_DIR}/r3bdata
${R3BROOT_SOURCE_DIR}/r3bdata/fibData
${R3BROOT_SOURCE_DIR}/tracking
)

include_directories( ${INCLUDE_DIRECTORIES})
include_directories(SYSTEM ${SYSTEM_INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES
${ROOT_LIBRARY_DIR}
${FAIRROOT_LIBRARY_DIR}
${Boost_LIBRARY_DIRS}
${FairMQ_LIBRARY_DIR}
)

link_directories( ${LINK_DIRECTORIES})

set(SRCS
)

set(NO_DICT_SRCS
    R3BMqDevice.cxx
)

#Set(LINKDEF TCalLinkDef.h)
Set(LIBRARY_NAME R3BMq)
Set(DEPENDENCIES
    ${DEPENDENCIES}
    FairMQ::FairMQ
    Base
    R3BData
    R3BFi4
    R3BTracking)

GENERATE_LIBRARY()

Set(Exe_Names
    runR3BDevice)

Set(Exe_Source
    runR3BDevice.cxx)

list(LENGTH Exe_Names _length)
math(EXPR _length ${_length}-1)

set(BIN_DESTINATION bin)
set(EXECUTABLE_OUTPUT_PATH "${EXECUTABLE_OUTPUT_PATH}")

ForEach(_file RANGE 0 ${_length})
    list(GET Exe_Names ${_file} _name)
    list(GET Exe_Source ${_file} _src)
    set(EXE_NAME ${_name})
    set(SRCS ${_src})
    set(DEPENDENCIES R3BMq)
    GENERATE_EXECUTABLE()
EndForEach(_file RANGE 0 ${_length})

set(EX_BIN_DIR ${EXECUTABLE_OUTPUT_PATH})
set(MAIN_BINARY_DIR ${CMAKE_BINARY_DIR})
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/start-fragment-tracker.sh.in ${EXECUTABLE_OUTPUT_PATH}/start-fragment-tracker.sh)

