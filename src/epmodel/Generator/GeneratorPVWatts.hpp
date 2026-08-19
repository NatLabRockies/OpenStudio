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

  /** \brief Represents a PVWatts photovoltaic generator.
   *
   * \par EnergyPlus object
   * \epobject{group-electric-load-center-generator.html#generatorpvwatts,Generator:PVWatts}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::GeneratorPVWatts</code>.
   *
   * - <b>Changed:</b> Model constructors require a DC system capacity and may
   *   also accept a surface; the EPModel constructor accepts only the model.
   * - <b>Not yet available:</b> <code>surface()</code>,
   *   <code>setSurface(...)</code>, and <code>resetSurface()</code>.
   * - <b>Added:</b> <code>pvWattsVersionValues()</code>,
   *   <code>moduleTypeValues()</code>, and <code>arrayTypeValues()</code> expose
   *   the valid EnergyPlus choice keys.
   * - <b>Not yet available:</b> The Model Generator metadata methods
   *   <code>generatorObjectType()</code>, <code>ratedElectricPowerOutput()</code>,
   *   <code>availabilitySchedule()</code>,
   *   <code>ratedThermaltoElectricalPowerRatio()</code>, and
   *   <code>electricLoadCenterDistribution()</code>.
   *
   * \par Known limitations
   * Surface-based array geometry and generator placement metadata must be
   * handled through lower-level object references when needed.
   */
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
