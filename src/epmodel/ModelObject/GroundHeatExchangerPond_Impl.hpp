/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GROUNDHEATEXCHANGERPOND_IMPL_HPP
#define EPMODEL_GROUNDHEATEXCHANGERPOND_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API GroundHeatExchangerPond_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~GroundHeatExchangerPond_Impl() override = default;

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
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
