/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_UTILITYCOSTVARIABLE_IMPL_HPP
#define EPMODEL_UTILITYCOSTVARIABLE_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API UtilityCostVariable_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~UtilityCostVariable_Impl() override = default;

      std::string variableType() const;
      bool isVariableTypeDefaulted() const;

      boost::optional<double> januaryValue() const;
      boost::optional<double> februaryValue() const;
      boost::optional<double> marchValue() const;
      boost::optional<double> aprilValue() const;
      boost::optional<double> mayValue() const;
      boost::optional<double> juneValue() const;
      boost::optional<double> julyValue() const;
      boost::optional<double> augustValue() const;
      boost::optional<double> septemberValue() const;
      boost::optional<double> octoberValue() const;
      boost::optional<double> novemberValue() const;
      boost::optional<double> decemberValue() const;

      bool setVariableType(const std::string& variableType);
      void resetVariableType();

      bool setJanuaryValue(double januaryValue);
      void resetJanuaryValue();
      bool setFebruaryValue(double februaryValue);
      void resetFebruaryValue();
      bool setMarchValue(double marchValue);
      void resetMarchValue();
      bool setAprilValue(double aprilValue);
      void resetAprilValue();
      bool setMayValue(double mayValue);
      void resetMayValue();
      bool setJuneValue(double juneValue);
      void resetJuneValue();
      bool setJulyValue(double julyValue);
      void resetJulyValue();
      bool setAugustValue(double augustValue);
      void resetAugustValue();
      bool setSeptemberValue(double septemberValue);
      void resetSeptemberValue();
      bool setOctoberValue(double octoberValue);
      void resetOctoberValue();
      bool setNovemberValue(double novemberValue);
      void resetNovemberValue();
      bool setDecemberValue(double decemberValue);
      void resetDecemberValue();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
