/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_DAYLIGHTINGDEVICETUBULAR_HPP
#define EPMODEL_DAYLIGHTINGDEVICETUBULAR_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class DaylightingDeviceTubular_Impl;
  }

  class EPMODEL_API DaylightingDeviceTubular : public ModelObject
  {
   public:
    explicit DaylightingDeviceTubular(const Model& model);

    virtual ~DaylightingDeviceTubular() override = default;
    DaylightingDeviceTubular(const DaylightingDeviceTubular& other) = default;
    DaylightingDeviceTubular(DaylightingDeviceTubular&& other) = default;
    DaylightingDeviceTubular& operator=(const DaylightingDeviceTubular&) = default;
    DaylightingDeviceTubular& operator=(DaylightingDeviceTubular&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Preserves openstudio::model scalar accessor naming/signatures for counterpart parity.
    // - Field Mapping: diameter, totalLength, and effectiveThermalResistance map directly to
    //   DaylightingDevice:Tubular scalar fields Diameter, Total Length, and Effective Thermal Resistance.
    // - Field Mapping: Dome Name, Diffuser Name, Construction Name, and extensible Transition Zone fields
    //   are relationship-like links and intentionally excluded from scalar accessors.
    // - ForwardTranslator evidence: translateDaylightingDeviceTubular writes these three scalar fields
    //   directly from modelObject.diameter(), modelObject.totalLength(), and modelObject.effectiveThermalResistance().
    // - TODO(parity): Add typed relationship/extensible APIs during non-scalar parity work.
    double diameter() const;
    bool setDiameter(double diameter);

    double totalLength() const;
    bool setTotalLength(double totalLength);

    double effectiveThermalResistance() const;
    bool setEffectiveThermalResistance(double effectiveThermalResistance);
    bool isEffectiveThermalResistanceDefaulted() const;
    void resetEffectiveThermalResistance();

   protected:
    using ImplType = detail::DaylightingDeviceTubular_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit DaylightingDeviceTubular(std::shared_ptr<detail::DaylightingDeviceTubular_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
