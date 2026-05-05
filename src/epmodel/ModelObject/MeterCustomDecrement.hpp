/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_METERCUSTOMDECREMENT_HPP
#define EPMODEL_METERCUSTOMDECREMENT_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class MeterCustomDecrement_Impl;
  }

  class EPMODEL_API MeterCustomDecrement : public ModelObject
  {
   public:
    explicit MeterCustomDecrement(const Model& model, const std::string& sourceMeterName);

    virtual ~MeterCustomDecrement() override = default;
    MeterCustomDecrement(const MeterCustomDecrement& other) = default;
    MeterCustomDecrement(MeterCustomDecrement&& other) = default;
    MeterCustomDecrement& operator=(const MeterCustomDecrement&) = default;
    MeterCustomDecrement& operator=(MeterCustomDecrement&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> fuelTypeValues();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model::MeterCustomDecrement scalar accessor naming/signatures for counterpart parity.
    // - Field Mapping: fuelType maps to EnergyPlus Meter:CustomDecrement field Resource Type.
    // - Field Mapping: sourceMeterName maps to EnergyPlus Meter:CustomDecrement field Source Meter Name.
    // - Field Mapping: Extensible Key Name / Output Variable or Meter Name pairs are relationship-like and excluded from scalar scope.
    // - ForwardTranslator evidence: ForwardTranslateMeterCustomDecrement.cpp writes modelObject.fuelType() and sourceMeterName() to
    //   Meter_CustomDecrementFields::ResourceType and Meter_CustomDecrementFields::SourceMeterName.
    // - TODO(parity): Add non-scalar extensible key/variable group APIs without changing these scalar signatures.
    boost::optional<std::string> fuelType() const;
    bool setFuelType(const std::string& fuelType);
    void resetFuelType();

    std::string sourceMeterName() const;
    bool setSourceMeterName(const std::string& sourceMeterName);

   protected:
    using ImplType = detail::MeterCustomDecrement_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit MeterCustomDecrement(std::shared_ptr<detail::MeterCustomDecrement_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
