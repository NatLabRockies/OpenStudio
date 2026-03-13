/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SCHEDULETYPELIMITS_HPP
#define EPMODEL_SCHEDULETYPELIMITS_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <boost/optional.hpp>

#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ScheduleTypeLimits_Impl;
  }

  /** ScheduleTypeLimits is a ModelObject that wraps the EnergyPlus IDD object
 * 'ScheduleTypeLimits'. */
  class EPMODEL_API ScheduleTypeLimits : public ModelObject
  {
   public:
    explicit ScheduleTypeLimits(const Model& model);

    virtual ~ScheduleTypeLimits() override = default;
    ScheduleTypeLimits(const ScheduleTypeLimits& other) = default;
    ScheduleTypeLimits(ScheduleTypeLimits&& other) = default;
    ScheduleTypeLimits& operator=(const ScheduleTypeLimits&) = default;
    ScheduleTypeLimits& operator=(ScheduleTypeLimits&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> numericTypeValues();
    static std::vector<std::string> unitTypeValues();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model scalar accessor names/signatures for this counterpart class.
    // - Field Mapping: lowerLimitValue, upperLimitValue, numericType, and unitType map directly to EnergyPlus ScheduleTypeLimits fields.
    // - ForwardTranslator evidence: ForwardTranslateScheduleTypeLimits.cpp reads OS_ScheduleTypeLimits fields and writes matching E+ ScheduleTypeLimits fields.
    // - TODO(parity): Keep units/unit-conversion helper behavior in model; epmodel scaffold remains scalar-only in this pass.
    boost::optional<double> lowerLimitValue() const;
    bool setLowerLimitValue(double lowerLimitValue);
    void resetLowerLimitValue();

    boost::optional<double> upperLimitValue() const;
    bool setUpperLimitValue(double upperLimitValue);
    void resetUpperLimitValue();

    boost::optional<std::string> numericType() const;
    bool setNumericType(const std::string& numericType);
    void resetNumericType();

    std::string unitType() const;
    bool isUnitTypeDefaulted() const;
    bool setUnitType(const std::string& unitType);
    void resetUnitType();

   protected:
    using ImplType = detail::ScheduleTypeLimits_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ScheduleTypeLimits(std::shared_ptr<detail::ScheduleTypeLimits_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
