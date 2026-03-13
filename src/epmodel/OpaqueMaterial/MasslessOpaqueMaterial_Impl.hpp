/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_MASSLESSOPAQUEMATERIAL_IMPL_HPP
#define EPMODEL_MASSLESSOPAQUEMATERIAL_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API MasslessOpaqueMaterial_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~MasslessOpaqueMaterial_Impl() override = default;

      std::string roughness() const;
      bool setRoughness(const std::string& roughness);

      double thermalResistance() const;
      bool setThermalResistance(double thermalResistance);

      boost::optional<double> thermalAbsorptance() const;
      bool isThermalAbsorptanceDefaulted() const;
      bool setThermalAbsorptance(double thermalAbsorptance);
      void resetThermalAbsorptance();

      boost::optional<double> solarAbsorptance() const;
      bool isSolarAbsorptanceDefaulted() const;
      bool setSolarAbsorptance(double solarAbsorptance);
      void resetSolarAbsorptance();

      boost::optional<double> visibleAbsorptance() const;
      bool isVisibleAbsorptanceDefaulted() const;
      bool setVisibleAbsorptance(double visibleAbsorptance);
      void resetVisibleAbsorptance();

      std::vector<std::string> roughnessValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
