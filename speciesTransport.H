
Info << "Calculating Species Transport " << nl << endl;
//Calculate the Effective Diffusivity for the vapour
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
    (turbulence->nut()/PrtVapourH2O) + (DVapourH2O) //Hand Calculated diffusivity
);

//solve vapour transport equation
fvScalarMatrix transportVapourH2O
(
    fvm::div(phi, vapourH2O) - fvm::laplacian(DEff * rho, vapourH2O)
);

transportVapourH2O.relax();

transportVapourH2O.solve();

fvOptions.correct(vapourH2O);


//Calculate the air fraction so we summ up to 1
air = 1;
air = air - vapourH2O;