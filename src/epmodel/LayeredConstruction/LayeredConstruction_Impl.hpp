/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_LAYEREDCONSTRUCTION_IMPL_HPP
#define EPMODEL_LAYEREDCONSTRUCTION_IMPL_HPP

#include "ConstructionBase/ConstructionBase_Impl.hpp"

#include <utilities/idf/WorkspaceExtensibleGroup.hpp>

#include <vector>

namespace openstudio {
namespace epmodel {

  class Material;

  namespace detail {

    class EPMODEL_API LayeredConstruction_Impl : public ConstructionBase_Impl
    {
     public:
      using ConstructionBase_Impl::ConstructionBase_Impl;
      virtual ~LayeredConstruction_Impl() override = default;

      /** @name Getters */
      //@{

      std::vector<Material> layers() const;
      Material getLayer(unsigned layerIndex) const;
      virtual bool eraseLayer(unsigned layerIndex);
      virtual bool insertLayer(unsigned layerIndex, const Material& material);
      virtual bool setLayer(unsigned layerIndex, const Material& material);
      virtual bool setLayers(const std::vector<Material>& materials);
      /** Returns layer indices that do not point to a Material object. Should be empty before simulation. */
      std::vector<unsigned> nullLayers() const;
      /** Returns the number of non-null layers. */
      unsigned numLayers() const;
      std::vector<unsigned> getLayerIndices(const Material& material) const;

      bool isOpaque() const override;
      bool isFenestration() const override;
      bool isSolarDiffusing() const override;
      bool isModelPartition() const override;
      bool isGreenRoof() const override;

      /** Clones any material layers that are shared with other constructions so that this
       *  construction has its own copies. */
      void ensureUniqueLayers();

     private:
      REGISTER_LOGGER("openstudio.epmodel.LayeredConstruction");

      /** Removes null layers and adjusts layerIndex accordingly. */
      unsigned mf_clearNullLayers(unsigned layerIndex);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
