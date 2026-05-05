/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GENERATORPVWATTS_HPP
#define EPMODEL_GENERATORPVWATTS_HPP

#include "EPModelAPI.hpp"
#include "ModelObject/ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class GeneratorPVWatts_Impl;
  }

  class EPMODEL_API GeneratorPVWatts : public ModelObject
  {
   public:
    explicit GeneratorPVWatts(const Model& model);

    virtual ~GeneratorPVWatts() override = default;
    GeneratorPVWatts(const GeneratorPVWatts& other) = default;
    GeneratorPVWatts(GeneratorPVWatts&& other) = default;
    GeneratorPVWatts& operator=(const GeneratorPVWatts&) = default;
    GeneratorPVWatts& operator=(GeneratorPVWatts&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> pvWattsVersionValues();
    static std::vector<std::string> moduleTypeValues();
    static std::vector<std::string> arrayTypeValues();

    // Schema Alignment Notes:
    // - API: Preserves openstudio::model::GeneratorPVWatts scalar accessor names/signatures.
    // - Field Mapping: Preserved scalar APIs map to EnergyPlus Generator:PVWatts scalar fields.
    // - Field Mapping: API uses Tilt/Azimuth scalar accessors and excludes SurfaceName relationship API in this pass.
    // - ForwardTranslator evidence: ForwardTranslateGeneratorPVWatts writes Array Geometry Type as TiltAzimuth when
    //   surface is absent and writes Tilt Angle/Azimuth Angle from these preserved scalar getters.
    // - TODO(parity): Add preserved relationship API for surface-driven geometry in a dedicated relationship pass.
    std::string pvWattsVersion() const;

    double dcSystemCapacity() const;
    bool setDCSystemCapacity(double dcSystemCapacity);

    std::string moduleType() const;
    bool isModuleTypeDefaulted() const;
    bool setModuleType(const std::string& moduleType);
    void resetModuleType();

    std::string arrayType() const;
    bool isArrayTypeDefaulted() const;
    bool setArrayType(const std::string& arrayType);
    void resetArrayType();

    double systemLosses() const;
    bool isSystemLossesDefaulted() const;
    bool setSystemLosses(double systemLosses);
    void resetSystemLosses();

    double tiltAngle() const;
    bool isTiltAngleDefaulted() const;
    bool setTiltAngle(double tiltAngle);
    void resetTiltAngle();

    double azimuthAngle() const;
    bool isAzimuthAngleDefaulted() const;
    bool setAzimuthAngle(double azimuthAngle);
    void resetAzimuthAngle();

    double groundCoverageRatio() const;
    bool isGroundCoverageRatioDefaulted() const;
    bool setGroundCoverageRatio(double groundCoverageRatio);
    void resetGroundCoverageRatio();

   protected:
    using ImplType = detail::GeneratorPVWatts_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit GeneratorPVWatts(std::shared_ptr<detail::GeneratorPVWatts_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
