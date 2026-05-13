/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_MASSLESSOPAQUEMATERIAL_IMPL_HPP
#define EPMODEL_MASSLESSOPAQUEMATERIAL_IMPL_HPP

#include "OpaqueMaterial/OpaqueMaterial_Impl.hpp"

#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API MasslessOpaqueMaterial_Impl : public OpaqueMaterial_Impl
    {
     public:
      using OpaqueMaterial_Impl::OpaqueMaterial_Impl;
      virtual ~MasslessOpaqueMaterial_Impl() override = default;

      std::string roughness() const;
      bool setRoughness(const std::string& roughness);

      double thermalResistance() const override;
      bool setThermalResistance(double thermalResistance) override;

      double thermalAbsorptance() const override;
      bool isThermalAbsorptanceDefaulted() const;
      bool setThermalAbsorptance(double thermalAbsorptance) override;
      void resetThermalAbsorptance();

      double solarAbsorptance() const override;
      bool isSolarAbsorptanceDefaulted() const;
      bool setSolarAbsorptance(double solarAbsorptance);
      void resetSolarAbsorptance();

      double visibleAbsorptance() const override;
      bool isVisibleAbsorptanceDefaulted() const;
      bool setVisibleAbsorptance(double visibleAbsorptance);
      void resetVisibleAbsorptance();

      std::vector<std::string> roughnessValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
