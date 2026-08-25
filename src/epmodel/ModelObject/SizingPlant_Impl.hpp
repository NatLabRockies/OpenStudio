/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SIZINGPLANT_IMPL_HPP
#define EPMODEL_SIZINGPLANT_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <boost/optional.hpp>

namespace openstudio {
namespace epmodel {

  class PlantLoop;
  class SizingPlant;

  namespace detail {

    class EPMODEL_API SizingPlant_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~SizingPlant_Impl() override = default;

      openstudio::epmodel::PlantLoop plantLoop() const;

      std::string loopType() const;
      bool setLoopType(const std::string& loopType);

      double designLoopExitTemperature() const;
      bool setDesignLoopExitTemperature(double designLoopExitTemperature);

      double loopDesignTemperatureDifference() const;
      bool setLoopDesignTemperatureDifference(double loopDesignTemperatureDifference);

      std::string sizingOption() const;
      bool setSizingOption(const std::string& sizingOption);

      int zoneTimestepsinAveragingWindow() const;
      bool setZoneTimestepsinAveragingWindow(int zoneTimestepsinAveragingWindow);

      std::string coincidentSizingFactorMode() const;
      bool setCoincidentSizingFactorMode(const std::string& coincidentSizingFactorMode);
      bool setPlantLoop(const openstudio::epmodel::PlantLoop& plantLoop);

     private:
      friend class ::openstudio::epmodel::SizingPlant;

      boost::optional<openstudio::epmodel::PlantLoop> optionalPlantLoop() const;
      bool setPlantLoopPointer(const openstudio::epmodel::PlantLoop& plantLoop);
      void doCanonicalize(LoadContext& context) override;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
