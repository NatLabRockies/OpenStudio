/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACBASEBOARDRADIANTCONVECTIVEWATERDESIGN_HPP
#define EPMODEL_ZONEHVACBASEBOARDRADIANTCONVECTIVEWATERDESIGN_HPP

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
    class ZoneHVACBaseboardRadiantConvectiveWaterDesign_Impl;
  }

  class EPMODEL_API ZoneHVACBaseboardRadiantConvectiveWaterDesign : public ModelObject
  {
   public:
    explicit ZoneHVACBaseboardRadiantConvectiveWaterDesign(const Model& model);

    virtual ~ZoneHVACBaseboardRadiantConvectiveWaterDesign() override = default;
    ZoneHVACBaseboardRadiantConvectiveWaterDesign(const ZoneHVACBaseboardRadiantConvectiveWaterDesign& other) = default;
    ZoneHVACBaseboardRadiantConvectiveWaterDesign(ZoneHVACBaseboardRadiantConvectiveWaterDesign&& other) = default;
    ZoneHVACBaseboardRadiantConvectiveWaterDesign& operator=(const ZoneHVACBaseboardRadiantConvectiveWaterDesign&) = default;
    ZoneHVACBaseboardRadiantConvectiveWaterDesign& operator=(ZoneHVACBaseboardRadiantConvectiveWaterDesign&&) = default;

    static IddObjectType iddObjectType();
    static std::vector<std::string> heatingDesignCapacityMethodValues();

    // Schema Alignment Notes:
    // - API: heatingDesignCapacityMethod, heatingDesignCapacityPerFloorArea, fractionofAutosizedHeatingDesignCapacity,
    //   convergenceTolerance, fractionRadiant, and fractionofRadiantEnergyIncidentonPeople map directly to the
    //   EnergyPlus ZoneHVAC:Baseboard:RadiantConvective:Water:Design fields as enumerated by
    //   ZoneHVAC_Baseboard_RadiantConvective_Water_DesignFields.
    // - No additional relationship-only data exists on this object beyond the name handled by ModelObject.
    std::string heatingDesignCapacityMethod() const;
    bool setHeatingDesignCapacityMethod(const std::string& heatingDesignCapacityMethod);
    void resetHeatingDesignCapacityMethod();

    boost::optional<double> heatingDesignCapacityPerFloorArea() const;
    bool setHeatingDesignCapacityPerFloorArea(double heatingDesignCapacityPerFloorArea);
    void resetHeatingDesignCapacityPerFloorArea();

    double fractionofAutosizedHeatingDesignCapacity() const;
    bool setFractionofAutosizedHeatingDesignCapacity(double fractionofAutosizedHeatingDesignCapacity);
    void resetFractionofAutosizedHeatingDesignCapacity();
    bool isFractionofAutosizedHeatingDesignCapacityDefaulted() const;

    double convergenceTolerance() const;
    bool setConvergenceTolerance(double convergenceTolerance);
    void resetConvergenceTolerance();
    bool isConvergenceToleranceDefaulted() const;

    double fractionRadiant() const;
    bool setFractionRadiant(double fractionRadiant);

    boost::optional<double> fractionofRadiantEnergyIncidentonPeople() const;
    bool setFractionofRadiantEnergyIncidentonPeople(double fractionofRadiantEnergyIncidentonPeople);
    void resetFractionofRadiantEnergyIncidentonPeople();

   protected:
    using ImplType = detail::ZoneHVACBaseboardRadiantConvectiveWaterDesign_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ZoneHVACBaseboardRadiantConvectiveWaterDesign(std::shared_ptr<detail::ZoneHVACBaseboardRadiantConvectiveWaterDesign_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
