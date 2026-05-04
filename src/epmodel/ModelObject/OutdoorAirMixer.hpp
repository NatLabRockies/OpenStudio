/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_OUTDOORAIRMIXER_HPP
#define EPMODEL_OUTDOORAIRMIXER_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include "../utilities/idd/IddEnums.hpp"

namespace openstudio {
namespace epmodel {

class Model;
class Node;

namespace detail {
class OutdoorAirMixer_Impl;
}

class EPMODEL_API OutdoorAirMixer : public ModelObject
{
 public:
  explicit OutdoorAirMixer(const Model& model);

  virtual ~OutdoorAirMixer() override = default;
  OutdoorAirMixer(const OutdoorAirMixer& other) = default;
  OutdoorAirMixer(OutdoorAirMixer&& other) = default;
  OutdoorAirMixer& operator=(const OutdoorAirMixer&) = default;
  OutdoorAirMixer& operator=(OutdoorAirMixer&&) = default;

  static IddObjectType iddObjectType();

  boost::optional<Node> mixedAirNode() const;
  boost::optional<Node> outdoorAirNode() const;
  boost::optional<Node> reliefAirNode() const;
  boost::optional<Node> returnAirNode() const;

 protected:
  using ImplType = detail::OutdoorAirMixer_Impl;

  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;
  friend class Model;

  explicit OutdoorAirMixer(std::shared_ptr<detail::OutdoorAirMixer_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
