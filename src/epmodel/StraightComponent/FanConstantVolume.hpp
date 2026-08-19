/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FANCONSTANTVOLUME_HPP
#define EPMODEL_FANCONSTANTVOLUME_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include "../utilities/idd/IddEnums.hpp"

#include <boost/optional.hpp>
#include <memory>
#include <string>

namespace openstudio {
namespace epmodel {

  class Model;
  class Node;
  class Schedule;

  namespace detail {
    class FanConstantVolume_Impl;
  }

/** \brief A constant-volume fan.
 *
 * \par EnergyPlus object
 * \epobject{group-fans.html#fanconstantvolume,Fan:ConstantVolume}
 *
 * \par Important behavior
 * The availability schedule and scalar fan fields map directly to Fan:ConstantVolume; plant or air-loop node insertion follows straight-component topology.
 *
 * \par OpenStudio Model API
 * The corresponding OpenStudio Model type is <code>openstudio::model::FanConstantVolume</code>.
 *
 * \par Known limitations
 * AirflowNetwork helpers and the autosized maximum-flow convenience are not available.
 */
  class EPMODEL_API FanConstantVolume : public StraightComponent
  {
   public:
    explicit FanConstantVolume(const Model& model);
    FanConstantVolume(const Model& model, Schedule& schedule);

    virtual ~FanConstantVolume() override = default;
    FanConstantVolume(const FanConstantVolume& other) = default;
    FanConstantVolume(FanConstantVolume&& other) = default;
    FanConstantVolume& operator=(const FanConstantVolume&) = default;
    FanConstantVolume& operator=(FanConstantVolume&&) = default;

    static IddObjectType iddObjectType();

    bool addToNode(Node& node);

    Schedule availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);

    double fanTotalEfficiency() const;
    bool setFanTotalEfficiency(double fanTotalEfficiency);

    double fanEfficiency() const;
    bool setFanEfficiency(double fanEfficiency);

    double pressureRise() const;
    bool setPressureRise(double pressureRise);

    boost::optional<double> maximumFlowRate() const;
    bool setMaximumFlowRate(double maximumFlowRate);
    void resetMaximumFlowRate();
    void autosizeMaximumFlowRate();
    bool isMaximumFlowRateAutosized() const;

    double motorEfficiency() const;
    bool setMotorEfficiency(double motorEfficiency);

    double motorInAirstreamFraction() const;
    bool setMotorInAirstreamFraction(double motorInAirstreamFraction);

    std::string endUseSubcategory() const;
    bool setEndUseSubcategory(const std::string& endUseSubcategory);

   protected:
    using ImplType = detail::FanConstantVolume_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit FanConstantVolume(std::shared_ptr<detail::FanConstantVolume_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
