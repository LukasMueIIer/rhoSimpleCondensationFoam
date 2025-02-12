//Water Vapour Properties

scalar PrtVapour(0.7); //Turbulent Prandtl number

dimensionedScalar DVapour("DVapour",dimViscosity,2.19E-5); //diffusivity for fricks law



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
    (turbulence->nut()/PrtVapour) + (DVapour) //Hand Calculated diffusivity
);



fvScalarMatrix transportVapour
(
    fvm::div(phi, chiVapour) - fvm::laplacian(DEff * rho, chiVapour)
);

transportVapour.relax();

transportVapour.solve();

fvOptions.correct(chiVapour);

//calculate local saturation

//Update Saturation Pressure
Info << "Updating Saturation pressures " << nl << endl;
pSaturationVapour = 
pow(-7.90298*(fracT/T-1) 
+  5.02808 * log10(fracT/T)
- 1.3816e-7 * (pow(10,11.344*(1-T/fracT)) - 1)
+ 8.1328e-3 * (pow(10,-3.49149*(fracT/T-1) ) - 1) 
+ log10(dimensionedScalar(dimless,1013.246)) ,10) * dimensionedScalar("pressureFactor",dimPressure,1000);

//Update Vapour Pressure

Info << "Updating Vapour Pressures" << nl << endl;

pVapour = rho * chiVapour * RVapour * T;

//Update Saturation

Info << "Updating Saturations" << nl << endl;

satVapour = pVapour / pSaturationVapour;
