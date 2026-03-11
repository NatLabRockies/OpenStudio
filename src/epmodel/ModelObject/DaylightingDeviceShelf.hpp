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

  // Schema Alignment Notes:
  // - API: Preserves openstudio::model scalar accessor naming/signature for counterpart parity.
  // - Field Mapping: viewFactortoOutsideShelf maps directly to DaylightingDevice:Shelf field
  //   View Factor to Outside Shelf.
  // - Field Mapping: WindowName, InsideShelfName, OutsideShelfName, and OutsideShelfConstructionName
  //   are relationship-like link fields and intentionally excluded from scalar accessors.
  // - ForwardTranslator evidence: translateDaylightingDeviceShelf writes ViewFactortoOutsideShelf
  //   directly from modelObject.viewFactortoOutsideShelf() when present.
  // - TODO(parity): Add typed relationship APIs for shelf/window linkage during non-scalar parity work.
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
