# EPModel scaffold directory

This directory originally held generated EnergyPlus wrappers. Some are still
minimal generated classes; others now have factory registration, tests, and
working HVAC behavior. The directory name no longer tells you whether a class
is ready to use.

Check the class header, implementation, factory registration, bindings, and
tests before depending on one of these wrappers.

When finishing a generated wrapper:

- identify the corresponding Model class, if there is one;
- decide which EnergyPlus object owns each reference;
- implement loading, repair, removal, and child ownership as needed;
- document important differences in the public header;
- add focused tests; and
- add Ruby/Python bindings only when the public API is ready.

The old generated Model-to-EnergyPlus mapping report is no longer maintained.
