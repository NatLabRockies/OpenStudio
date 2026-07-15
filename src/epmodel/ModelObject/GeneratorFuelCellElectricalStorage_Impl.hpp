/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GENERATORFUELCELLELECTRICALSTORAGE_IMPL_HPP
#define EPMODEL_GENERATORFUELCELLELECTRICALSTORAGE_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API GeneratorFuelCellElectricalStorage_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~GeneratorFuelCellElectricalStorage_Impl() override = default;

      std::string choiceofModel() const;
      bool setChoiceofModel(const std::string& choiceofModel);
      void resetChoiceofModel();

      double nominalChargingEnergeticEfficiency() const;
      bool setNominalChargingEnergeticEfficiency(double nominalChargingEnergeticEfficiency);
      void resetNominalChargingEnergeticEfficiency();

      double nominalDischargingEnergeticEfficiency() const;
      bool setNominalDischargingEnergeticEfficiency(double nominalDischargingEnergeticEfficiency);
      void resetNominalDischargingEnergeticEfficiency();

      double simpleMaximumCapacity() const;
      bool setSimpleMaximumCapacity(double simpleMaximumCapacity);
      void resetSimpleMaximumCapacity();

      double simpleMaximumPowerDraw() const;
      bool setSimpleMaximumPowerDraw(double simpleMaximumPowerDraw);
      void resetSimpleMaximumPowerDraw();

      double simpleMaximumPowerStore() const;
      bool setSimpleMaximumPowerStore(double simpleMaximumPowerStore);
      void resetSimpleMaximumPowerStore();

      double initialChargeState() const;
      bool setInitialChargeState(double initialChargeState);
      void resetInitialChargeState();

      std::vector<std::string> choiceofModelValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
