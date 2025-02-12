//Effective Diffusivity
volScalarField DEff
(
    IOobject
    (
        "DEff",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::NO_WRITE
    ),
    (turbulence->nut()/0.7) + (dimensionedScalar("D",dimViscosity,2.19E-5)) //Hand Calculated diffusivity
);


fvScalarMatrix transportVapour
(
    fvm::div(phi, chiVapour) - fvm::laplacian(DEff * rho, chiVapour)
);

transportVapour.relax();

transportVapour.solve();

fvOptions.correct(chiVapour);
