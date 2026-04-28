/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GROUNDHEATTRANSFERBASEMENTMATLPROPS_IMPL_HPP
#define EPMODEL_GROUNDHEATTRANSFERBASEMENTMATLPROPS_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API GroundHeatTransferBasementMatlProps_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~GroundHeatTransferBasementMatlProps_Impl() override = default;

      double nMATNumberofmaterialsinthisdomain() const;
      bool setNMATNumberofmaterialsinthisdomain(double nMATNumberofmaterialsinthisdomain);

      double densityforFoundationWall() const;
      bool isDensityforFoundationWallDefaulted() const;
      bool setDensityforFoundationWall(double densityforFoundationWall);
      void resetDensityforFoundationWall();

      double densityforFloorSlab() const;
      bool isDensityforFloorSlabDefaulted() const;
      bool setDensityforFloorSlab(double densityforFloorSlab);
      void resetDensityforFloorSlab();

      double densityforCeiling() const;
      bool isDensityforCeilingDefaulted() const;
      bool setDensityforCeiling(double densityforCeiling);
      void resetDensityforCeiling();

      double densityforSoil() const;
      bool isDensityforSoilDefaulted() const;
      bool setDensityforSoil(double densityforSoil);
      void resetDensityforSoil();

      double densityforGravel() const;
      bool isDensityforGravelDefaulted() const;
      bool setDensityforGravel(double densityforGravel);
      void resetDensityforGravel();

      double densityforWood() const;
      bool isDensityforWoodDefaulted() const;
      bool setDensityforWood(double densityforWood);
      void resetDensityforWood();

      double specificheatforfoundationwall() const;
      bool isSpecificheatforfoundationwallDefaulted() const;
      bool setSpecificheatforfoundationwall(double specificheatforfoundationwall);
      void resetSpecificheatforfoundationwall();

      double specificheatforfloorslab() const;
      bool isSpecificheatforfloorslabDefaulted() const;
      bool setSpecificheatforfloorslab(double specificheatforfloorslab);
      void resetSpecificheatforfloorslab();

      double specificheatforceiling() const;
      bool isSpecificheatforceilingDefaulted() const;
      bool setSpecificheatforceiling(double specificheatforceiling);
      void resetSpecificheatforceiling();

      double specificheatforsoil() const;
      bool isSpecificheatforsoilDefaulted() const;
      bool setSpecificheatforsoil(double specificheatforsoil);
      void resetSpecificheatforsoil();

      double specificheatforgravel() const;
      bool isSpecificheatforgravelDefaulted() const;
      bool setSpecificheatforgravel(double specificheatforgravel);
      void resetSpecificheatforgravel();

      double specificheatforwood() const;
      bool isSpecificheatforwoodDefaulted() const;
      bool setSpecificheatforwood(double specificheatforwood);
      void resetSpecificheatforwood();

      double thermalconductivityforfoundationwall() const;
      bool isThermalconductivityforfoundationwallDefaulted() const;
      bool setThermalconductivityforfoundationwall(double thermalconductivityforfoundationwall);
      void resetThermalconductivityforfoundationwall();

      double thermalconductivityforfloorslab() const;
      bool isThermalconductivityforfloorslabDefaulted() const;
      bool setThermalconductivityforfloorslab(double thermalconductivityforfloorslab);
      void resetThermalconductivityforfloorslab();

      double thermalconductivityforceiling() const;
      bool isThermalconductivityforceilingDefaulted() const;
      bool setThermalconductivityforceiling(double thermalconductivityforceiling);
      void resetThermalconductivityforceiling();

      double thermalconductivityforsoil() const;
      bool isThermalconductivityforsoilDefaulted() const;
      bool setThermalconductivityforsoil(double thermalconductivityforsoil);
      void resetThermalconductivityforsoil();

      double thermalconductivityforgravel() const;
      bool isThermalconductivityforgravelDefaulted() const;
      bool setThermalconductivityforgravel(double thermalconductivityforgravel);
      void resetThermalconductivityforgravel();

      double thermalconductivityforwood() const;
      bool isThermalconductivityforwoodDefaulted() const;
      bool setThermalconductivityforwood(double thermalconductivityforwood);
      void resetThermalconductivityforwood();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
