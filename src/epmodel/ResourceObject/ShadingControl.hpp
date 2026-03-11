/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SHADINGCONTROL_HPP
#define EPMODEL_SHADINGCONTROL_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <boost/optional.hpp>
#include <memory>
#include <string>
#include <vector>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ShadingControl_Impl;
  }

  class EPMODEL_API ShadingControl : public ModelObject
  {
   public:
    explicit ShadingControl(const Model& model);

    virtual ~ShadingControl() override = default;
    ShadingControl(const ShadingControl& other) = default;
    ShadingControl(ShadingControl&& other) = default;
    ShadingControl& operator=(const ShadingControl&) = default;
    ShadingControl& operator=(ShadingControl&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> shadingTypeValues();
    static std::vector<std::string> shadingControlTypeValues();
    static std::vector<std::string> typeofSlatAngleControlforBlindsValues();
    static std::vector<std::string> multipleSurfaceControlTypeValues();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model ShadingControl scalar accessor names/signatures while living under the ResourceObject bucket.
    // - Field Mapping: Each scalar we expose maps directly to a WindowShadingControl field (ShadingType, ShadingControlType,
    //   Shading Control Sequence Number, Setpoint, Glare Control Is Active, Type of Slat Angle Control for Blinds, Setpoint 2,
    //   and Multiple Surface Control Type) via WindowShadingControlFields enum values.
    // - Field Mapping: Relationship-like fields (Zone, Construction with Shading, Shading Device Material, Schedule,
    //   Slat Angle Schedule, Daylighting Control, and extensible Fenestration Surface names) are intentionally excluded from
    //   scalar-only coverage.
    // - TODO(parity): Add the omitted relationship APIs once relationship handling is bootstrapped for this bucket.

    std::string shadingType() const;
    bool setShadingType(const std::string& shadingType);

    int shadingControlSequenceNumber() const;
    bool setShadingControlSequenceNumber(int shadingControlSequenceNumber);
    bool isShadingControlSequenceNumberDefaulted() const;
    void resetShadingControlSequenceNumber();

    std::string shadingControlType() const;
    bool isShadingControlTypeDefaulted() const;
    bool setShadingControlType(const std::string& shadingControlType);
    void resetShadingControlType();

    boost::optional<double> setpoint() const;
    bool setSetpoint(double setpoint);
    void resetSetpoint();
    bool isSetpointDefaulted() const;

    bool glareControlIsActive() const;
    bool setGlareControlIsActive(bool glareControlIsActive);
    void resetGlareControlIsActive();

    std::string typeofSlatAngleControlforBlinds() const;
    bool isTypeofSlatAngleControlforBlindsDefaulted() const;
    bool setTypeofSlatAngleControlforBlinds(const std::string& typeofSlatAngleControlforBlinds);
    void resetTypeofSlatAngleControlforBlinds();

    boost::optional<double> setpoint2() const;
    bool setSetpoint2(double setpoint2);

    std::string multipleSurfaceControlType() const;
    bool setMultipleSurfaceControlType(const std::string& multipleSurfaceControlType);

   protected:
    using ImplType = detail::ShadingControl_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ShadingControl(std::shared_ptr<detail::ShadingControl_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
