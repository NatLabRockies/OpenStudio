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

#include <utilities/idf/IdfExtensibleGroup.hpp>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API PlantEquipmentOperationSchemes_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~PlantEquipmentOperationSchemes_Impl() override = default;

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

      std::vector<std::string> controlSchemeObjectTypeValues() const;

     private:
      boost::optional<std::string> controlSchemeObjectTypeField(unsigned schemeIndex) const;
      boost::optional<IdfExtensibleGroup> controlSchemeGroup(unsigned schemeIndex) const;
      boost::optional<IdfExtensibleGroup> ensureControlSchemeGroup(unsigned schemeIndex);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
