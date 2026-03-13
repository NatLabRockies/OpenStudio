/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ROOMAIRMODELTYPE_IMPL_HPP
#define EPMODEL_ROOMAIRMODELTYPE_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {
  namespace detail {

    class EPMODEL_API RoomAirModelType_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~RoomAirModelType_Impl() override = default;

      std::string roomAirModelingType() const;
      bool isRoomAirModelingTypeDefaulted() const;
      bool setRoomAirModelingType(const std::string& roomAirModelingType);
      void resetRoomAirModelingType();

      std::string airTemperatureCouplingStrategy() const;
      bool isAirTemperatureCouplingStrategyDefaulted() const;
      bool setAirTemperatureCouplingStrategy(const std::string& airTemperatureCouplingStrategy);
      void resetAirTemperatureCouplingStrategy();

      std::vector<std::string> roomAirModelingTypeValues() const;
      std::vector<std::string> airTemperatureCouplingStrategyValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
