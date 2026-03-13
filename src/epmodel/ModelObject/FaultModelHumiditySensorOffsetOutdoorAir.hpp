/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FAULTMODELHUMIDITYSENSOROFFSETOUTDOORAIR_HPP
#define EPMODEL_FAULTMODELHUMIDITYSENSOROFFSETOUTDOORAIR_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class FaultModelHumiditySensorOffsetOutdoorAir_Impl;
  }

  class EPMODEL_API FaultModelHumiditySensorOffsetOutdoorAir : public ModelObject
  {
   public:
    explicit FaultModelHumiditySensorOffsetOutdoorAir(const Model& model);

    virtual ~FaultModelHumiditySensorOffsetOutdoorAir() override = default;
    FaultModelHumiditySensorOffsetOutdoorAir(const FaultModelHumiditySensorOffsetOutdoorAir& other) = default;
    FaultModelHumiditySensorOffsetOutdoorAir(FaultModelHumiditySensorOffsetOutdoorAir&& other) = default;
    FaultModelHumiditySensorOffsetOutdoorAir& operator=(const FaultModelHumiditySensorOffsetOutdoorAir&) = default;
    FaultModelHumiditySensorOffsetOutdoorAir& operator=(FaultModelHumiditySensorOffsetOutdoorAir&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class/accessor naming.
    // - Field Mapping: humiditySensorOffset maps directly to EnergyPlus FaultModel:HumiditySensorOffset:OutdoorAir /
    //   Humidity Sensor Offset.
    // - Field Mapping: Name is provided by base ModelObject naming API and is intentionally not duplicated here.
    // - Field Mapping: Availability Schedule Name and Severity Schedule Name are object-list relationship fields,
    //   and Controller Object Type/Name are target-link fields, so they are intentionally excluded from scalar accessors.
    // - TODO(parity): Add relationship APIs after scalar scaffold saturation.
    double humiditySensorOffset() const;
    bool setHumiditySensorOffset(double humiditySensorOffset);
    bool isHumiditySensorOffsetDefaulted() const;
    void resetHumiditySensorOffset();

   protected:
    using ImplType = detail::FaultModelHumiditySensorOffsetOutdoorAir_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit FaultModelHumiditySensorOffsetOutdoorAir(std::shared_ptr<detail::FaultModelHumiditySensorOffsetOutdoorAir_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
