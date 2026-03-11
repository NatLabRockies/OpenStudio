/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ROOMAIRSETTINGSONENODEDISPLACEMENTVENTILATION_HPP
#define EPMODEL_ROOMAIRSETTINGSONENODEDISPLACEMENTVENTILATION_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class RoomAirSettingsOneNodeDisplacementVentilation_Impl;
}

class EPMODEL_API RoomAirSettingsOneNodeDisplacementVentilation : public ModelObject
{
 public:
  explicit RoomAirSettingsOneNodeDisplacementVentilation(const Model& model);

  virtual ~RoomAirSettingsOneNodeDisplacementVentilation() override = default;
  RoomAirSettingsOneNodeDisplacementVentilation(const RoomAirSettingsOneNodeDisplacementVentilation& other) = default;
  RoomAirSettingsOneNodeDisplacementVentilation(RoomAirSettingsOneNodeDisplacementVentilation&& other) = default;
  RoomAirSettingsOneNodeDisplacementVentilation& operator=(const RoomAirSettingsOneNodeDisplacementVentilation&) = default;
  RoomAirSettingsOneNodeDisplacementVentilation& operator=(RoomAirSettingsOneNodeDisplacementVentilation&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: This no-counterpart epmodel type uses IDD-derived class and accessor naming.
  // - Field Mapping: fractionofConvectiveInternalLoadsAddedtoFloorAir maps directly to EnergyPlus
  //   RoomAirSettings:OneNodeDisplacementVentilation / Fraction of Convective Internal Loads Added to Floor Air.
  // - Field Mapping: fractionofInfiltrationInternalLoadsAddedtoFloorAir maps directly to EnergyPlus
  //   RoomAirSettings:OneNodeDisplacementVentilation / Fraction of Infiltration Internal Loads Added to Floor Air.
  // - Field Mapping: Zone Name is an object-list relationship field and intentionally excluded from scalar accessors
  //   in this scaffold pass.
  // - Field Mapping: Name remains available via ModelObject base name APIs.
  // - TODO(parity): Add typed relationship APIs for excluded fields after scalar saturation.
  boost::optional<double> fractionofConvectiveInternalLoadsAddedtoFloorAir() const;
  boost::optional<double> fractionofInfiltrationInternalLoadsAddedtoFloorAir() const;

  bool setFractionofConvectiveInternalLoadsAddedtoFloorAir(double fractionofConvectiveInternalLoadsAddedtoFloorAir);
  bool setFractionofInfiltrationInternalLoadsAddedtoFloorAir(double fractionofInfiltrationInternalLoadsAddedtoFloorAir);

  void resetFractionofConvectiveInternalLoadsAddedtoFloorAir();
  void resetFractionofInfiltrationInternalLoadsAddedtoFloorAir();

 protected:
  using ImplType = detail::RoomAirSettingsOneNodeDisplacementVentilation_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit RoomAirSettingsOneNodeDisplacementVentilation(std::shared_ptr<detail::RoomAirSettingsOneNodeDisplacementVentilation_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
