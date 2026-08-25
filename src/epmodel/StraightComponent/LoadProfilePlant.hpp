/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_LOADPROFILEPLANT_HPP
#define EPMODEL_LOADPROFILEPLANT_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include "../utilities/idd/IddEnums.hpp"

#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class Node;
  class Schedule;

  namespace detail {
    class LoadProfilePlant_Impl;
  }

/** \brief A plant load-profile component.
 *
 * \par EnergyPlus object
 * \epobject{group-non-zone-equipment.html#loadprofileplant,LoadProfile:Plant}
 *
 * \par Important behavior
 * Load and flow-fraction schedules, scalar fields, and demand-side placement map directly to LoadProfile:Plant. The default load schedule uses ScheduleCompact.
 *
 * \par OpenStudio Model API
 * The corresponding OpenStudio Model type is <code>openstudio::model::LoadProfilePlant</code>.
 *
 * \par Known limitations
 * ScheduleRuleset is not available for the default seeded schedule; EPModel also exposes some EnergyPlus default/reset helpers not present in Model.
 */
  class EPMODEL_API LoadProfilePlant : public StraightComponent
  {
   public:
    explicit LoadProfilePlant(const Model& model);
    explicit LoadProfilePlant(const Model& model, Schedule& loadSchedule, Schedule& flowRateFractionSchedule);

    virtual ~LoadProfilePlant() override = default;
    LoadProfilePlant(const LoadProfilePlant& other) = default;
    LoadProfilePlant(LoadProfilePlant&& other) = default;
    LoadProfilePlant& operator=(const LoadProfilePlant&) = default;
    LoadProfilePlant& operator=(LoadProfilePlant&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> plantLoopFluidTypeValues();

    Schedule loadSchedule() const;
    bool setLoadSchedule(Schedule& schedule);

    double peakFlowRate() const;
    bool setPeakFlowRate(double peakFlowRate);

    Schedule flowRateFractionSchedule() const;
    bool setFlowRateFractionSchedule(Schedule& schedule);

    std::string plantLoopFluidType() const;
    bool setPlantLoopFluidType(const std::string& plantLoopFluidType);
    bool isPlantLoopFluidTypeDefaulted() const;
    void resetPlantLoopFluidType();

    double degreeofSubCooling() const;
    bool setDegreeofSubCooling(double degreeofSubCooling);
    bool isDegreeofSubCoolingDefaulted() const;
    void resetDegreeofSubCooling();

    double degreeofLoopSubCooling() const;
    bool setDegreeofLoopSubCooling(double degreeofLoopSubCooling);
    bool isDegreeofLoopSubCoolingDefaulted() const;
    void resetDegreeofLoopSubCooling();

    bool addToNode(Node& node);

   protected:
    using ImplType = detail::LoadProfilePlant_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit LoadProfilePlant(std::shared_ptr<detail::LoadProfilePlant_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
