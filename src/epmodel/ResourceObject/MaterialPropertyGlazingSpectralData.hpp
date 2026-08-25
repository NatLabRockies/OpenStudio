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

  /** \brief Names a set of glazing spectral data.
   *
   * \par EnergyPlus object
   * \epobject{group-surface-construction-elements.html#materialpropertyglazingspectraldata,MaterialProperty:GlazingSpectralData}.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::MaterialPropertyGlazingSpectralData</code>.
   * EPModel currently exposes only inherited name access; the Model spectral
   * row methods (<code>spectralDataFields()</code>,
   * <code>setSpectralDataFields()</code>, <code>addSpectralDataField()</code>,
   * and <code>resetSpectralDataFields()</code>) are not available.
   *
   * \par Known limitations
   * Spectral wavelength, transmittance, and reflectance rows cannot yet be
   * created or edited through this wrapper.
   */
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
