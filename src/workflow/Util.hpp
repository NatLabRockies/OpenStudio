/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef WORKFLOW_UTIL_HPP
#define WORKFLOW_UTIL_HPP

#include "../utilities/core/Filesystem.hpp"
#include <array>
#include <string_view>

namespace openstudio {

namespace model {
  class Model;
}
namespace epmodel {
  class Model;
}
class IdfObject;
class Workspace;
class WorkflowStepResult;
class BCLMeasure;
struct IddObjectType;

namespace workflow {

  namespace util {

    model::Model loadOSM(const openstudio::filesystem::path& osmPath);
    Workspace loadIDF(const openstudio::filesystem::path& idfPath);
    epmodel::Model loadEPModel(const openstudio::filesystem::path& idfPath);

    void gatherReports(const openstudio::filesystem::path& runDirPath, const openstudio::filesystem::path& rootDirPath);

    bool addResultMeasureInfo(WorkflowStepResult& result, BCLMeasure& measure);

    // Cleans up the run directory (remove epw, .mtr)
    void cleanup(const openstudio::filesystem::path& runDirPath);

    bool mergeOutputTableSummaryReports(IdfObject& existingObject, const IdfObject& newObject);
    bool addEnergyPlusOutputRequest(Workspace& workspace, IdfObject& idfObject);

    // Schedule can be used onto a meter/variable, the EMS/PythonPlugin **could** be used for custom reporting
    // Also adding some cost/utility related objects, the goal is to be not too restrictive here
    static constexpr std::array<std::string_view, 11> safe_idd_prefixes{
      "Output",     "Meter",    "PythonPlugin", "EnergyManagementSystem", "Schedule", "LifeCycleCost", "UtilityCost", "ComponentCost",
      "Compliance", "Currency", "FuelFactors",
    };

    // If the IddObjectType.valueName doesn't start with one of the allowed prefixes (see `safe_idd_prefixes`), it returns true.
    bool isEnergyPlusOutputRequestPotentiallyUnsafe(const IddObjectType& iddObjectType);

    void zipResults(const openstudio::path& dirPath);

    /** Remove any invalid characters in the measure attribute keys. Periods and Pipes are the most problematic
     * because MongoDB does not allow hash keys with periods, and pipes are used in the map/reduce method that
     * was written to speed up the data write in OpenStudio-Server. Also, remove any trailing underscores and spaces.
     *
     * Ported from workflow-gem rename_hash_keys */
    std::string sanitizeKey(std::string key);

  }  // namespace util
}  // namespace workflow
}  // namespace openstudio

#endif  // WORKFLOW_UTIL_HPP
