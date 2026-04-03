# IDD Schema Alignment Docs

This directory collects supporting references for the broader OpenStudio to
EnergyPlus schema-alignment effort.

It is intentionally not the live epmodel status or work queue.

Use these instead:

- `src/epmodel/README.md` for durable epmodel architecture and behavior notes
- `src/epmodel/AGENTS.md` for epmodel implementation guidance
- `.opencode/hvac-parity-docs/hvac-api-roadmap.md` for active HVAC parity
  status, queue order, and next steps

## Directory Index

- `os_hvac_concepts.md`
  Canonical `openstudio::model` HVAC topology concepts and patterns.
- `idd_mapping.md`
  High-level OpenStudio IDD to EnergyPlus IDD mapping summary.
- `idd_mapping_appendix.generated.md`
  Machine-generated full inventory tables with translator evidence.
- `os_idd_object_relationships.md`
  HVAC-focused object-list relationship inventory derived from
  `OpenStudio.idd`.
- `InputOutputReference.pdf`
  EnergyPlus field-semantics reference.
- `scripts/generate_os_idd_object_relationships.py`
  Regenerates `os_idd_object_relationships.md`.

## Key External Schema Files

- `../../resources/model/OpenStudio.idd`
- `../../resources/energyplus/ProposedEnergy+.idd`
