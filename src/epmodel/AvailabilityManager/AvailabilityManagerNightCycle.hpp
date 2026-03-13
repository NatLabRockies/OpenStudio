/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AVAILABILITYMANAGERNIGHTCYCLE_HPP
#define EPMODEL_AVAILABILITYMANAGERNIGHTCYCLE_HPP

#include "EPModelAPI.hpp"
#include "AvailabilityManager/AvailabilityManager.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class AirLoopHVAC;
  class Model;

  namespace detail {
    class AvailabilityManagerNightCycle_Impl;
  }

  class EPMODEL_API AvailabilityManagerNightCycle : public AvailabilityManager
  {
   public:
    explicit AvailabilityManagerNightCycle(const Model& model);

    virtual ~AvailabilityManagerNightCycle() override = default;
    AvailabilityManagerNightCycle(const AvailabilityManagerNightCycle& other) = default;
    AvailabilityManagerNightCycle(AvailabilityManagerNightCycle&& other) = default;
    AvailabilityManagerNightCycle& operator=(const AvailabilityManagerNightCycle&) = default;
    AvailabilityManagerNightCycle& operator=(AvailabilityManagerNightCycle&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> controlTypeValues();
    static std::vector<std::string> cyclingRunTimeControlTypeValues();

    // Schema Alignment Notes:
    // - API: Preserves openstudio::model scalar accessor names/signatures for this model-counterpart class.
    // - Field Mapping: scalar APIs map directly to E+ AvailabilityManager:NightCycle fields
    //   (Control Type, Thermostat Tolerance, Cycling Run Time, Cycling Run Time Control Type).
    // - TODO(parity): Keep relationship fields (schedule links and zone-list targets) out of this scalar-only scaffold pass.
    boost::optional<AirLoopHVAC> airLoopHVAC() const;

    std::string controlType() const;
    bool setControlType(const std::string& controlType);
    bool isControlTypeDefaulted() const;
    void resetControlType();

    double thermostatTolerance() const;
    bool setThermostatTolerance(double thermostatTolerance);
    bool isThermostatToleranceDefaulted() const;
    void resetThermostatTolerance();

    double cyclingRunTime() const;
    bool setCyclingRunTime(double cyclingRunTime);
    bool isCyclingRunTimeDefaulted() const;
    void resetCyclingRunTime();

    std::string cyclingRunTimeControlType() const;
    bool setCyclingRunTimeControlType(const std::string& cyclingRunTimeControlType);
    bool isCyclingRunTimeControlTypeDefaulted() const;
    void resetCyclingRunTimeControlType();

   protected:
    using ImplType = detail::AvailabilityManagerNightCycle_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AvailabilityManagerNightCycle(std::shared_ptr<detail::AvailabilityManagerNightCycle_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
