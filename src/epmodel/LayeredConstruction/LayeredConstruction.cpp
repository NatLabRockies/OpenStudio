/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "LayeredConstruction/LayeredConstruction.hpp"
#include "LayeredConstruction/LayeredConstruction_Impl.hpp"

#include "Model.hpp"
#include "Material/Material_Impl.hpp"
#include "FenestrationMaterial/FenestrationMaterial.hpp"
#include "FenestrationMaterial/FenestrationMaterial_Impl.hpp"
#include "OpaqueMaterial/OpaqueMaterial.hpp"
#include "OpaqueMaterial/OpaqueMaterial_Impl.hpp"
#include "OpaqueMaterial/AirGap.hpp"
#include "OpaqueMaterial/AirGap_Impl.hpp"
#include "OpaqueMaterial/RoofVegetation.hpp"
#include "OpaqueMaterial/RoofVegetation_Impl.hpp"
#include "Glazing/Glazing.hpp"
#include "Glazing/Glazing_Impl.hpp"
#include "Glazing/SimpleGlazing.hpp"
#include "Glazing/SimpleGlazing_Impl.hpp"
#include "Glazing/StandardGlazing.hpp"
#include "Glazing/StandardGlazing_Impl.hpp"
#include "Glazing/RefractionExtinctionGlazing.hpp"
#include "Glazing/RefractionExtinctionGlazing_Impl.hpp"
#include "GasLayer/GasLayer.hpp"
#include "GasLayer/GasLayer_Impl.hpp"

#include <utilities/core/Assert.hpp>

namespace openstudio {
namespace epmodel {

  namespace detail {

    std::vector<Material> LayeredConstruction_Impl::layers() const {
      std::vector<Material> result;
      for (const IdfExtensibleGroup& idfGroup : extensibleGroups()) {
        auto group = idfGroup.cast<WorkspaceExtensibleGroup>();
        auto oTarget = group.getTarget(0);
        if (!oTarget) {
          LOG(Warn, "Skipping layer " << group.groupIndex() << " in " << briefDescription()
                                      << ", as there is no Material object referenced by the corresponding field.");
          continue;
        }
        auto oMaterial = oTarget->optionalCast<Material>();
        if (!oMaterial) {
          LOG(Warn, "Skipping layer " << group.groupIndex() << " in " << briefDescription() << ", as the referenced object is not a Material.");
          continue;
        }
        result.push_back(*oMaterial);
      }
      return result;
    }

    Material LayeredConstruction_Impl::getLayer(unsigned layerIndex) const {
      if (layerIndex >= numLayers()) {
        LOG_AND_THROW("Asked to get material layer indexed " << layerIndex << ", but " << briefDescription() << " has just " << numLayers()
                                                             << " layers.");
      }
      IdfExtensibleGroup idfGroup = getExtensibleGroup(layerIndex);
      OS_ASSERT(!idfGroup.empty());
      auto group = idfGroup.cast<WorkspaceExtensibleGroup>();
      auto oTarget = group.getTarget(0);
      if (!oTarget) {
        LOG_AND_THROW("There is no material at layerIndex " << layerIndex << " in " << briefDescription() << ".");
      }
      auto oMaterial = oTarget->optionalCast<Material>();
      if (!oMaterial) {
        LOG_AND_THROW("Object at layerIndex " << layerIndex << " in " << briefDescription() << " is not a Material.");
      }
      return *oMaterial;
    }

    bool LayeredConstruction_Impl::eraseLayer(unsigned layerIndex) {
      layerIndex = mf_clearNullLayers(layerIndex);
      std::vector<Material> ls = layers();
      if (layerIndex >= ls.size()) {
        return false;
      }
      ls.erase(ls.begin() + layerIndex);
      if ((model().strictnessLevel() < StrictnessLevel::Final) || LayeredConstruction::layersAreValid(ls)) {
        return !eraseExtensibleGroup(layerIndex).empty();
      }
      return false;
    }

