/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PLANTCOMPONENTUSERDEFINED_IMPL_HPP
#define EPMODEL_PLANTCOMPONENTUSERDEFINED_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

#include <boost/optional.hpp>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API PlantComponentUserDefined_Impl : public StraightComponent_Impl
    {
     public:
      using StraightComponent_Impl::StraightComponent_Impl;
      virtual ~PlantComponentUserDefined_Impl() override = default;

      unsigned inletPort() const override;
      unsigned outletPort() const override;

      int numberOfPlantLoopConnections() const;
      bool setNumberOfPlantLoopConnections(int numberOfPlantLoopConnections);

      std::vector<std::string> plantConnection1LoadingModeValues() const;
      std::vector<std::string> plantConnection1LoopFlowRequestModeValues() const;
      std::vector<std::string> plantConnection2LoadingModeValues() const;
      std::vector<std::string> plantConnection2LoopFlowRequestModeValues() const;
      std::vector<std::string> plantConnection3LoadingModeValues() const;
      std::vector<std::string> plantConnection3LoopFlowRequestModeValues() const;
      std::vector<std::string> plantConnection4LoadingModeValues() const;
      std::vector<std::string> plantConnection4LoopFlowRequestModeValues() const;

      std::string plantConnection1LoadingMode() const;
      bool setPlantConnection1LoadingMode(const std::string& plantConnection1LoadingMode);

      std::string plantConnection1LoopFlowRequestMode() const;
      bool setPlantConnection1LoopFlowRequestMode(const std::string& plantConnection1LoopFlowRequestMode);

      boost::optional<std::string> plantConnection2LoadingMode() const;
      bool setPlantConnection2LoadingMode(const std::string& plantConnection2LoadingMode);
      void resetPlantConnection2LoadingMode();

      boost::optional<std::string> plantConnection2LoopFlowRequestMode() const;
      bool setPlantConnection2LoopFlowRequestMode(const std::string& plantConnection2LoopFlowRequestMode);
      void resetPlantConnection2LoopFlowRequestMode();

      boost::optional<std::string> plantConnection3LoadingMode() const;
      bool setPlantConnection3LoadingMode(const std::string& plantConnection3LoadingMode);
      void resetPlantConnection3LoadingMode();

      boost::optional<std::string> plantConnection3LoopFlowRequestMode() const;
      bool setPlantConnection3LoopFlowRequestMode(const std::string& plantConnection3LoopFlowRequestMode);
      void resetPlantConnection3LoopFlowRequestMode();

      boost::optional<std::string> plantConnection4LoadingMode() const;
      bool setPlantConnection4LoadingMode(const std::string& plantConnection4LoadingMode);
      void resetPlantConnection4LoadingMode();

      boost::optional<std::string> plantConnection4LoopFlowRequestMode() const;
      bool setPlantConnection4LoopFlowRequestMode(const std::string& plantConnection4LoopFlowRequestMode);
      void resetPlantConnection4LoopFlowRequestMode();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
