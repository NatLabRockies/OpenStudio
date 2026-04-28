/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_WINDOWTHERMALMODELPARAMS_IMPL_HPP
#define EPMODEL_WINDOWTHERMALMODELPARAMS_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API WindowThermalModelParams_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~WindowThermalModelParams_Impl() override = default;

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

      std::vector<std::string> standardValues() const;
      std::vector<std::string> thermalModelValues() const;
      std::vector<std::string> deflectionModelValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