    bool LayeredConstruction_Impl::insertLayer(unsigned layerIndex, const Material& material) {
      if (material.model() != model()) {
        return false;
      }
      layerIndex = mf_clearNullLayers(layerIndex);

      // DLM: duplicates check in layersAreValid which is not called if strictness < Final
      if (isFenestration()) {
        if (layerIndex >= 8) {
          return false;
        }
      } else if (layerIndex >= 10) {
        return false;
      }

      unsigned n = numLayers();
      std::vector<Material> ls = layers();
      auto layersBegin = ls.begin();
      auto layersEnd = ls.end();
      auto insertAtIt = layersBegin;
      while ((static_cast<unsigned>(insertAtIt - layersBegin) < layerIndex) && (insertAtIt != layersEnd)) {
        ++insertAtIt;
      }
      ls.insert(insertAtIt, material);
      OS_ASSERT(ls.size() == ++n);
      if ((model().strictnessLevel() < StrictnessLevel::Final) || LayeredConstruction::layersAreValid(ls)) {
        IdfExtensibleGroup idfGroup = insertExtensibleGroup(layerIndex, StringVector());
        OS_ASSERT(!idfGroup.empty());
        auto group = idfGroup.cast<WorkspaceExtensibleGroup>();
        bool ok = group.setPointer(0, material.handle());
        OS_ASSERT(ok);
        return true;
      }
      return false;
    }

    bool LayeredConstruction_Impl::setLayer(unsigned layerIndex, const Material& material) {
      if (material.model() != model()) {
        return false;
      }
      layerIndex = mf_clearNullLayers(layerIndex);
      if (layerIndex >= numLayers()) {
        LOG(Info, "Asked to change the Material at layer " << layerIndex << " in " << briefDescription() << ", but there are only " << numLayers()
                                                           << " layers.");
        return false;
      }
      std::vector<Material> ls = layers();
      ls[layerIndex] = material;
      if ((model().strictnessLevel() < StrictnessLevel::Final) || LayeredConstruction::layersAreValid(ls)) {
        auto group = getExtensibleGroup(layerIndex).cast<WorkspaceExtensibleGroup>();
        OS_ASSERT(!group.empty());
        bool ok = group.setPointer(0, material.handle());
        OS_ASSERT(ok);
        return true;
      }
      return false;
    }

    bool LayeredConstruction_Impl::setLayers(const std::vector<Material>& materials) {
      // DLM: duplicates check in layersAreValid which is not called if strictness < Final
      if (materials.empty()) {
        // ok
      } else if (materials[0].optionalCast<FenestrationMaterial>()) {
        if (materials.size() > 8) {
          return false;
        }
      } else if (materials.size() > 10) {
        return false;
      }
      for (const Material& material : materials) {
        if (material.model() != model()) {
          return false;
        }
      }

      if ((model().strictnessLevel() < StrictnessLevel::Final) || LayeredConstruction::layersAreValid(materials)) {
        clearExtensibleGroups();
        for (const Material& material : materials) {
          OS_ASSERT(material.model() == model());
          auto group = pushExtensibleGroup(StringVector(), false).cast<WorkspaceExtensibleGroup>();
          OS_ASSERT(!group.empty());
          bool ok = group.setPointer(0, material.handle());
          OS_ASSERT(ok);
        }
        return true;
      }
      return false;
    }

    std::vector<unsigned> LayeredConstruction_Impl::nullLayers() const {
      std::vector<unsigned> result;
      for (const IdfExtensibleGroup& idfGroup : extensibleGroups()) {
        auto group = idfGroup.cast<WorkspaceExtensibleGroup>();
        auto oTarget = group.getTarget(0);
        if (!oTarget || !oTarget->optionalCast<Material>()) {
          result.push_back(group.groupIndex());
        }
      }
      return result;
    }

    unsigned LayeredConstruction_Impl::numLayers() const {
      return layers().size();
    }

    std::vector<unsigned> LayeredConstruction_Impl::getLayerIndices(const Material& material) const {
      std::vector<unsigned> result;
      for (const IdfExtensibleGroup& idfGroup : extensibleGroups()) {
        auto group = idfGroup.cast<WorkspaceExtensibleGroup>();
        auto oTarget = group.getTarget(0);
        if (!oTarget) {
          continue;
        }
        auto oMaterial = oTarget->optionalCast<Material>();
        if (oMaterial && (material.handle() == oMaterial->handle())) {
          result.push_back(group.groupIndex());
        }
      }
      return result;
    }

    bool LayeredConstruction_Impl::isOpaque() const {
      std::vector<Material> ls = layers();
      for (const Material& layer : ls) {
        if (!layer.optionalCast<OpaqueMaterial>()) {
          return false;
        }
      }
      return true;
    }

    bool LayeredConstruction_Impl::isFenestration() const {
      std::vector<Material> ls = layers();
      for (const Material& layer : ls) {
        if (!layer.optionalCast<FenestrationMaterial>()) {
          return false;
        }
      }
      return true;
    }

