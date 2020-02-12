
#include "runFairMQDevice.h"
#include "R3BMqDevice.h"

namespace bpo = boost::program_options;

void addCustomOptions(bpo::options_description& options)
{
    options.add_options()
    ("task", bpo::value<std::string>()->default_value(""), "R3B Task")
    ("all", bpo::value<bool>()->default_value(true), "Require all input branches")
    ("branch", bpo::value<std::vector<std::string>>()->multitoken(), "Input branches")
    ("folder", bpo::value<std::vector<std::string>>()->multitoken(), "Input folders")
    ("class", bpo::value<std::vector<std::string>>()->multitoken(), "Input classes")
    ("output", bpo::value<std::vector<std::string>>()->multitoken(), "Output branches");
}

FairMQDevicePtr getDevice(const FairMQProgOptions& /*config*/)
{
    return new R3BMqDevice();
}
