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

/** \brief The design-side data used by a radiant-convective hot-water baseboard.
 *
 * \par EnergyPlus object
 * \epobject{group-radiative-convective-units.html#zonehvac-baseboard-radiantconvective-water-design,ZoneHVAC:Baseboard:RadiantConvective:Water:Design}
 *
 * \par Important behavior
 * This EPModel type exposes the split-out design-capacity and convergence fields directly.
 *
 * \par OpenStudio Model API
 * The corresponding OpenStudio Model class is <code>There is no same-name openstudio::model wrapper; its behavior is part of openstudio::model::ZoneHVACBaseboardRadiantConvectiveWater.</code>.
 *
 * \par Known limitations
 * It is a persisted EnergyPlus companion rather than an independent OpenStudio
 * Model component, and it has no zone or plant topology of its own.
 */
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
