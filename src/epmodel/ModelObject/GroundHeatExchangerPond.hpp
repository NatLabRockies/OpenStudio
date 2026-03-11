/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GROUNDHEATEXCHANGERPOND_HPP
#define EPMODEL_GROUNDHEATEXCHANGERPOND_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class GroundHeatExchangerPond_Impl;
}

class EPMODEL_API GroundHeatExchangerPond : public ModelObject
{
 public:
  explicit GroundHeatExchangerPond(const Model& model);

  virtual ~GroundHeatExchangerPond() override = default;
  GroundHeatExchangerPond(const GroundHeatExchangerPond& other) = default;
  GroundHeatExchangerPond(GroundHeatExchangerPond&& other) = default;
  GroundHeatExchangerPond& operator=(const GroundHeatExchangerPond&) = default;
  GroundHeatExchangerPond& operator=(GroundHeatExchangerPond&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived class/accessor naming.
  // - Field Mapping: Scalar APIs map directly to GroundHeatExchanger:Pond numeric fields.
  // - Field Mapping: Fluid Inlet Node Name and Fluid Outlet Node Name are relationship-like node link fields and are excluded.
  // - TODO(parity): Add relationship APIs incrementally after scalar saturation.
  double pondDepth() const;
  double pondArea() const;
  double hydronicTubingInsideDiameter() const;
  double hydronicTubingOutsideDiameter() const;
  double hydronicTubingThermalConductivity() const;
  double groundThermalConductivity() const;
  int numberofTubingCircuits() const;
  double lengthofEachTubingCircuit() const;

  bool setPondDepth(double pondDepth);
  bool setPondArea(double pondArea);
  bool setHydronicTubingInsideDiameter(double hydronicTubingInsideDiameter);
  bool setHydronicTubingOutsideDiameter(double hydronicTubingOutsideDiameter);
  bool setHydronicTubingThermalConductivity(double hydronicTubingThermalConductivity);
  bool setGroundThermalConductivity(double groundThermalConductivity);
  bool setNumberofTubingCircuits(int numberofTubingCircuits);
  bool setLengthofEachTubingCircuit(double lengthofEachTubingCircuit);

 protected:
  using ImplType = detail::GroundHeatExchangerPond_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit GroundHeatExchangerPond(std::shared_ptr<detail::GroundHeatExchangerPond_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
