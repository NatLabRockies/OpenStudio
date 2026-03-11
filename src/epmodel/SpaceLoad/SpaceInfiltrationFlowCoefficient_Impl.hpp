/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SPACEINFILTRATIONFLOWCOEFFICIENT_IMPL_HPP
#define EPMODEL_SPACEINFILTRATIONFLOWCOEFFICIENT_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <boost/optional.hpp>

namespace openstudio {
namespace epmodel {

  class Model_Impl;

  namespace detail {

    class EPMODEL_API SpaceInfiltrationFlowCoefficient_Impl : public ModelObject_Impl
    {
     public:
      SpaceInfiltrationFlowCoefficient_Impl(const IdfObject& object, Model_Impl* model, bool keepHandle);
      SpaceInfiltrationFlowCoefficient_Impl(const openstudio::detail::WorkspaceObject_Impl& other, Model_Impl* model, bool keepHandle);
      SpaceInfiltrationFlowCoefficient_Impl(const SpaceInfiltrationFlowCoefficient_Impl& other, Model_Impl* model, bool keepHandle);
      virtual ~SpaceInfiltrationFlowCoefficient_Impl() override = default;

      double flowCoefficient() const;
      double stackCoefficient() const;
      double pressureExponent() const;
      bool isPressureExponentDefaulted() const;
      double windCoefficient() const;
      double shelterFactor() const;

      bool setFlowCoefficient(double flowCoefficient);
      bool setStackCoefficient(double stackCoefficient);
      bool setPressureExponent(double pressureExponent);
      void resetPressureExponent();
      bool setWindCoefficient(double windCoefficient);
      bool setShelterFactor(double shelterFactor);

     private:
      REGISTER_LOGGER("openstudio.epmodel.SpaceInfiltrationFlowCoefficient");
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
