/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVAC_EXHAUSTCONTROL_HPP
#define EPMODEL_ZONEHVAC_EXHAUSTCONTROL_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <boost/optional.hpp>
#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ZoneHVACExhaustControl_Impl;
  }

  class EPMODEL_API ZoneHVACExhaustControl : public ModelObject
  {
   public:
    explicit ZoneHVACExhaustControl(const Model& model);

    virtual ~ZoneHVACExhaustControl() override = default;
    ZoneHVACExhaustControl(const ZoneHVACExhaustControl& other) = default;
    ZoneHVACExhaustControl(ZoneHVACExhaustControl&& other) = default;
    ZoneHVACExhaustControl& operator=(const ZoneHVACExhaustControl&) = default;
    ZoneHVACExhaustControl& operator=(ZoneHVACExhaustControl&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> flowControlTypeValues();

    // Schema Alignment Notes:
    // - API: IDD-derived naming is used because no openstudio::model counterpart exists.
    // - Field Mapping: Flow Control Type and Design Exhaust Flow Rate map directly to the EnergyPlus
    //   ZoneHVAC:ExhaustControl IDD fields.
    // - Field Mapping: Availability Schedule Name, zone/node targets, and schedule/object-list references are
    //   relationship-only and intentionally excluded from this scalar API.
    std::string flowControlType() const;
    bool isFlowControlTypeDefaulted() const;
    bool setFlowControlType(const std::string& flowControlType);
    void resetFlowControlType();

    boost::optional<double> designExhaustFlowRate() const;
    bool isDesignExhaustFlowRateAutosized() const;
    bool setDesignExhaustFlowRate(double designExhaustFlowRate);
    void autosizeDesignExhaustFlowRate();
    void resetDesignExhaustFlowRate();

   protected:
    using ImplType = detail::ZoneHVACExhaustControl_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ZoneHVACExhaustControl(std::shared_ptr<detail::ZoneHVACExhaustControl_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
