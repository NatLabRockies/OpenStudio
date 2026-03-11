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
  double densityforFoundationWall() const;
  double densityforFloorSlab() const;
  double densityforCeiling() const;
  double densityforSoil() const;
  double densityforGravel() const;
  double densityforWood() const;
  double specificheatforfoundationwall() const;
  double specificheatforfloorslab() const;
  double specificheatforceiling() const;
  double specificheatforsoil() const;
  double specificheatforgravel() const;
  double specificheatforwood() const;
  double thermalconductivityforfoundationwall() const;
  double thermalconductivityforfloorslab() const;
  double thermalconductivityforceiling() const;
  double thermalconductivityforsoil() const;
  double thermalconductivityforgravel() const;
  double thermalconductivityforwood() const;

  bool isDensityforFoundationWallDefaulted() const;
  bool isDensityforFloorSlabDefaulted() const;
  bool isDensityforCeilingDefaulted() const;
  bool isDensityforSoilDefaulted() const;
  bool isDensityforGravelDefaulted() const;
  bool isDensityforWoodDefaulted() const;
  bool isSpecificheatforfoundationwallDefaulted() const;
  bool isSpecificheatforfloorslabDefaulted() const;
  bool isSpecificheatforceilingDefaulted() const;
  bool isSpecificheatforsoilDefaulted() const;
  bool isSpecificheatforgravelDefaulted() const;
  bool isSpecificheatforwoodDefaulted() const;
  bool isThermalconductivityforfoundationwallDefaulted() const;
  bool isThermalconductivityforfloorslabDefaulted() const;
  bool isThermalconductivityforceilingDefaulted() const;
  bool isThermalconductivityforsoilDefaulted() const;
  bool isThermalconductivityforgravelDefaulted() const;
  bool isThermalconductivityforwoodDefaulted() const;

  bool setNMATNumberofmaterialsinthisdomain(double nMATNumberofmaterialsinthisdomain);
  bool setDensityforFoundationWall(double densityforFoundationWall);
  bool setDensityforFloorSlab(double densityforFloorSlab);
  bool setDensityforCeiling(double densityforCeiling);
  bool setDensityforSoil(double densityforSoil);
  bool setDensityforGravel(double densityforGravel);
  bool setDensityforWood(double densityforWood);
  bool setSpecificheatforfoundationwall(double specificheatforfoundationwall);
  bool setSpecificheatforfloorslab(double specificheatforfloorslab);
  bool setSpecificheatforceiling(double specificheatforceiling);
  bool setSpecificheatforsoil(double specificheatforsoil);
  bool setSpecificheatforgravel(double specificheatforgravel);
  bool setSpecificheatforwood(double specificheatforwood);
  bool setThermalconductivityforfoundationwall(double thermalconductivityforfoundationwall);
  bool setThermalconductivityforfloorslab(double thermalconductivityforfloorslab);
  bool setThermalconductivityforceiling(double thermalconductivityforceiling);
  bool setThermalconductivityforsoil(double thermalconductivityforsoil);
  bool setThermalconductivityforgravel(double thermalconductivityforgravel);
  bool setThermalconductivityforwood(double thermalconductivityforwood);

  void resetDensityforFoundationWall();
  void resetDensityforFloorSlab();
  void resetDensityforCeiling();
  void resetDensityforSoil();
  void resetDensityforGravel();
  void resetDensityforWood();
  void resetSpecificheatforfoundationwall();
  void resetSpecificheatforfloorslab();
  void resetSpecificheatforceiling();
  void resetSpecificheatforsoil();
  void resetSpecificheatforgravel();
  void resetSpecificheatforwood();
  void resetThermalconductivityforfoundationwall();
  void resetThermalconductivityforfloorslab();
  void resetThermalconductivityforceiling();
  void resetThermalconductivityforsoil();
  void resetThermalconductivityforgravel();
  void resetThermalconductivityforwood();
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
