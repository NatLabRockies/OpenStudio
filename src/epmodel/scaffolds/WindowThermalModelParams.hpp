/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_WINDOWTHERMALMODELPARAMS_HPP
#define EPMODEL_WINDOWTHERMALMODELPARAMS_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class WindowThermalModelParams_Impl;
  }

  class EPMODEL_API WindowThermalModelParams : public ModelObject
  {
   public:
    explicit WindowThermalModelParams(const Model& model);

    virtual ~WindowThermalModelParams() override = default;
    WindowThermalModelParams(const WindowThermalModelParams& other) = default;
    WindowThermalModelParams(WindowThermalModelParams&& other) = default;
    WindowThermalModelParams& operator=(const WindowThermalModelParams&) = default;
    WindowThermalModelParams& operator=(WindowThermalModelParams&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> standardValues();
    static std::vector<std::string> thermalModelValues();
    static std::vector<std::string> deflectionModelValues();

    // Schema Alignment Notes:
    // - API: Scalar accessors map directly to WindowThermalModel:Params fields from the EnergyPlus schema.
    // - Field Mapping: The Name field maps to WindowThermalModelParameters and is retained through ModelObject::nameString.
    // - TODO(parity): Add relationship helpers once non-scalar coverage is required without changing these scalar signatures.
    std::string standard() const;
    bool isStandardDefaulted() const;
    bool setStandard(const std::string& standard);
    void resetStandard();

    std::string thermalModel() const;
    bool isThermalModelDefaulted() const;
    bool setThermalModel(const std::string& thermalModel);
    void resetThermalModel();

    double sdScalar() const;
    bool isSdScalarDefaulted() const;
    bool setSdScalar(double sdScalar);
    void resetSdScalar();

    std::string deflectionModel() const;
    bool isDeflectionModelDefaulted() const;
    bool setDeflectionModel(const std::string& deflectionModel);
    void resetDeflectionModel();

    double vacuumPressureLimit() const;
    bool isVacuumPressureLimitDefaulted() const;
    bool setVacuumPressureLimit(double vacuumPressureLimit);
    void resetVacuumPressureLimit();

    double initialTemperature() const;
    bool isInitialTemperatureDefaulted() const;
    bool setInitialTemperature(double initialTemperature);
    void resetInitialTemperature();

    double initialPressure() const;
    bool isInitialPressureDefaulted() const;
    bool setInitialPressure(double initialPressure);
    void resetInitialPressure();

   protected:
    using ImplType = detail::WindowThermalModelParams_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit WindowThermalModelParams(std::shared_ptr<detail::WindowThermalModelParams_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
