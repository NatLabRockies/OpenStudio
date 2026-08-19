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

  /** \brief Version.
   *
   * \par EnergyPlus object
   * \epobject{group-simulation-parameters.html#version,Version}.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::Version</code>. EPModel exposes public <code>setVersionIdentifier()</code> plus default-state and reset accessors; the Model-only <code>prereleaseIdentifier()</code> and <code>setPrereleaseIdentifier()</code> are not available.
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
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
