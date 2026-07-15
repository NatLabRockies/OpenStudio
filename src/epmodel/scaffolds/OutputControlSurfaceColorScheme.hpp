/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_OUTPUTCONTROLSURFACECOLORSCHEME_HPP
#define EPMODEL_OUTPUTCONTROLSURFACECOLORSCHEME_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class OutputControlSurfaceColorScheme_Impl;
  }

  class EPMODEL_API OutputControlSurfaceColorScheme : public ModelObject
  {
   public:
    explicit OutputControlSurfaceColorScheme(const Model& model);

    virtual ~OutputControlSurfaceColorScheme() override = default;
    OutputControlSurfaceColorScheme(const OutputControlSurfaceColorScheme& other) = default;
    OutputControlSurfaceColorScheme(OutputControlSurfaceColorScheme&& other) = default;
    OutputControlSurfaceColorScheme& operator=(const OutputControlSurfaceColorScheme&) = default;
    OutputControlSurfaceColorScheme& operator=(OutputControlSurfaceColorScheme&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: This no-counterpart type keeps IDD-derived class/API naming.
    // - Field Mapping: Name remains available through base ModelObject scalar API.
    // - Field Mapping: Extensible Drawing Element Type and Color for Drawing Element fields are excluded from scalar accessors in this scaffold cycle.
    // - TODO(parity): Add extensible-group APIs after scalar saturation without changing base scalar signatures.

   protected:
    using ImplType = detail::OutputControlSurfaceColorScheme_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit OutputControlSurfaceColorScheme(std::shared_ptr<detail::OutputControlSurfaceColorScheme_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
