E+ Scaffold ModelObjects
========================

This directory contains epmodel `ModelObject` types that are present as EnergyPlus IDD objects but are not produced by any `openstudio::model` object in the OpenStudio -> EnergyPlus mapping inventory and are not required by production epmodel topology or canonicalization code.

The classification is derived from `doc/idd-schema-alignment/idd_mapping.generated.md` by reversing the `EP IddObjectType(s) produced` column, not by comparing class names. Some OpenStudio model classes translate to differently named EnergyPlus objects, and those generated EnergyPlus outputs should stay with the main `ModelObject` sources.

These scaffold objects are candidates for expanding epmodel scope and EnergyPlus coverage as their relationships, canonicalization rules, and API surface become explicit.