    bool LayeredConstruction_Impl::isSolarDiffusing() const {
      std::vector<Material> ls = layers();
      if (ls.empty()) {
        return false;
      }
      if (!isFenestration()) {
        return false;
      }
      for (const Material& layer : ls) {
        if (auto sg = layer.optionalCast<StandardGlazing>()) {
          if (sg->solarDiffusing()) {
            return true;
          }
        } else if (auto reg = layer.optionalCast<RefractionExtinctionGlazing>()) {
          if (reg->solarDiffusing()) {
            return true;
          }
        }
      }
      return false;
    }

    bool LayeredConstruction_Impl::isModelPartition() const {
      return false;
    }

    bool LayeredConstruction_Impl::isGreenRoof() const {
      std::vector<Material> ls = layers();
      return !ls.empty() && ls[0].optionalCast<RoofVegetation>().has_value();
    }

    void LayeredConstruction_Impl::ensureUniqueLayers() {
      for (const IdfExtensibleGroup& idfGroup : extensibleGroups()) {
        auto group = idfGroup.cast<WorkspaceExtensibleGroup>();
        auto oTarget = group.getTarget(0);
        if (!oTarget) {
          LOG(Warn, "Skipping layer " << group.groupIndex() << " in " << briefDescription()
                                      << ", as there is no Material object referenced by the corresponding field.");
          continue;
        }
        auto oMaterial = oTarget->optionalCast<Material>();
        if (!oMaterial) {
          continue;
        }
        // If this material is referenced by more than one object, clone it
        if (oMaterial->numSources() > 1) {
          auto newMaterialObj = oMaterial->clone();
          bool ok = group.setPointer(0, newMaterialObj.handle());
          OS_ASSERT(ok);
        }
      }
    }

    unsigned LayeredConstruction_Impl::mf_clearNullLayers(unsigned layerIndex) {
      std::vector<unsigned> indices = nullLayers();
      for (int i = static_cast<int>(indices.size()) - 1; i >= 0; --i) {
        unsigned index = indices[i];
        StringVector eraseResult = eraseExtensibleGroup(index);
        OS_ASSERT(!eraseResult.empty());
        if (layerIndex > index) {
          --layerIndex;
        }
      }
      return layerIndex;
    }

  }  // namespace detail

  LayeredConstruction::LayeredConstruction(IddObjectType type, const Model& model) : ConstructionBase(type, model) {}

  LayeredConstruction::LayeredConstruction(std::shared_ptr<detail::LayeredConstruction_Impl> impl) : ConstructionBase(std::move(impl)) {}

  bool LayeredConstruction::layersAreValid(const std::vector<Material>& materials) {
    if (materials.empty()) {
      return false;
    }

    if (materials[0].optionalCast<OpaqueMaterial>()) {
      std::vector<OpaqueMaterial> opaqueMaterials;
      for (const Material& material : materials) {
        if (!material.optionalCast<OpaqueMaterial>()) {
          LOG(Info, "Not all materials can be converted to OpaqueMaterial.");
          return false;
        }
        opaqueMaterials.push_back(material.cast<OpaqueMaterial>());
      }
      return layersAreValid(opaqueMaterials);
    }

    if (materials[0].optionalCast<FenestrationMaterial>()) {
      std::vector<FenestrationMaterial> fenestrationMaterials;
      for (const Material& material : materials) {
        if (!material.optionalCast<FenestrationMaterial>()) {
          LOG(Info, "Not all materials can be converted to FenestrationMaterial.");
          return false;
        }
        fenestrationMaterials.push_back(material.cast<FenestrationMaterial>());
      }
      return layersAreValid(fenestrationMaterials);
    }

    return false;
  }

