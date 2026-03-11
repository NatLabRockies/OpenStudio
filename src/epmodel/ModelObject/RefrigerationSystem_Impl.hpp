/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_REFRIGERATIONSYSTEM_IMPL_HPP
#define EPMODEL_REFRIGERATIONSYSTEM_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <string>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API RefrigerationSystem_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~RefrigerationSystem_Impl() override = default;

      // Schema Alignment Notes (Impl): Transfer load lists lack simple scalar fields beyond Name, so they are
      // generated through Refrigeration:TransferLoadList (name only) objects derived from secondary system and cascade
      // condenser references rather than dedicated scalars in this impl.

      double minimumCondensingTemperature() const;
      bool setMinimumCondensingTemperature(double minimumCondensingTemperature);

      std::string refrigerationSystemWorkingFluidType() const;
      bool setRefrigerationSystemWorkingFluidType(const std::string& refrigerationSystemWorkingFluidType);

      std::string suctionTemperatureControlType() const;
      bool setSuctionTemperatureControlType(const std::string& suctionTemperatureControlType);
      bool isSuctionTemperatureControlTypeDefaulted() const;
      void resetSuctionTemperatureControlType();

      double sumUASuctionPiping() const;
      bool setSumUASuctionPiping(double sumUASuctionPiping);
      bool isSumUASuctionPipingDefaulted() const;
      void resetSumUASuctionPiping();

      std::string endUseSubcategory() const;
      bool setEndUseSubcategory(const std::string& endUseSubcategory);
      bool isEndUseSubcategoryDefaulted() const;
      void resetEndUseSubcategory();

      std::string intercoolerType() const;
      bool setIntercoolerType(const std::string& intercoolerType);
      bool isIntercoolerTypeDefaulted() const;
      void resetIntercoolerType();

      double shellandCoilIntercoolerEffectiveness() const;
      bool setShellandCoilIntercoolerEffectiveness(double shellandCoilIntercoolerEffectiveness);
      bool isShellandCoilIntercoolerEffectivenessDefaulted() const;
      void resetShellandCoilIntercoolerEffectiveness();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_REFRIGERATIONSYSTEM_IMPL_HPP
