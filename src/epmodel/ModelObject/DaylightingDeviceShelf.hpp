/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_DAYLIGHTINGDEVICESHELF_HPP
#define EPMODEL_DAYLIGHTINGDEVICESHELF_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class DaylightingDeviceShelf_Impl;
  }

  /** \brief Represents <code>DaylightingDevice:Shelf</code>.
   *
   * \par EnergyPlus object
   * \epobject{group-daylighting.html#daylightingdeviceshelf,DaylightingDevice:Shelf}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::DaylightingDeviceShelf</code>.
   * **Not yet available:** Model surface, construction, and extensible transition/shelf relationship conveniences are not exposed unless declared here.
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
  class EPMODEL_API DaylightingDeviceShelf : public ModelObject
  {
   public:
    explicit DaylightingDeviceShelf(const Model& model);

    virtual ~DaylightingDeviceShelf() override = default;
    DaylightingDeviceShelf(const DaylightingDeviceShelf& other) = default;
    DaylightingDeviceShelf(DaylightingDeviceShelf&& other) = default;
    DaylightingDeviceShelf& operator=(const DaylightingDeviceShelf&) = default;
    DaylightingDeviceShelf& operator=(DaylightingDeviceShelf&&) = default;

    static IddObjectType iddObjectType();
    boost::optional<double> viewFactortoOutsideShelf() const;
    bool setViewFactortoOutsideShelf(double viewFactortoOutsideShelf);
    void resetViewFactortoOutsideShelf();

   protected:
    using ImplType = detail::DaylightingDeviceShelf_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit DaylightingDeviceShelf(std::shared_ptr<detail::DaylightingDeviceShelf_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
