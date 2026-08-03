/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_LAYEREDCONSTRUCTION_HPP
#define EPMODEL_LAYEREDCONSTRUCTION_HPP

#include "EPModelAPI.hpp"
#include "ConstructionBase/ConstructionBase.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class FenestrationMaterial;
  class Material;
  class OpaqueMaterial;

  namespace detail {
    class LayeredConstruction_Impl;
  }

  /** LayeredConstruction is an abstract base class for constructions composed of material layers. */
  class EPMODEL_API LayeredConstruction : public ConstructionBase
  {
   public:
    virtual ~LayeredConstruction() override = default;
    LayeredConstruction(const LayeredConstruction& other) = default;
    LayeredConstruction(LayeredConstruction&& other) = default;
    LayeredConstruction& operator=(const LayeredConstruction&) = default;
    LayeredConstruction& operator=(LayeredConstruction&&) = default;

    /** @name Getters */
    //@{

    std::vector<Material> layers() const;
    Material getLayer(unsigned layerIndex) const;

    //@}
    /** @name Static Validators */
    //@{

    /** Returns true if the given layers are a valid set for a LayeredConstruction. */
    static bool layersAreValid(const std::vector<Material>& materials);
    static bool layersAreValid(const std::vector<OpaqueMaterial>& opaqueMaterials);
    static bool layersAreValid(const std::vector<FenestrationMaterial>& fenestrationMaterials);

    //@}
    /** @name Setters */
    //@{

    bool eraseLayer(unsigned layerIndex);
    bool insertLayer(unsigned layerIndex, const Material& material);
    bool setLayer(unsigned layerIndex, const Material& material);
    bool setLayers(const std::vector<Material>& materials);

    //@}
    /** @name Queries */
    //@{

    std::vector<unsigned> nullLayers() const;
    unsigned numLayers() const;
    std::vector<unsigned> getLayerIndices(const Material& material) const;

    //@}

    void ensureUniqueLayers();

   protected:
    LayeredConstruction(IddObjectType type, const Model& model);

    using ImplType = detail::LayeredConstruction_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit LayeredConstruction(std::shared_ptr<detail::LayeredConstruction_Impl> impl);

   private:
    REGISTER_LOGGER("openstudio.epmodel.LayeredConstruction");
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
