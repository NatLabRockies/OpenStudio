/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_WINDOWMATERIALGLAZINGEQUIVALENTLAYER_IMPL_HPP
#define EPMODEL_WINDOWMATERIALGLAZINGEQUIVALENTLAYER_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <string>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API WindowMaterialGlazingEquivalentLayer_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~WindowMaterialGlazingEquivalentLayer_Impl() override = default;

      std::string opticalDataType() const;
      bool isOpticalDataTypeDefaulted() const;
      bool setOpticalDataType(const std::string& opticalDataType);
      void resetOpticalDataType();

      double frontSideBeamBeamSolarTransmittance() const;
      bool setFrontSideBeamBeamSolarTransmittance(double frontSideBeamBeamSolarTransmittance);
      double backSideBeamBeamSolarTransmittance() const;
      bool setBackSideBeamBeamSolarTransmittance(double backSideBeamBeamSolarTransmittance);
      double frontSideBeamBeamSolarReflectance() const;
      bool setFrontSideBeamBeamSolarReflectance(double frontSideBeamBeamSolarReflectance);
      double backSideBeamBeamSolarReflectance() const;
      bool setBackSideBeamBeamSolarReflectance(double backSideBeamBeamSolarReflectance);

      double frontSideBeamBeamVisibleSolarTransmittance() const;
      bool isFrontSideBeamBeamVisibleSolarTransmittanceDefaulted() const;
      bool setFrontSideBeamBeamVisibleSolarTransmittance(double frontSideBeamBeamVisibleSolarTransmittance);
      void resetFrontSideBeamBeamVisibleSolarTransmittance();
      double backSideBeamBeamVisibleSolarTransmittance() const;
      bool isBackSideBeamBeamVisibleSolarTransmittanceDefaulted() const;
      bool setBackSideBeamBeamVisibleSolarTransmittance(double backSideBeamBeamVisibleSolarTransmittance);
      void resetBackSideBeamBeamVisibleSolarTransmittance();
      double frontSideBeamBeamVisibleSolarReflectance() const;
      bool isFrontSideBeamBeamVisibleSolarReflectanceDefaulted() const;
      bool setFrontSideBeamBeamVisibleSolarReflectance(double frontSideBeamBeamVisibleSolarReflectance);
      void resetFrontSideBeamBeamVisibleSolarReflectance();
      double backSideBeamBeamVisibleSolarReflectance() const;
      bool isBackSideBeamBeamVisibleSolarReflectanceDefaulted() const;
      bool setBackSideBeamBeamVisibleSolarReflectance(double backSideBeamBeamVisibleSolarReflectance);
      void resetBackSideBeamBeamVisibleSolarReflectance();

      double frontSideBeamDiffuseSolarTransmittance() const;
      bool isFrontSideBeamDiffuseSolarTransmittanceDefaulted() const;
      bool setFrontSideBeamDiffuseSolarTransmittance(double frontSideBeamDiffuseSolarTransmittance);
      void resetFrontSideBeamDiffuseSolarTransmittance();
      double backSideBeamDiffuseSolarTransmittance() const;
      bool isBackSideBeamDiffuseSolarTransmittanceDefaulted() const;
      bool setBackSideBeamDiffuseSolarTransmittance(double backSideBeamDiffuseSolarTransmittance);
      void resetBackSideBeamDiffuseSolarTransmittance();
      double frontSideBeamDiffuseSolarReflectance() const;
      bool isFrontSideBeamDiffuseSolarReflectanceDefaulted() const;
      bool setFrontSideBeamDiffuseSolarReflectance(double frontSideBeamDiffuseSolarReflectance);
      void resetFrontSideBeamDiffuseSolarReflectance();
      double backSideBeamDiffuseSolarReflectance() const;
      bool isBackSideBeamDiffuseSolarReflectanceDefaulted() const;
      bool setBackSideBeamDiffuseSolarReflectance(double backSideBeamDiffuseSolarReflectance);
      void resetBackSideBeamDiffuseSolarReflectance();

      double frontSideBeamDiffuseVisibleSolarTransmittance() const;
      bool isFrontSideBeamDiffuseVisibleSolarTransmittanceDefaulted() const;
      bool setFrontSideBeamDiffuseVisibleSolarTransmittance(double frontSideBeamDiffuseVisibleSolarTransmittance);
      void resetFrontSideBeamDiffuseVisibleSolarTransmittance();
      double backSideBeamDiffuseVisibleSolarTransmittance() const;
      bool isBackSideBeamDiffuseVisibleSolarTransmittanceDefaulted() const;
      bool setBackSideBeamDiffuseVisibleSolarTransmittance(double backSideBeamDiffuseVisibleSolarTransmittance);
      void resetBackSideBeamDiffuseVisibleSolarTransmittance();
      double frontSideBeamDiffuseVisibleSolarReflectance() const;
      bool isFrontSideBeamDiffuseVisibleSolarReflectanceDefaulted() const;
      bool setFrontSideBeamDiffuseVisibleSolarReflectance(double frontSideBeamDiffuseVisibleSolarReflectance);
      void resetFrontSideBeamDiffuseVisibleSolarReflectance();
      double backSideBeamDiffuseVisibleSolarReflectance() const;
      bool isBackSideBeamDiffuseVisibleSolarReflectanceDefaulted() const;
      bool setBackSideBeamDiffuseVisibleSolarReflectance(double backSideBeamDiffuseVisibleSolarReflectance);
      void resetBackSideBeamDiffuseVisibleSolarReflectance();

      boost::optional<double> diffuseDiffuseSolarTransmittance() const;
      bool isDiffuseDiffuseSolarTransmittanceDefaulted() const;
      bool isDiffuseDiffuseSolarTransmittanceAutocalculated() const;
      bool setDiffuseDiffuseSolarTransmittance(double diffuseDiffuseSolarTransmittance);
      void resetDiffuseDiffuseSolarTransmittance();
      void autocalculateDiffuseDiffuseSolarTransmittance();

      boost::optional<double> frontSideDiffuseDiffuseSolarReflectance() const;
      bool isFrontSideDiffuseDiffuseSolarReflectanceDefaulted() const;
      bool isFrontSideDiffuseDiffuseSolarReflectanceAutocalculated() const;
      bool setFrontSideDiffuseDiffuseSolarReflectance(double frontSideDiffuseDiffuseSolarReflectance);
      void resetFrontSideDiffuseDiffuseSolarReflectance();
      void autocalculateFrontSideDiffuseDiffuseSolarReflectance();

      boost::optional<double> backSideDiffuseDiffuseSolarReflectance() const;
      bool isBackSideDiffuseDiffuseSolarReflectanceDefaulted() const;
      bool isBackSideDiffuseDiffuseSolarReflectanceAutocalculated() const;
      bool setBackSideDiffuseDiffuseSolarReflectance(double backSideDiffuseDiffuseSolarReflectance);
      void resetBackSideDiffuseDiffuseSolarReflectance();
      void autocalculateBackSideDiffuseDiffuseSolarReflectance();

      boost::optional<double> diffuseDiffuseVisibleSolarTransmittance() const;
      bool isDiffuseDiffuseVisibleSolarTransmittanceDefaulted() const;
      bool isDiffuseDiffuseVisibleSolarTransmittanceAutocalculated() const;
      bool setDiffuseDiffuseVisibleSolarTransmittance(double diffuseDiffuseVisibleSolarTransmittance);
      void resetDiffuseDiffuseVisibleSolarTransmittance();
      void autocalculateDiffuseDiffuseVisibleSolarTransmittance();

      boost::optional<double> frontSideDiffuseDiffuseVisibleSolarReflectance() const;
      bool isFrontSideDiffuseDiffuseVisibleSolarReflectanceDefaulted() const;
      bool isFrontSideDiffuseDiffuseVisibleSolarReflectanceAutocalculated() const;
      bool setFrontSideDiffuseDiffuseVisibleSolarReflectance(double frontSideDiffuseDiffuseVisibleSolarReflectance);
      void resetFrontSideDiffuseDiffuseVisibleSolarReflectance();
      void autocalculateFrontSideDiffuseDiffuseVisibleSolarReflectance();

      boost::optional<double> backSideDiffuseDiffuseVisibleSolarReflectance() const;
      bool isBackSideDiffuseDiffuseVisibleSolarReflectanceDefaulted() const;
      bool isBackSideDiffuseDiffuseVisibleSolarReflectanceAutocalculated() const;
      bool setBackSideDiffuseDiffuseVisibleSolarReflectance(double backSideDiffuseDiffuseVisibleSolarReflectance);
      void resetBackSideDiffuseDiffuseVisibleSolarReflectance();
      void autocalculateBackSideDiffuseDiffuseVisibleSolarReflectance();

      double infraredTransmittance() const;
      bool isInfraredTransmittanceDefaulted() const;
      bool setInfraredTransmittance(double infraredTransmittance);
      void resetInfraredTransmittance();

      double frontSideInfraredEmissivity() const;
      bool isFrontSideInfraredEmissivityDefaulted() const;
      bool setFrontSideInfraredEmissivity(double frontSideInfraredEmissivity);
      void resetFrontSideInfraredEmissivity();

      double backSideInfraredEmissivity() const;
      bool isBackSideInfraredEmissivityDefaulted() const;
      bool setBackSideInfraredEmissivity(double backSideInfraredEmissivity);
      void resetBackSideInfraredEmissivity();

      double thermalResistance() const;
      bool isThermalResistanceDefaulted() const;
      bool setThermalResistance(double thermalResistance);
      void resetThermalResistance();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
