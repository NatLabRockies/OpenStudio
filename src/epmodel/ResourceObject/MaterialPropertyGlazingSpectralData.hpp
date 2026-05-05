/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_MATERIALPROPERTYGLAZINGSPECTRALDATA_HPP
#define EPMODEL_MATERIALPROPERTYGLAZINGSPECTRALDATA_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class MaterialPropertyGlazingSpectralData_Impl;
  }

  /** MaterialPropertyGlazingSpectralData is a ModelObject that wraps the EnergyPlus IDD object
 * 'MaterialProperty:GlazingSpectralData'. */
  class EPMODEL_API MaterialPropertyGlazingSpectralData : public ModelObject
  {
   public:
    explicit MaterialPropertyGlazingSpectralData(const Model& model);

    virtual ~MaterialPropertyGlazingSpectralData() override = default;
    MaterialPropertyGlazingSpectralData(const MaterialPropertyGlazingSpectralData& other) = default;
    MaterialPropertyGlazingSpectralData(MaterialPropertyGlazingSpectralData&& other) = default;
    MaterialPropertyGlazingSpectralData& operator=(const MaterialPropertyGlazingSpectralData&) = default;
    MaterialPropertyGlazingSpectralData& operator=(MaterialPropertyGlazingSpectralData&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Preserves openstudio::model class naming for this counterpart type.
    // - Field Mapping: In scalar-only scaffold mode, only inherited ModelObject name accessors are exposed.
    // - ForwardTranslator evidence: ForwardTranslateMaterialPropertyGlazingSpectralData maps Name plus extensible spectral groups.
    // - TODO(parity): Add non-scalar extensible spectralDataFields API in a dedicated parity pass.

   protected:
    using ImplType = detail::MaterialPropertyGlazingSpectralData_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit MaterialPropertyGlazingSpectralData(std::shared_ptr<detail::MaterialPropertyGlazingSpectralData_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
