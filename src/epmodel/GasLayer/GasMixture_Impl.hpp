/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GASMIXTURE_IMPL_HPP
#define EPMODEL_GASMIXTURE_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <string>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API GasMixture_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~GasMixture_Impl() override = default;

      double thickness() const;
      bool setThickness(double thickness);

      int numberofGasesinMixture() const;
      bool setNumberofGasesinMixture(int numberofGasesinMixture);
      unsigned numGases() const;

      std::string gas1Type() const;
      double gas1Fraction() const;
      bool setGas1Type(const std::string& gas1Type);
      void resetGas1Type();
      bool setGas1Fraction(double gas1Fraction);
      void resetGas1Fraction();

      std::string gas2Type() const;
      double gas2Fraction() const;
      bool setGas2Type(const std::string& gas2Type);
      void resetGas2Type();
      bool setGas2Fraction(double gas2Fraction);
      void resetGas2Fraction();

      std::string gas3Type() const;
      boost::optional<double> gas3Fraction() const;
      bool setGas3Type(const std::string& gas3Type);
      void resetGas3Type();
      bool setGas3Fraction(double gas3Fraction);
      void resetGas3Fraction();

      std::string gas4Type() const;
      boost::optional<double> gas4Fraction() const;
      bool setGas4Type(const std::string& gas4Type);
      void resetGas4Type();
      bool setGas4Fraction(double gas4Fraction);
      void resetGas4Fraction();

     private:
      // Intentionally no additional helper state.
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_GASMIXTURE_IMPL_HPP