  bool LayeredConstruction::layersAreValid(const std::vector<OpaqueMaterial>& opaqueMaterials) {
    // Rule 1: AirGap must have non-AirGap on either side.
    // Rule 2: RoofVegetation must be on exterior layer.
    // Rule 3: Up to 10 layers are allowed.
    if (opaqueMaterials.size() > 10) {
      return false;
    }

    bool previousWasNonAirGap = false;
    for (unsigned i = 0, n = opaqueMaterials.size(); i < n; ++i) {
      if (opaqueMaterials[i].optionalCast<AirGap>()) {
        if (!previousWasNonAirGap) {
          LOG(Info, "Proposed OpaqueMaterials are invalid because an AirGap at layer "
                      << i << " either starts the construction, or is preceded by another AirGap.");
          return false;
        }
        previousWasNonAirGap = false;
      } else {
        previousWasNonAirGap = true;
      }
      if (opaqueMaterials[i].optionalCast<RoofVegetation>() && (i > 0)) {
        LOG(Info, "Proposed OpaqueMaterials are invalid because RoofVegetation must be at layer 0, not layer " << i << ".");
        return false;
      }
    }

    if ((!opaqueMaterials.empty()) && (!previousWasNonAirGap)) {
      LOG(Info,
          "Proposed OpaqueMaterials are invalid because an AirGap at layer " << opaqueMaterials.size() << " is the last layer in the construction.");
      return false;
    }

    return true;
  }

  bool LayeredConstruction::layersAreValid(const std::vector<FenestrationMaterial>& fenestrationMaterials) {
    // Rule 1: SimpleGlazing cannot be combined with other Glazings or any GasLayers.
    // Rule 2: GasLayers must have non-GasLayer on either side.
    // Rule 3: GasLayers must have Glazing on either side.
    // Rule 4: Up to 8 layers are allowed.
    if (fenestrationMaterials.size() > 8) {
      return false;
    }

    bool hasSimpleGlazing = false;
    bool hasGlazing = false;
    bool hasGasLayer = false;
    bool previousWasNonGasLayer = false;
    bool gasLayerEnclosed = true;

    for (const auto& fm : fenestrationMaterials) {
      bool isGlazing = fm.optionalCast<Glazing>().has_value();
      bool isSimpleGlazing = fm.optionalCast<SimpleGlazing>().has_value();
      bool isGasLayer = fm.optionalCast<GasLayer>().has_value();

      if (isSimpleGlazing) {
        if (hasGlazing || hasGasLayer) {
          return false;
        }
        hasSimpleGlazing = true;
        hasGlazing = true;
      }
      if (isGlazing && !isSimpleGlazing && hasSimpleGlazing) {
        return false;
      }
      if (isGasLayer && hasSimpleGlazing) {
        return false;
      }
      if (isGasLayer) {
        if (!previousWasNonGasLayer || !hasGlazing) {
          return false;
        }
        hasGasLayer = true;
        previousWasNonGasLayer = false;
        gasLayerEnclosed = false;
      } else {
        previousWasNonGasLayer = true;
      }
      if (isGlazing) {
        hasGlazing = true;
        gasLayerEnclosed = true;
      }
    }

    if ((!fenestrationMaterials.empty()) && (!previousWasNonGasLayer)) {
      return false;
    }
    if (!gasLayerEnclosed) {
      return false;
    }

    return true;
  }

  std::vector<Material> LayeredConstruction::layers() const {
    return getImpl<detail::LayeredConstruction_Impl>()->layers();
  }

  Material LayeredConstruction::getLayer(unsigned layerIndex) const {
    return getImpl<detail::LayeredConstruction_Impl>()->getLayer(layerIndex);
  }

  bool LayeredConstruction::eraseLayer(unsigned layerIndex) {
    return getImpl<detail::LayeredConstruction_Impl>()->eraseLayer(layerIndex);
  }

  bool LayeredConstruction::insertLayer(unsigned layerIndex, const Material& material) {
    return getImpl<detail::LayeredConstruction_Impl>()->insertLayer(layerIndex, material);
  }

  bool LayeredConstruction::setLayer(unsigned layerIndex, const Material& material) {
    return getImpl<detail::LayeredConstruction_Impl>()->setLayer(layerIndex, material);
  }

  bool LayeredConstruction::setLayers(const std::vector<Material>& materials) {
    return getImpl<detail::LayeredConstruction_Impl>()->setLayers(materials);
  }

  std::vector<unsigned> LayeredConstruction::nullLayers() const {
    return getImpl<detail::LayeredConstruction_Impl>()->nullLayers();
  }

  unsigned LayeredConstruction::numLayers() const {
    return getImpl<detail::LayeredConstruction_Impl>()->numLayers();
  }

  std::vector<unsigned> LayeredConstruction::getLayerIndices(const Material& material) const {
    return getImpl<detail::LayeredConstruction_Impl>()->getLayerIndices(material);
  }

  void LayeredConstruction::ensureUniqueLayers() {
    getImpl<detail::LayeredConstruction_Impl>()->ensureUniqueLayers();
  }

}  // namespace epmodel
}  // namespace openstudio
