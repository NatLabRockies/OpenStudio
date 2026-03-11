/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SKYTEMPERATURE_HPP
#define EPMODEL_SKYTEMPERATURE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SkyTemperature_Impl;
  }

  class EPMODEL_API SkyTemperature : public ModelObject
  {
   public:
    explicit SkyTemperature(const Model& model);

    virtual ~SkyTemperature() override = default;
    SkyTemperature(const SkyTemperature& other) = default;
    SkyTemperature(SkyTemperature&& other) = default;
    SkyTemperature& operator=(const SkyTemperature&) = default;
    SkyTemperature& operator=(SkyTemperature&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> calculationTypeValues();

    std::string calculationType() const;
    bool setCalculationType(const std::string& calculationType);
    bool isCalculationTypeDefaulted() const;
    void resetCalculationType();

    bool useWeatherFileHorizontalIR() const;
    bool setUseWeatherFileHorizontalIR(bool useWeatherFileHorizontalIR);
    bool isUseWeatherFileHorizontalIRDefaulted() const;
    void resetUseWeatherFileHorizontalIR();

    // Schema Alignment Notes:
    // - API: preserves the openstudio::model::SkyTemperature name/signature and keeps the same EnergyPlus counterpart for parity.
    // - Field Mapping: calculationType() and useWeatherFileHorizontalIR() map directly to WeatherProperty:SkyTemperature's Calculation Type and Use Weather File Horizontal IR fields via WeatherProperty_SkyTemperatureFields; Name and Schedule Name remain object-list relationships managed by the ModelObject base.
    // - Field Mapping: ForwardTranslator::translateSkyTemperature generates WeatherProperty:SkyTemperature for exports, so this epmodel type mirrors that alignment while keeping the existing API names.
    // - TODO(parity): add object-list helpers for the Schedule Name relationship once non-scalar coverage is required.

   protected:
    using ImplType = detail::SkyTemperature_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SkyTemperature(std::shared_ptr<detail::SkyTemperature_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
