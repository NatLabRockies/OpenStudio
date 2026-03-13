/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_VERSION_HPP
#define EPMODEL_VERSION_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class Version_Impl;
  }

  class EPMODEL_API Version : public ModelObject
  {
   public:
    explicit Version(const Model& model);

    virtual ~Version() override = default;
    Version(const Version& other) = default;
    Version(Version&& other) = default;
    Version& operator=(const Version&) = default;
    Version& operator=(Version&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model Version scalar accessor names/signatures.
    // - Field Mapping: versionIdentifier maps to the EnergyPlus Version Identifier field.
    // - ForwardTranslator::translateVersion writes ENERGYPLUS_VERSION into the Version Identifier field by default.
    /** @name Version identifier field */
    //@{
    std::string versionIdentifier() const;
    bool isVersionIdentifierDefaulted() const;
    bool setVersionIdentifier(const std::string& versionIdentifier);
    void resetVersionIdentifier();
    //@}

   protected:
    using ImplType = detail::Version_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit Version(std::shared_ptr<detail::Version_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
