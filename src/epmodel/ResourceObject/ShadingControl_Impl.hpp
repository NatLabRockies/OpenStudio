/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SHADINGCONTROL_IMPL_HPP
#define EPMODEL_SHADINGCONTROL_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <boost/optional.hpp>
#include <string>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ShadingControl_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ShadingControl_Impl() override = default;

      std::string shadingType() const;
      bool setShadingType(const std::string& shadingType);

      int shadingControlSequenceNumber() const;
      bool setShadingControlSequenceNumber(int shadingControlSequenceNumber);
      bool isShadingControlSequenceNumberDefaulted() const;
      void resetShadingControlSequenceNumber();

      std::string shadingControlType() const;
      bool setShadingControlType(const std::string& shadingControlType);
      bool isShadingControlTypeDefaulted() const;
      void resetShadingControlType();

      boost::optional<double> setpoint() const;
      bool setSetpoint(double setpoint);
      bool isSetpointDefaulted() const;
      void resetSetpoint();

      bool glareControlIsActive() const;
      bool setGlareControlIsActive(bool glareControlIsActive);
      void resetGlareControlIsActive();

      std::string typeofSlatAngleControlforBlinds() const;
      bool setTypeofSlatAngleControlforBlinds(const std::string& typeofSlatAngleControlforBlinds);
      bool isTypeofSlatAngleControlforBlindsDefaulted() const;
      void resetTypeofSlatAngleControlforBlinds();

      boost::optional<double> setpoint2() const;
      bool setSetpoint2(double setpoint2);

      std::string multipleSurfaceControlType() const;
      bool setMultipleSurfaceControlType(const std::string& multipleSurfaceControlType);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
