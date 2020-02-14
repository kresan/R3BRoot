
#include "runFairMQDevice.h"
#include "R3BMqSink.h"

namespace bpo = boost::program_options;

void addCustomOptions(bpo::options_description& options)
{
    options.add_options()
    ("file", bpo::value<std::string>()->default_value(""), "Output file")
    ("all", bpo::value<bool>()->default_value(true), "Require all input branches")
    ("branch", bpo::value<std::vector<std::string>>()->multitoken(), "Input branches")
    ("folder", bpo::value<std::vector<std::string>>()->multitoken(), "Input folders")
    ("class", bpo::value<std::vector<std::string>>()->multitoken(), "Input classes");
}

FairMQDevicePtr getDevice(const FairMQProgOptions& /*config*/)
{
    return new R3BMqSink();
}
