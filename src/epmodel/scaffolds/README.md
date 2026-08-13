# EPModel scaffold objects

This directory is a historical source grouping for wrappers that began as
generated EnergyPlus-backed scaffolds. Some are still skeletal; others are
factory-registered, tested, and used by production EPModel topology. Directory
placement alone is therefore not an implementation-status signal.

A generated scaffold is a starting point, not an implementation-status claim.
It may have scalar accessors while still lacking the relationships,
canonicalization, ownership rules, lifecycle behavior, tests, and bindings
needed for normal use.

Promotion should be driven by a real API or workflow requirement. Before a
skeletal wrapper is treated as production-ready:

- identify any canonical `openstudio::model` counterpart and the behavior that
  must be preserved;
- identify its actual EnergyPlus owners and relationship fields;
- implement repair and lifecycle rules at the owning type;
- add type-local `Schema Alignment Notes` and focused tests; and
- add public bindings only when the wrapper is ready to expose.

Production references, factory registration, bindings, and tests are evidence
that a wrapper has been promoted. This directory does not depend on a
generated Model-to-EnergyPlus mapping report.
