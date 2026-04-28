/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_LOADPROFILEPLANT_IMPL_HPP
#define EPMODEL_LOADPROFILEPLANT_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

#include <boost/optional.hpp>

#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Node;
  class Schedule;

  namespace detail {

    class EPMODEL_API LoadProfilePlant_Impl : public StraightComponent_Impl
    {
     public:
      using StraightComponent_Impl::StraightComponent_Impl;
      virtual ~LoadProfilePlant_Impl() override = default;

      unsigned inletPort() const override;
      unsigned outletPort() const override;
      bool addToNode(Node& node) override;

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

      std::vector<std::string> plantLoopFluidTypeValues() const;

      double degreeofSubCooling() const;
      bool setDegreeofSubCooling(double degreeofSubCooling);
      bool isDegreeofSubCoolingDefaulted() const;
      void resetDegreeofSubCooling();

      double degreeofLoopSubCooling() const;
      bool setDegreeofLoopSubCooling(double degreeofLoopSubCooling);
      bool isDegreeofLoopSubCoolingDefaulted() const;
      void resetDegreeofLoopSubCooling();

     private:
      boost::optional<Schedule> optionalLoadSchedule() const;
      boost::optional<Schedule> optionalFlowRateFractionSchedule() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
