/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SURFACEPROPERTYCONVECTIONCOEFFICIENTSMULTIPLESURFACE_IMPL_HPP
#define EPMODEL_SURFACEPROPERTYCONVECTIONCOEFFICIENTSMULTIPLESURFACE_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API SurfacePropertyConvectionCoefficientsMultipleSurface_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~SurfacePropertyConvectionCoefficientsMultipleSurface_Impl() override = default;

      boost::optional<std::string> surfaceType() const;
      bool setSurfaceType(const std::string& surfaceType);
      void resetSurfaceType();
      std::vector<std::string> surfaceTypeValues() const;

      boost::optional<std::string> convectionCoefficient1Location() const;
      bool setConvectionCoefficient1Location(const std::string& convectionCoefficient1Location);
      void resetConvectionCoefficient1Location();
      std::vector<std::string> convectionCoefficient1LocationValues() const;

      boost::optional<std::string> convectionCoefficient1Type() const;
      bool setConvectionCoefficient1Type(const std::string& convectionCoefficient1Type);
      void resetConvectionCoefficient1Type();
      std::vector<std::string> convectionCoefficient1TypeValues() const;

      boost::optional<double> convectionCoefficient1() const;
      bool setConvectionCoefficient1(double convectionCoefficient1);
      void resetConvectionCoefficient1();

      boost::optional<std::string> convectionCoefficient2Location() const;
      bool setConvectionCoefficient2Location(const std::string& convectionCoefficient2Location);
      void resetConvectionCoefficient2Location();
      std::vector<std::string> convectionCoefficient2LocationValues() const;

      boost::optional<std::string> convectionCoefficient2Type() const;
      bool setConvectionCoefficient2Type(const std::string& convectionCoefficient2Type);
      void resetConvectionCoefficient2Type();
      std::vector<std::string> convectionCoefficient2TypeValues() const;

      boost::optional<double> convectionCoefficient2() const;
      bool setConvectionCoefficient2(double convectionCoefficient2);
      void resetConvectionCoefficient2();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
