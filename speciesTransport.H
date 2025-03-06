Info << "Calculating Species Transport " << nl << endl;
//Calculate the Effective Diffusivity for the vapour
volScalarField DEff
(
    (turbulence->nut() / PrtVapourH2O) + (DVapourH2O) //Hand Calculated diffusivity
);

//solve vapour transport equation
fvScalarMatrix transportVapourH2O
(
    fvm::div(phi, vapourH2O) - fvm::laplacian(DEff * rho, vapourH2O)
);

transportVapourH2O.relax();

transportVapourH2O.solve();

fvOptions.correct(vapourH2O);

Info << vapourH2O;

//Calculate the air fraction so we summ up to 1, correct any fraction that has a negative value
forAll(mesh.C(),cellID)
{
    if(neg(vapourH2O[cellID]))
    {
        vapourH2O[cellID] = scalar(0.);
    }
    air[cellID] = scalar(1.); // - vapourH2O[cellID];
}
    
Info << air << endl;
