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
