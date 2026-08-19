/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AVAILABILITYMANAGEROPTIMUMSTART_HPP
#define EPMODEL_AVAILABILITYMANAGEROPTIMUMSTART_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class AvailabilityManagerOptimumStart_Impl;
  }

  /** \brief Determines when a loop should start to reach its occupied conditions.
   *
   * \par EnergyPlus object
   * \epobject{group-system-availability-managers.html#availabilitymanageroptimumstart,AvailabilityManager:OptimumStart}
   *
   * \par Important behavior
   * A newly constructed manager initializes control type to
   * <code>MaximumofZoneList</code>, the control algorithm to
   * <code>AdaptiveTemperatureGradient</code>, maximum start time to 6.0 hours,
   * the cooling and heating gradients to 3.0 and 3.0, the initial gradients to
   * 2.0 and 2.0, constant start time to 2.0 hours, and the previous-day count
   * to 3.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::AvailabilityManagerOptimumStart</code>.
   *
   * - <b>Not yet available:</b> <code>loop()</code>,
   *   <code>applicabilitySchedule()</code>,
   *   <code>setApplicabilitySchedule(...)</code>,
   *   <code>controlZone()</code>, <code>setControlZone(...)</code>, and
   *   <code>resetControlZone()</code>.
   *
   * \par Known limitations
   * The EPModel wrapper currently exposes scalar fields only. It cannot be
   * passed to typed loop-assignment APIs or fully configured through typed
   * applicability-schedule and control-zone relationships.
   */
  class EPMODEL_API AvailabilityManagerOptimumStart : public ModelObject
  {
   public:
    explicit AvailabilityManagerOptimumStart(const Model& model);

    virtual ~AvailabilityManagerOptimumStart() override = default;
    AvailabilityManagerOptimumStart(const AvailabilityManagerOptimumStart& other) = default;
    AvailabilityManagerOptimumStart(AvailabilityManagerOptimumStart&& other) = default;
    AvailabilityManagerOptimumStart& operator=(const AvailabilityManagerOptimumStart&) = default;
    AvailabilityManagerOptimumStart& operator=(AvailabilityManagerOptimumStart&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> controlTypeValues();
    static std::vector<std::string> controlAlgorithmValues();

    std::string controlType() const;
    bool setControlType(const std::string& controlType);

    double maximumValueforOptimumStartTime() const;
    bool setMaximumValueforOptimumStartTime(double maximumValueforOptimumStartTime);

    std::string controlAlgorithm() const;
    bool setControlAlgorithm(const std::string& controlAlgorithm);

    double constantTemperatureGradientduringCooling() const;
    bool setConstantTemperatureGradientduringCooling(double constantTemperatureGradientduringCooling);

    double constantTemperatureGradientduringHeating() const;
    bool setConstantTemperatureGradientduringHeating(double constantTemperatureGradientduringHeating);

    double initialTemperatureGradientduringCooling() const;
    bool setInitialTemperatureGradientduringCooling(double initialTemperatureGradientduringCooling);

    double initialTemperatureGradientduringHeating() const;
    bool setInitialTemperatureGradientduringHeating(double initialTemperatureGradientduringHeating);

    double constantStartTime() const;
    bool setConstantStartTime(double constantStartTime);

    int numberofPreviousDays() const;
    bool setNumberofPreviousDays(int numberofPreviousDays);

   protected:
    using ImplType = detail::AvailabilityManagerOptimumStart_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AvailabilityManagerOptimumStart(std::shared_ptr<detail::AvailabilityManagerOptimumStart_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
