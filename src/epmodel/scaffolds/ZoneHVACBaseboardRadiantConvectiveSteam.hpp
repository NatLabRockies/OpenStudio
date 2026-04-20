/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACBASEBOARDRADIANTCONVECTIVESTEAM_HPP
#define EPMODEL_ZONEHVACBASEBOARDRADIANTCONVECTIVESTEAM_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <boost/optional.hpp>
#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ZoneHVACBaseboardRadiantConvectiveSteam_Impl;
  }

  class EPMODEL_API ZoneHVACBaseboardRadiantConvectiveSteam : public ModelObject
  {
   public:
    explicit ZoneHVACBaseboardRadiantConvectiveSteam(const Model& model);
    virtual ~ZoneHVACBaseboardRadiantConvectiveSteam() override = default;
    ZoneHVACBaseboardRadiantConvectiveSteam(const ZoneHVACBaseboardRadiantConvectiveSteam& other) = default;
    ZoneHVACBaseboardRadiantConvectiveSteam(ZoneHVACBaseboardRadiantConvectiveSteam&& other) = default;
    ZoneHVACBaseboardRadiantConvectiveSteam& operator=(const ZoneHVACBaseboardRadiantConvectiveSteam&) = default;
    ZoneHVACBaseboardRadiantConvectiveSteam& operator=(ZoneHVACBaseboardRadiantConvectiveSteam&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: heatingDesignCapacity, degreeofSubCooling, and maximumSteamFlowRate map to the EnergyPlus
    //   ZoneHVAC:Baseboard:RadiantConvective:Steam fields Heating Design Capacity, Degree of SubCooling, and Maximum Steam Flow Rate.
    // - The Design Object, Availability Schedule Name, node names, and surface extensible fields remain relationship-only targets and are
    //   intentionally excluded from this scalar-only API.

    // heatingDesignCapacity
    boost::optional<double> heatingDesignCapacity() const;
    bool isHeatingDesignCapacityAutosized() const;
    bool setHeatingDesignCapacity(double heatingDesignCapacity);
    void autosizeHeatingDesignCapacity();

    // degreeofSubCooling
    boost::optional<double> degreeofSubCooling() const;
    bool isDegreeofSubCoolingDefaulted() const;
    bool setDegreeofSubCooling(double degreeofSubCooling);
    void resetDegreeofSubCooling();

    // maximumSteamFlowRate
    boost::optional<double> maximumSteamFlowRate() const;
    bool isMaximumSteamFlowRateAutosized() const;
    bool setMaximumSteamFlowRate(double maximumSteamFlowRate);
    void autosizeMaximumSteamFlowRate();

   protected:
    using ImplType = detail::ZoneHVACBaseboardRadiantConvectiveSteam_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ZoneHVACBaseboardRadiantConvectiveSteam(std::shared_ptr<detail::ZoneHVACBaseboardRadiantConvectiveSteam_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
