/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COMPONENTCOSTLINEITEM_IMPL_HPP
#define EPMODEL_COMPONENTCOSTLINEITEM_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ComponentCostLineItem_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ComponentCostLineItem_Impl() override = default;

      std::vector<std::string> lineItemTypeValues() const;

      boost::optional<std::string> type() const;
      bool setType(const std::string& type);
      void resetType();

      std::string lineItemType() const;
      bool setLineItemType(const std::string& lineItemType);

      std::string itemName() const;
      bool setItemName(const std::string& itemName);

      boost::optional<std::string> objectEndUseKey() const;
      bool setObjectEndUseKey(const std::string& objectEndUseKey);
      void resetObjectEndUseKey();

      boost::optional<double> costperEach() const;
      bool setCostperEach(double costperEach);
      void resetCostperEach();

      boost::optional<double> costperArea() const;
      bool setCostperArea(double costperArea);
      void resetCostperArea();

      boost::optional<double> costperUnitofOutputCapacity() const;
      bool setCostperUnitofOutputCapacity(double costperUnitofOutputCapacity);
      void resetCostperUnitofOutputCapacity();

      boost::optional<double> costperUnitofOutputCapacityperCOP() const;
      bool setCostperUnitofOutputCapacityperCOP(double costperUnitofOutputCapacityperCOP);
      void resetCostperUnitofOutputCapacityperCOP();

      boost::optional<double> costperVolume() const;
      bool setCostperVolume(double costperVolume);
      void resetCostperVolume();

      boost::optional<double> costperVolumeRate() const;
      bool setCostperVolumeRate(double costperVolumeRate);
      void resetCostperVolumeRate();

      boost::optional<double> costperEnergyperTemperatureDifference() const;
      bool setCostperEnergyperTemperatureDifference(double costperEnergyperTemperatureDifference);
      void resetCostperEnergyperTemperatureDifference();

      boost::optional<double> quantity() const;
      bool setQuantity(double quantity);
      void resetQuantity();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
