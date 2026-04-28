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
      bool setPondDepth(double pondDepth);

      double pondArea() const;
      bool setPondArea(double pondArea);

      double hydronicTubingInsideDiameter() const;
      bool setHydronicTubingInsideDiameter(double hydronicTubingInsideDiameter);

      double hydronicTubingOutsideDiameter() const;
      bool setHydronicTubingOutsideDiameter(double hydronicTubingOutsideDiameter);

      double hydronicTubingThermalConductivity() const;
      bool setHydronicTubingThermalConductivity(double hydronicTubingThermalConductivity);

      double groundThermalConductivity() const;
      bool setGroundThermalConductivity(double groundThermalConductivity);

      int numberofTubingCircuits() const;
      bool setNumberofTubingCircuits(int numberofTubingCircuits);

      double lengthofEachTubingCircuit() const;
      bool setLengthofEachTubingCircuit(double lengthofEachTubingCircuit);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
