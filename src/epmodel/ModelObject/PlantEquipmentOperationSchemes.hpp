/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_PLANTEQUIPMENTOPERATIONSCHEMES_HPP
#define EPMODEL_PLANTEQUIPMENTOPERATIONSCHEMES_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <boost/optional.hpp>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class PlantEquipmentOperationSchemes_Impl;
  }

  class EPMODEL_API PlantEquipmentOperationSchemes : public ModelObject
  {
   public:
    explicit PlantEquipmentOperationSchemes(const Model& model);

    virtual ~PlantEquipmentOperationSchemes() override = default;
    PlantEquipmentOperationSchemes(const PlantEquipmentOperationSchemes& other) = default;
    PlantEquipmentOperationSchemes(PlantEquipmentOperationSchemes&& other) = default;
    PlantEquipmentOperationSchemes& operator=(const PlantEquipmentOperationSchemes&) = default;
    PlantEquipmentOperationSchemes& operator=(PlantEquipmentOperationSchemes&&) = default;

    static IddObjectType iddObjectType();
    static std::vector<std::string> controlSchemeObjectTypeValues();

    // Schema Alignment Notes:
    // - API: Exposes the scalar Control Scheme N Object Type choices defined on PlantEquipmentOperationSchemes in the ProposedEnergy+.idd.
    // - Field Mapping: Control Scheme Name and Control Scheme Schedule remain relationship-like object-list/schedule fields and are intentionally excluded from this scalar scaffold.
    // - TODO(parity): Add Control Scheme relationships once scalar parity is satisfied.
    std::string controlScheme1ObjectType() const;
    bool setControlScheme1ObjectType(const std::string& controlScheme1ObjectType);

    boost::optional<std::string> controlScheme2ObjectType() const;
    bool setControlScheme2ObjectType(const std::string& controlScheme2ObjectType);
    void resetControlScheme2ObjectType();

    boost::optional<std::string> controlScheme3ObjectType() const;
    bool setControlScheme3ObjectType(const std::string& controlScheme3ObjectType);
    void resetControlScheme3ObjectType();

    boost::optional<std::string> controlScheme4ObjectType() const;
    bool setControlScheme4ObjectType(const std::string& controlScheme4ObjectType);
    void resetControlScheme4ObjectType();

    boost::optional<std::string> controlScheme5ObjectType() const;
    bool setControlScheme5ObjectType(const std::string& controlScheme5ObjectType);
    void resetControlScheme5ObjectType();

    boost::optional<std::string> controlScheme6ObjectType() const;
    bool setControlScheme6ObjectType(const std::string& controlScheme6ObjectType);
    void resetControlScheme6ObjectType();

    boost::optional<std::string> controlScheme7ObjectType() const;
    bool setControlScheme7ObjectType(const std::string& controlScheme7ObjectType);
    void resetControlScheme7ObjectType();

    boost::optional<std::string> controlScheme8ObjectType() const;
    bool setControlScheme8ObjectType(const std::string& controlScheme8ObjectType);
    void resetControlScheme8ObjectType();

   protected:
    using ImplType = detail::PlantEquipmentOperationSchemes_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit PlantEquipmentOperationSchemes(std::shared_ptr<detail::PlantEquipmentOperationSchemes_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
