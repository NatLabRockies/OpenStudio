/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_WINDOWMATERIALSCREENEQUIVALENTLAYER_IMPL_HPP
#define EPMODEL_WINDOWMATERIALSCREENEQUIVALENTLAYER_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <string>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API WindowMaterialScreenEquivalentLayer_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~WindowMaterialScreenEquivalentLayer_Impl() override = default;

      boost::optional<double> screenBeamBeamSolarTransmittance() const;
      bool isScreenBeamBeamSolarTransmittanceDefaulted() const;
      bool isScreenBeamBeamSolarTransmittanceAutocalculated() const;
      bool setScreenBeamBeamSolarTransmittance(double screenBeamBeamSolarTransmittance);
      void resetScreenBeamBeamSolarTransmittance();
      void autocalculateScreenBeamBeamSolarTransmittance();

      double screenBeamDiffuseSolarTransmittance() const;
      bool setScreenBeamDiffuseSolarTransmittance(double screenBeamDiffuseSolarTransmittance);
      double screenBeamDiffuseSolarReflectance() const;
      bool setScreenBeamDiffuseSolarReflectance(double screenBeamDiffuseSolarReflectance);
      double screenBeamBeamVisibleSolarTransmittance() const;
      bool setScreenBeamBeamVisibleSolarTransmittance(double screenBeamBeamVisibleSolarTransmittance);
      double screenBeamDiffuseVisibleSolarTransmittance() const;
      bool setScreenBeamDiffuseVisibleSolarTransmittance(double screenBeamDiffuseVisibleSolarTransmittance);
      double screenBeamDiffuseVisibleSolarReflectance() const;
      bool setScreenBeamDiffuseVisibleSolarReflectance(double screenBeamDiffuseVisibleSolarReflectance);

      double screenInfraredTransmittance() const;
      bool isScreenInfraredTransmittanceDefaulted() const;
      bool setScreenInfraredTransmittance(double screenInfraredTransmittance);
      void resetScreenInfraredTransmittance();

      double screenInfraredEmissivity() const;
      bool isScreenInfraredEmissivityDefaulted() const;
      bool setScreenInfraredEmissivity(double screenInfraredEmissivity);
      void resetScreenInfraredEmissivity();

      double screenWireSpacing() const;
      bool isScreenWireSpacingDefaulted() const;
      bool setScreenWireSpacing(double screenWireSpacing);
      void resetScreenWireSpacing();

      double screenWireDiameter() const;
      bool isScreenWireDiameterDefaulted() const;
      bool setScreenWireDiameter(double screenWireDiameter);
      void resetScreenWireDiameter();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
