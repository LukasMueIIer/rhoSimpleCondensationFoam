# rhoSimpleCondensationFoam
A solver that is built upon rhoSimpleFoam.
The goal is to obtain the capability to simulate the condensation of jet engine exhausts in the atmosphere.

The approach is very "engineering" based. The goal is to have fast and reasonably accurate results.

Developed on Foam v2406

## gridCondensationExtract
is a custom postProcessing utility intended to write condensation related field values on a uniform grid. 
They are output as a csv file that can be read with panda.
Additional fields can easily be added by simply appending the createFields file.


## Example Cases
These cases are used during development of the solver and later on to guide case creation.
They are set up based on python scripts. Therefore to run them a python environment is needed which contains:
PyFoam
classy_blocks
FoamFunctions