
#include "runFairMQDevice.h"
#include "R3BMqSampler.h"

namespace bpo = boost::program_options;

void addCustomOptions(bpo::options_description& options)
{
    options.add_options()
    ("file", bpo::value<std::string>()->default_value(""), "Input file name")
    ("branch", bpo::value<std::vector<std::string>>()->multitoken(), "Input branches");
}

FairMQDevicePtr getDevice(const FairMQProgOptions& /*config*/)
{
    return new R3BMqSampler();
}
