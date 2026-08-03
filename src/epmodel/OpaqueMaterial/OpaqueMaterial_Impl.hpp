/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_OPAQUEMATERIAL_IMPL_HPP
#define EPMODEL_OPAQUEMATERIAL_IMPL_HPP

#include "Material/Material_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API OpaqueMaterial_Impl : public Material_Impl
    {
     public:
      using Material_Impl::Material_Impl;
      virtual ~OpaqueMaterial_Impl() override = default;

      virtual double thermalConductivity() const;
      virtual bool setThermalConductivity(double value);

      virtual double thermalConductance() const;
      virtual bool setThermalConductance(double value);

      virtual double thermalResistivity() const;
      virtual bool setThermalResistivity(double value);

      virtual double thermalResistance() const = 0;
      virtual bool setThermalResistance(double value) = 0;

      virtual double thermalAbsorptance() const;
      virtual bool setThermalAbsorptance(double value);

      virtual boost::optional<double> thermalReflectance() const;
      virtual bool setThermalReflectance(boost::optional<double> value);

      virtual double solarAbsorptance() const;
      virtual bool setSolarAbsorptance(boost::optional<double> value);

      virtual boost::optional<double> solarReflectance() const;
      virtual bool setSolarReflectance(boost::optional<double> value);

      virtual double visibleAbsorptance() const;
      virtual bool setVisibleAbsorptance(boost::optional<double> value);

      virtual boost::optional<double> visibleReflectance() const;
      virtual bool setVisibleReflectance(boost::optional<double> value);

      virtual boost::optional<double> heatCapacity() const;

      virtual boost::optional<double> getVisibleTransmittance() const override;
      virtual boost::optional<double> interiorVisibleAbsorptance() const override;
      virtual boost::optional<double> exteriorVisibleAbsorptance() const override;

     private:
      REGISTER_LOGGER("openstudio.epmodel.OpaqueMaterial");
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
