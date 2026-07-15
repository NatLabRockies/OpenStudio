/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COMPLEXFENESTRATIONPROPERTYSOLARABSORBEDLAYERS_HPP
#define EPMODEL_COMPLEXFENESTRATIONPROPERTYSOLARABSORBEDLAYERS_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ComplexFenestrationPropertySolarAbsorbedLayers_Impl;
  }

  class EPMODEL_API ComplexFenestrationPropertySolarAbsorbedLayers : public ModelObject
  {
   public:
    explicit ComplexFenestrationPropertySolarAbsorbedLayers(const Model& model);

    virtual ~ComplexFenestrationPropertySolarAbsorbedLayers() override = default;
    ComplexFenestrationPropertySolarAbsorbedLayers(const ComplexFenestrationPropertySolarAbsorbedLayers& other) = default;
    ComplexFenestrationPropertySolarAbsorbedLayers(ComplexFenestrationPropertySolarAbsorbedLayers&& other) = default;
    ComplexFenestrationPropertySolarAbsorbedLayers& operator=(const ComplexFenestrationPropertySolarAbsorbedLayers&) = default;
    ComplexFenestrationPropertySolarAbsorbedLayers& operator=(ComplexFenestrationPropertySolarAbsorbedLayers&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: This no-counterpart epmodel type uses IDD-derived class/accessor naming.
    // - Field Mapping: Name remains available through base ModelObject scalar API.
    // - Field Mapping: Fenestration Surface, Construction Name, and Layer 1-5 Solar Radiation Absorbed Schedule Name
    //   are object-list relationship fields and are intentionally excluded from simple scalar accessor scaffolding.
    // - TODO(parity): Add relationship helper APIs after scalar scaffold saturation.

   protected:
    using ImplType = detail::ComplexFenestrationPropertySolarAbsorbedLayers_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ComplexFenestrationPropertySolarAbsorbedLayers(std::shared_ptr<detail::ComplexFenestrationPropertySolarAbsorbedLayers_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
