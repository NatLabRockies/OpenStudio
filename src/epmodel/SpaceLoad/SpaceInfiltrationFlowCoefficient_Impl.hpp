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
      bool setFlowCoefficient(double flowCoefficient);

      double stackCoefficient() const;
      bool setStackCoefficient(double stackCoefficient);

      double pressureExponent() const;
      bool isPressureExponentDefaulted() const;
      bool setPressureExponent(double pressureExponent);
      void resetPressureExponent();

      double windCoefficient() const;
      bool setWindCoefficient(double windCoefficient);

      double shelterFactor() const;
      bool setShelterFactor(double shelterFactor);

     private:
      REGISTER_LOGGER("openstudio.epmodel.SpaceInfiltrationFlowCoefficient");
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
