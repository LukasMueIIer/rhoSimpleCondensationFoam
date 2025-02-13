# rhoSimpleCondensationFoam
A solver that is built upon rhoSimpleFoam.
The goal is to obtain the capability to simulate the condensation of jet engine exhausts in the atmosphere.

The approach is very "engineering" based. The goal is to have fast and reasonably accurate results.

Developed on Foam v2406

## gridCondensationExtract
is a custom postProcessing utility intended to write condensation related field values on a uniform grid. 
They are output in a foam dictionary, so they can be read with pyfoam and used for further post processing steps