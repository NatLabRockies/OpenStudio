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

  /** \brief Specifies when and how a window shading device is controlled.
   *
   * \par EnergyPlus object
   * \epobject{group-thermal-zone-description-geometry.html#windowpropertyshadingcontrol,WindowShadingControl}.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::ShadingControl</code>. EPModel exposes the
   * EnergyPlus scalar fields and the additional
   * <code>shadingControlSequenceNumber()</code> accessors. Model relationship
   * methods for the zone, construction, shading material, schedules,
   * daylighting control, and controlled subsurfaces are not available.
   *
   * \par Known limitations
   * This wrapper cannot assign the shading-control relationships or the
   * extensible fenestration-surface list.
   */
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
