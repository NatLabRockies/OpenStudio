/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SPACEINFILTRATIONEFFECTIVELEAKAGEAREA_IMPL_HPP
#define EPMODEL_SPACEINFILTRATIONEFFECTIVELEAKAGEAREA_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <boost/optional.hpp>
#include <string>

namespace openstudio {
namespace epmodel {

  class Model_Impl;

  namespace detail {

    class EPMODEL_API SpaceInfiltrationEffectiveLeakageArea_Impl : public ModelObject_Impl
    {
     public:
      SpaceInfiltrationEffectiveLeakageArea_Impl(const IdfObject& object, Model_Impl* model, bool keepHandle);
      SpaceInfiltrationEffectiveLeakageArea_Impl(const openstudio::detail::WorkspaceObject_Impl& other, Model_Impl* model, bool keepHandle);
      SpaceInfiltrationEffectiveLeakageArea_Impl(const SpaceInfiltrationEffectiveLeakageArea_Impl& other, Model_Impl* model, bool keepHandle);
      virtual ~SpaceInfiltrationEffectiveLeakageArea_Impl() override = default;

      double effectiveAirLeakageArea() const;
      double stackCoefficient() const;
      double windCoefficient() const;

      bool setEffectiveAirLeakageArea(double effectiveAirLeakageArea);
      bool setStackCoefficient(double stackCoefficient);
      bool setWindCoefficient(double windCoefficient);

     private:
      REGISTER_LOGGER("openstudio.epmodel.SpaceInfiltrationEffectiveLeakageArea");
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
