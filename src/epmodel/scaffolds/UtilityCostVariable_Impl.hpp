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
      bool setVariableType(const std::string& variableType);
      void resetVariableType();

      boost::optional<double> januaryValue() const;
      bool setJanuaryValue(double januaryValue);
      void resetJanuaryValue();
      boost::optional<double> februaryValue() const;
      bool setFebruaryValue(double februaryValue);
      void resetFebruaryValue();
      boost::optional<double> marchValue() const;
      bool setMarchValue(double marchValue);
      void resetMarchValue();
      boost::optional<double> aprilValue() const;
      bool setAprilValue(double aprilValue);
      void resetAprilValue();
      boost::optional<double> mayValue() const;
      bool setMayValue(double mayValue);
      void resetMayValue();
      boost::optional<double> juneValue() const;
      bool setJuneValue(double juneValue);
      void resetJuneValue();
      boost::optional<double> julyValue() const;
      bool setJulyValue(double julyValue);
      void resetJulyValue();
      boost::optional<double> augustValue() const;
      bool setAugustValue(double augustValue);
      void resetAugustValue();
      boost::optional<double> septemberValue() const;
      bool setSeptemberValue(double septemberValue);
      void resetSeptemberValue();
      boost::optional<double> octoberValue() const;
      bool setOctoberValue(double octoberValue);
      void resetOctoberValue();
      boost::optional<double> novemberValue() const;
      bool setNovemberValue(double novemberValue);
      void resetNovemberValue();
      boost::optional<double> decemberValue() const;
      bool setDecemberValue(double decemberValue);
      void resetDecemberValue();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
