/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GROUNDHEATTRANSFERBASEMENTMATLPROPS_HPP
#define EPMODEL_GROUNDHEATTRANSFERBASEMENTMATLPROPS_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class GroundHeatTransferBasementMatlProps_Impl;
}

class EPMODEL_API GroundHeatTransferBasementMatlProps : public ModelObject
{
 public:
  explicit GroundHeatTransferBasementMatlProps(const Model& model);

  virtual ~GroundHeatTransferBasementMatlProps() override = default;
  GroundHeatTransferBasementMatlProps(const GroundHeatTransferBasementMatlProps& other) = default;
  GroundHeatTransferBasementMatlProps(GroundHeatTransferBasementMatlProps&& other) = default;
  GroundHeatTransferBasementMatlProps& operator=(const GroundHeatTransferBasementMatlProps&) = default;
  GroundHeatTransferBasementMatlProps& operator=(GroundHeatTransferBasementMatlProps&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived class/accessor naming.
  // - Field Mapping: Scalar APIs map directly to GroundHeatTransfer:Basement:MatlProps N1-N19 material fields.
  // - TODO(parity): Add relationship APIs incrementally if future schema revisions introduce link fields.
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

 protected:
  using ImplType = detail::GroundHeatTransferBasementMatlProps_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit GroundHeatTransferBasementMatlProps(std::shared_ptr<detail::GroundHeatTransferBasementMatlProps_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
