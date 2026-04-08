/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_PLANTEQUIPMENTOPERATIONSCHEMES_IMPL_HPP
#define EPMODEL_PLANTEQUIPMENTOPERATIONSCHEMES_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <boost/optional.hpp>
#include <string>
#include <vector>

#include <utilities/idf/WorkspaceExtensibleGroup.hpp>

namespace openstudio {
namespace epmodel {

  class ModelObject;
  class PlantEquipmentOperationCoolingLoad;
  class PlantEquipmentOperationHeatingLoad;
  class PlantEquipmentOperationScheme;
  class Schedule;

  namespace detail {

    class EPMODEL_API PlantEquipmentOperationSchemes_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~PlantEquipmentOperationSchemes_Impl() override = default;

      boost::optional<openstudio::epmodel::PlantEquipmentOperationHeatingLoad> plantEquipmentOperationHeatingLoad() const;
      bool setPlantEquipmentOperationHeatingLoad(const openstudio::epmodel::PlantEquipmentOperationHeatingLoad& controlScheme);
      void resetPlantEquipmentOperationHeatingLoad();
      boost::optional<openstudio::epmodel::Schedule> plantEquipmentOperationHeatingLoadSchedule() const;
      bool setPlantEquipmentOperationHeatingLoadSchedule(openstudio::epmodel::Schedule& schedule);
      void resetPlantEquipmentOperationHeatingLoadSchedule();

      boost::optional<openstudio::epmodel::PlantEquipmentOperationCoolingLoad> plantEquipmentOperationCoolingLoad() const;
      bool setPlantEquipmentOperationCoolingLoad(const openstudio::epmodel::PlantEquipmentOperationCoolingLoad& controlScheme);
      void resetPlantEquipmentOperationCoolingLoad();
      boost::optional<openstudio::epmodel::Schedule> plantEquipmentOperationCoolingLoadSchedule() const;
      bool setPlantEquipmentOperationCoolingLoadSchedule(openstudio::epmodel::Schedule& schedule);
      void resetPlantEquipmentOperationCoolingLoadSchedule();

      boost::optional<openstudio::epmodel::PlantEquipmentOperationScheme> primaryPlantEquipmentOperationScheme() const;
      bool setPrimaryPlantEquipmentOperationScheme(const openstudio::epmodel::PlantEquipmentOperationScheme& controlScheme);
      void resetPrimaryPlantEquipmentOperationScheme();
      boost::optional<openstudio::epmodel::Schedule> primaryPlantEquipmentOperationSchemeSchedule() const;
      bool setPrimaryPlantEquipmentOperationSchemeSchedule(openstudio::epmodel::Schedule& schedule);
      void resetPrimaryPlantEquipmentOperationSchemeSchedule();

      boost::optional<openstudio::epmodel::Schedule> componentSetpointOperationSchemeSchedule() const;
      bool setComponentSetpointOperationSchemeSchedule(openstudio::epmodel::Schedule& schedule);
      void resetComponentSetpointOperationSchemeSchedule();

      std::vector<std::string> controlSchemeObjectTypeValues() const;

      void doCanonicalize(LoadContext& context) override;

     private:
      static const std::string& heatingLoadControlSchemeObjectType();
      static const std::string& coolingLoadControlSchemeObjectType();
      static const std::string& componentSetpointControlSchemeObjectType();
      static const std::string& defaultPrimaryControlSchemeObjectType();
      static bool isSupportedControlSchemeType(const std::string& controlSchemeObjectType);
      static bool isPrimaryControlSchemeType(const std::string& controlSchemeObjectType);

      boost::optional<std::string> controlSchemeObjectTypeField(unsigned schemeIndex) const;
      boost::optional<std::string> controlSchemeRawField(unsigned schemeIndex, unsigned fieldIndex) const;
      boost::optional<unsigned> controlSchemeIndex(const std::string& controlSchemeObjectType) const;
      boost::optional<unsigned> primaryControlSchemeIndex() const;

      boost::optional<openstudio::epmodel::ModelObject> controlScheme(const std::string& controlSchemeObjectType) const;
      boost::optional<openstudio::epmodel::ModelObject> controlScheme(unsigned schemeIndex) const;
      // Canonicalization-only repair helper. Ordinary APIs are expected to work
      // from live pointers or explicit typed setters, not by resolving raw
      // imported field strings on demand.
      boost::optional<openstudio::epmodel::ModelObject> resolveAndAttachControlScheme(unsigned schemeIndex);
      bool setControlScheme(unsigned schemeIndex, const std::string& controlSchemeObjectType,
                            const openstudio::epmodel::ModelObject& controlScheme);
      bool setControlScheme(const std::string& controlSchemeObjectType, const openstudio::epmodel::ModelObject& controlScheme);
      void resetControlScheme(const std::string& controlSchemeObjectType);
      boost::optional<openstudio::epmodel::Schedule> controlSchemeSchedule(const std::string& controlSchemeObjectType) const;
      boost::optional<openstudio::epmodel::Schedule> controlSchemeSchedule(unsigned schemeIndex) const;
      // Canonicalization-only repair helper. Ordinary APIs are expected to work
      // from live pointers or explicit typed setters, not by resolving raw
      // imported field strings on demand.
      boost::optional<openstudio::epmodel::Schedule> resolveAndAttachControlSchemeSchedule(unsigned schemeIndex);
      bool setControlSchemeSchedule(unsigned schemeIndex, openstudio::epmodel::Schedule& schedule);
      bool setControlSchemeSchedule(const std::string& controlSchemeObjectType, openstudio::epmodel::Schedule& schedule);
      void resetControlSchemeSchedule(const std::string& controlSchemeObjectType);
      bool clearControlScheme(unsigned schemeIndex);
      bool clearControlSchemeSchedule(unsigned schemeIndex);
      void eraseControlSchemeGroupIfEmpty(unsigned schemeIndex);
      bool groupHasControlScheme(unsigned schemeIndex) const;
      bool groupHasControlSchemeSchedule(unsigned schemeIndex) const;

      boost::optional<WorkspaceExtensibleGroup> controlSchemeGroup(unsigned schemeIndex) const;
      boost::optional<WorkspaceExtensibleGroup> ensureControlSchemeGroup(unsigned schemeIndex);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
