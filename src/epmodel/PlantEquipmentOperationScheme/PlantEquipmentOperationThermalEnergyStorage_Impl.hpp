/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PLANTEQUIPMENTOPERATIONTHERMALENERGYSTORAGE_IMPL_HPP
#define EPMODEL_PLANTEQUIPMENTOPERATIONTHERMALENERGYSTORAGE_IMPL_HPP

#include "PlantEquipmentOperationScheme_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API PlantEquipmentOperationThermalEnergyStorage_Impl : public PlantEquipmentOperationScheme_Impl
    {
     public:
      using PlantEquipmentOperationScheme_Impl::PlantEquipmentOperationScheme_Impl;

      double nonChargingChilledWaterTemperature() const;
      bool setNonChargingChilledWaterTemperature(double nonChargingChilledWaterTemperature);

      double chargingChilledWaterTemperature() const;
      bool setChargingChilledWaterTemperature(double chargingChilledWaterTemperature);

      boost::optional<double> component1FlowRate() const;
      bool isComponent1FlowRateAutosized() const;
      bool setComponent1FlowRate(double component1FlowRate);
      void autosizeComponent1FlowRate();

      std::string component1ObjectType() const;
      bool setComponent1ObjectType(const std::string& component1ObjectType);

      std::string component1OperationType() const;
      bool setComponent1OperationType(const std::string& component1OperationType);

      boost::optional<std::string> component2ObjectType() const;
      bool setComponent2ObjectType(const std::string& component2ObjectType);
      void resetComponent2ObjectType();

      boost::optional<double> component2FlowRate() const;
      bool isComponent2FlowRateAutosized() const;
      bool setComponent2FlowRate(double component2FlowRate);
      void resetComponent2FlowRate();
      void autosizeComponent2FlowRate();

      boost::optional<std::string> component2OperationType() const;
      bool setComponent2OperationType(const std::string& component2OperationType);
      void resetComponent2OperationType();

      boost::optional<std::string> component3ObjectType() const;
      bool setComponent3ObjectType(const std::string& component3ObjectType);
      void resetComponent3ObjectType();

      boost::optional<double> component3FlowRate() const;
      bool isComponent3FlowRateAutosized() const;
      bool setComponent3FlowRate(double component3FlowRate);
      void resetComponent3FlowRate();
      void autosizeComponent3FlowRate();

      boost::optional<std::string> component3OperationType() const;
      bool setComponent3OperationType(const std::string& component3OperationType);
      void resetComponent3OperationType();

      boost::optional<std::string> component4ObjectType() const;
      bool setComponent4ObjectType(const std::string& component4ObjectType);
      void resetComponent4ObjectType();

      boost::optional<double> component4FlowRate() const;
      bool isComponent4FlowRateAutosized() const;
      bool setComponent4FlowRate(double component4FlowRate);
      void resetComponent4FlowRate();
      void autosizeComponent4FlowRate();

      boost::optional<std::string> component4OperationType() const;
      bool setComponent4OperationType(const std::string& component4OperationType);
      void resetComponent4OperationType();

      boost::optional<std::string> component5ObjectType() const;
      bool setComponent5ObjectType(const std::string& component5ObjectType);
      void resetComponent5ObjectType();

      boost::optional<double> component5FlowRate() const;
      bool isComponent5FlowRateAutosized() const;
      bool setComponent5FlowRate(double component5FlowRate);
      void resetComponent5FlowRate();
      void autosizeComponent5FlowRate();

      boost::optional<std::string> component5OperationType() const;
      bool setComponent5OperationType(const std::string& component5OperationType);
      void resetComponent5OperationType();

      boost::optional<std::string> component6ObjectType() const;
      bool setComponent6ObjectType(const std::string& component6ObjectType);
      void resetComponent6ObjectType();

      boost::optional<double> component6FlowRate() const;
      bool isComponent6FlowRateAutosized() const;
      bool setComponent6FlowRate(double component6FlowRate);
      void resetComponent6FlowRate();
      void autosizeComponent6FlowRate();

      boost::optional<std::string> component6OperationType() const;
      bool setComponent6OperationType(const std::string& component6OperationType);
      void resetComponent6OperationType();

      boost::optional<std::string> component7ObjectType() const;
      bool setComponent7ObjectType(const std::string& component7ObjectType);
      void resetComponent7ObjectType();

      boost::optional<double> component7FlowRate() const;
      bool isComponent7FlowRateAutosized() const;
      bool setComponent7FlowRate(double component7FlowRate);
      void resetComponent7FlowRate();
      void autosizeComponent7FlowRate();

      boost::optional<std::string> component7OperationType() const;
      bool setComponent7OperationType(const std::string& component7OperationType);
      void resetComponent7OperationType();

      boost::optional<std::string> component8ObjectType() const;
      bool setComponent8ObjectType(const std::string& component8ObjectType);
      void resetComponent8ObjectType();

      boost::optional<double> component8FlowRate() const;
      bool isComponent8FlowRateAutosized() const;
      bool setComponent8FlowRate(double component8FlowRate);
      void resetComponent8FlowRate();
      void autosizeComponent8FlowRate();

      boost::optional<std::string> component8OperationType() const;
      bool setComponent8OperationType(const std::string& component8OperationType);
      void resetComponent8OperationType();

      boost::optional<std::string> component9ObjectType() const;
      bool setComponent9ObjectType(const std::string& component9ObjectType);
      void resetComponent9ObjectType();

      boost::optional<double> component9FlowRate() const;
      bool isComponent9FlowRateAutosized() const;
      bool setComponent9FlowRate(double component9FlowRate);
      void resetComponent9FlowRate();
      void autosizeComponent9FlowRate();

      boost::optional<std::string> component9OperationType() const;
      bool setComponent9OperationType(const std::string& component9OperationType);
      void resetComponent9OperationType();

      boost::optional<std::string> component10ObjectType() const;
      bool setComponent10ObjectType(const std::string& component10ObjectType);
      void resetComponent10ObjectType();

      boost::optional<double> component10FlowRate() const;
      bool isComponent10FlowRateAutosized() const;
      bool setComponent10FlowRate(double component10FlowRate);
      void resetComponent10FlowRate();
      void autosizeComponent10FlowRate();

      boost::optional<std::string> component10OperationType() const;
      bool setComponent10OperationType(const std::string& component10OperationType);
      void resetComponent10OperationType();

      std::vector<std::string> component1ObjectTypeValues() const;
      std::vector<std::string> component1OperationTypeValues() const;

      std::vector<std::string> component2ObjectTypeValues() const;
      std::vector<std::string> component2OperationTypeValues() const;

      std::vector<std::string> component3ObjectTypeValues() const;
      std::vector<std::string> component3OperationTypeValues() const;

      std::vector<std::string> component4ObjectTypeValues() const;
      std::vector<std::string> component4OperationTypeValues() const;

      std::vector<std::string> component5ObjectTypeValues() const;
      std::vector<std::string> component5OperationTypeValues() const;

      std::vector<std::string> component6ObjectTypeValues() const;
      std::vector<std::string> component6OperationTypeValues() const;

      std::vector<std::string> component7ObjectTypeValues() const;
      std::vector<std::string> component7OperationTypeValues() const;

      std::vector<std::string> component8ObjectTypeValues() const;
      std::vector<std::string> component8OperationTypeValues() const;

      std::vector<std::string> component9ObjectTypeValues() const;
      std::vector<std::string> component9OperationTypeValues() const;

      std::vector<std::string> component10ObjectTypeValues() const;
      std::vector<std::string> component10OperationTypeValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
