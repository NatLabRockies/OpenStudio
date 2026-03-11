/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACBASEBOARDRADIANTCONVECTIVESTEAMDESIGN_HPP
#define EPMODEL_ZONEHVACBASEBOARDRADIANTCONVECTIVESTEAMDESIGN_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <boost/optional.hpp>
#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ZoneHVACBaseboardRadiantConvectiveSteamDesign_Impl;
  }

  class EPMODEL_API ZoneHVACBaseboardRadiantConvectiveSteamDesign : public ModelObject
  {
   public:
    explicit ZoneHVACBaseboardRadiantConvectiveSteamDesign(const Model& model);
    virtual ~ZoneHVACBaseboardRadiantConvectiveSteamDesign() override = default;
    ZoneHVACBaseboardRadiantConvectiveSteamDesign(const ZoneHVACBaseboardRadiantConvectiveSteamDesign& other) = default;
    ZoneHVACBaseboardRadiantConvectiveSteamDesign(ZoneHVACBaseboardRadiantConvectiveSteamDesign&& other) = default;
    ZoneHVACBaseboardRadiantConvectiveSteamDesign& operator=(const ZoneHVACBaseboardRadiantConvectiveSteamDesign&) = default;
    ZoneHVACBaseboardRadiantConvectiveSteamDesign& operator=(ZoneHVACBaseboardRadiantConvectiveSteamDesign&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> heatingDesignCapacityMethodValues();

    // Schema Alignment Notes:
    // - API: heatingDesignCapacityMethod/heatingDesignCapacityPerFloorArea/fractionofAutosizedHeatingDesignCapacity/convergenceTolerance/fractionRadiant/fractionofRadiantEnergyIncidentonPeople
    //   map to the EnergyPlus ZoneHVAC:Baseboard:RadiantConvective:Steam:Design fields with the same names.
    // - Name/reference relationships are inherited from ModelObject, and the extensible surface entries remain relationship-only targets that are intentionally excluded.
    std::string heatingDesignCapacityMethod() const;
    bool setHeatingDesignCapacityMethod(const std::string& heatingDesignCapacityMethod);
    void resetHeatingDesignCapacityMethod();

    boost::optional<double> heatingDesignCapacityPerFloorArea() const;
    bool setHeatingDesignCapacityPerFloorArea(double heatingDesignCapacityPerFloorArea);
    void resetHeatingDesignCapacityPerFloorArea();

    double fractionofAutosizedHeatingDesignCapacity() const;
    bool isFractionofAutosizedHeatingDesignCapacityDefaulted() const;
    bool setFractionofAutosizedHeatingDesignCapacity(double fractionofAutosizedHeatingDesignCapacity);
    void resetFractionofAutosizedHeatingDesignCapacity();

    double convergenceTolerance() const;
    bool isConvergenceToleranceDefaulted() const;
    bool setConvergenceTolerance(double convergenceTolerance);
    void resetConvergenceTolerance();

    double fractionRadiant() const;
    bool setFractionRadiant(double fractionRadiant);

    boost::optional<double> fractionofRadiantEnergyIncidentonPeople() const;
    bool setFractionofRadiantEnergyIncidentonPeople(double fractionofRadiantEnergyIncidentonPeople);
    void resetFractionofRadiantEnergyIncidentonPeople();

   protected:
    using ImplType = detail::ZoneHVACBaseboardRadiantConvectiveSteamDesign_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ZoneHVACBaseboardRadiantConvectiveSteamDesign(std::shared_ptr<detail::ZoneHVACBaseboardRadiantConvectiveSteamDesign_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
