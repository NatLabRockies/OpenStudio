/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ROOMAIRMODELTYPE_HPP
#define EPMODEL_ROOMAIRMODELTYPE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class RoomAirModelType_Impl;
}

class EPMODEL_API RoomAirModelType : public ModelObject
{
 public:
  explicit RoomAirModelType(const Model& model);

  virtual ~RoomAirModelType() override = default;
  RoomAirModelType(const RoomAirModelType& other) = default;
  RoomAirModelType(RoomAirModelType&& other) = default;
  RoomAirModelType& operator=(const RoomAirModelType&) = default;
  RoomAirModelType& operator=(RoomAirModelType&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> roomAirModelingTypeValues();
  static std::vector<std::string> airTemperatureCouplingStrategyValues();

  // Schema Alignment Notes:
  // - API: This no-counterpart epmodel type uses IDD-derived class/accessor naming.
  // - Field Mapping: roomAirModelingType and airTemperatureCouplingStrategy map directly to EnergyPlus
  //   RoomAirModelType / Room-Air Modeling Type and Air Temperature Coupling Strategy.
  // - Field Mapping: Zone Name is an object-list relationship field and is intentionally excluded from
  //   scalar accessors in this scaffold pass.
  // - Field Mapping: Name is intentionally omitted here and remains provided by ModelObject base name APIs.
  // - TODO(parity): Add typed relationship API for Zone Name when relationship accessors are scaffolded.
  std::string roomAirModelingType() const;
  bool isRoomAirModelingTypeDefaulted() const;
  std::string airTemperatureCouplingStrategy() const;
  bool isAirTemperatureCouplingStrategyDefaulted() const;

  bool setRoomAirModelingType(const std::string& roomAirModelingType);
  void resetRoomAirModelingType();
  bool setAirTemperatureCouplingStrategy(const std::string& airTemperatureCouplingStrategy);
  void resetAirTemperatureCouplingStrategy();

 protected:
  using ImplType = detail::RoomAirModelType_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit RoomAirModelType(std::shared_ptr<detail::RoomAirModelType_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
