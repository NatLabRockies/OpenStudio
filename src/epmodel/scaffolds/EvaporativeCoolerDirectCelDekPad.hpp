/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_EVAPORATIVECOOLERDIRECTCELDEKPAD_HPP
#define EPMODEL_EVAPORATIVECOOLERDIRECTCELDEKPAD_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <boost/optional.hpp>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class EvaporativeCoolerDirectCelDekPad_Impl;
}

class EPMODEL_API EvaporativeCoolerDirectCelDekPad : public ModelObject
{
 public:
  explicit EvaporativeCoolerDirectCelDekPad(const Model& model);

  virtual ~EvaporativeCoolerDirectCelDekPad() override = default;
  EvaporativeCoolerDirectCelDekPad(const EvaporativeCoolerDirectCelDekPad& other) = default;
  EvaporativeCoolerDirectCelDekPad(EvaporativeCoolerDirectCelDekPad&& other) = default;
  EvaporativeCoolerDirectCelDekPad& operator=(const EvaporativeCoolerDirectCelDekPad&) = default;
  EvaporativeCoolerDirectCelDekPad& operator=(EvaporativeCoolerDirectCelDekPad&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: This no-counterpart epmodel type uses IDD-derived class/accessor naming.
  // - Field Mapping: directPadArea/directPadDepth/recirculatingWaterPumpPowerConsumption/controlType map directly to
  //   EvaporativeCooler:Direct:CelDekPad fields.
  // - Field Mapping: Availability Schedule Name, Air Inlet Node Name, Air Outlet Node Name, and Water Supply Storage Tank Name are
  //   relationship-like fields and are excluded from scalar accessors.
  // - TODO(parity): Add relationship APIs incrementally after scalar saturation.
  boost::optional<double> directPadArea() const;
  bool isDirectPadAreaAutosized() const;
  bool setDirectPadArea(double directPadArea);
  void resetDirectPadArea();
  void autosizeDirectPadArea();

  boost::optional<double> directPadDepth() const;
  bool isDirectPadDepthAutosized() const;
  bool setDirectPadDepth(double directPadDepth);
  void resetDirectPadDepth();
  void autosizeDirectPadDepth();

  double recirculatingWaterPumpPowerConsumption() const;
  bool setRecirculatingWaterPumpPowerConsumption(double recirculatingWaterPumpPowerConsumption);

  boost::optional<std::string> controlType() const;
  bool setControlType(const std::string& controlType);
  void resetControlType();

 protected:
  using ImplType = detail::EvaporativeCoolerDirectCelDekPad_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit EvaporativeCoolerDirectCelDekPad(std::shared_ptr<detail::EvaporativeCoolerDirectCelDekPad_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
