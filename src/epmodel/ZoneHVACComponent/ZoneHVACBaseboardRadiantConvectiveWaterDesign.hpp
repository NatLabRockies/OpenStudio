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
    // - Status: Scalar Parity. This split design-side wrapper exposes a small scalar surface and has no direct same-name canonical model peer.
    // - Canonical Counterpart: openstudio::model::ZoneHVACBaseboardRadiantConvectiveWater.
    // - Implemented Parity: The design-capacity method, heating-capacity sizing scalars, convergence tolerance, radiant fraction, and people-incident radiant fraction map directly to the EnergyPlus design-only fields.
    // - Documented Delta: This epmodel type is an EnergyPlus split-out design object with no same-name canonical `openstudio::model` wrapper, so the closest canonical behavior is represented by the broader ZoneHVACBaseboardRadiantConvectiveWater wrapper.
    // - Field/Storage Mapping: The object carries only scalar design inputs; no additional relationship-only children exist beyond the base name storage.
    // - Evidence: `src/model/ZoneHVACBaseboardRadiantConvectiveWater.hpp`, `src/model/ZoneHVACBaseboardRadiantConvectiveWater.cpp`, and `src/epmodel/test/ZoneHVACBaseboardRadiantConvectiveWaterDesign_GTest.cpp`.
    // - Remaining Parity Work: Keep the split-design scalar surface aligned with the canonical baseboard wrapper and document any future split-out deltas here.
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
