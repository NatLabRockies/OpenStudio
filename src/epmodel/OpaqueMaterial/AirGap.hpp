/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRGAP_HPP
#define EPMODEL_AIRGAP_HPP

#include "EPModelAPI.hpp"
#include "Material/Material.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class AirGap_Impl;
  }

  class EPMODEL_API AirGap : public Material
  {
   public:
    explicit AirGap(const Model& model, double thermalResistance = 0.1);

    virtual ~AirGap() override = default;
    AirGap(const AirGap& other) = default;
    AirGap(AirGap&& other) = default;
    AirGap& operator=(const AirGap&) = default;
    AirGap& operator=(AirGap&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Preserves openstudio::model::AirGap scalar accessor names/signatures.
    // - Field Mapping: thermalResistance/setThermalResistance/resetThermalResistance map to E+ Material:AirGap Thermal Resistance.
    // - ForwardTranslator evidence: ForwardTranslateAirGap.cpp writes model AirGap::thermalResistance directly to Material:AirGap Thermal Resistance.
    // - TODO(parity): Introduce an epmodel OpaqueMaterial hierarchy and migrate AirGap inheritance when broader opaque-material parity lands.
    double thermalResistance() const;

    bool setThermalResistance(double thermalResistance);
    void resetThermalResistance();

   protected:
    using ImplType = detail::AirGap_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AirGap(std::shared_ptr<detail::AirGap_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
