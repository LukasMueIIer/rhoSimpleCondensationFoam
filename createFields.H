Info<< "Reading thermophysical properties\n" << endl;

autoPtr<fluidThermo> pThermo
(
    fluidThermo::New(mesh)
);
fluidThermo& thermo = pThermo();
thermo.validate(args.executable(), "h", "e");

volScalarField& p = thermo.p();

volScalarField rho
(
    IOobject
    (
        "rho",
        runTime.timeName(),
        mesh,
        IOobject::READ_IF_PRESENT,
        IOobject::AUTO_WRITE
    ),
    thermo.rho()
);

Info<< "Reading field U\n" << endl;
volVectorField U
(
    IOobject
    (
        "U",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

#include "compressibleCreatePhi.H"

pressureControl pressureControl(p, rho, simple.dict());

mesh.setFluxRequired(p.name());

Info<< "Creating turbulence model\n" << endl;
autoPtr<compressible::turbulenceModel> turbulence
(
    compressible::turbulenceModel::New
    (
        rho,
        U,
        phi,
        thermo
    )
);

dimensionedScalar initialMass = fvc::domainIntegrate(rho);

Info<< "Createing Water Vapour Mass Fraction Field" << nl << endl;

volScalarField chiVapour
(
    IOobject
    (
        "chiVapour",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

volScalarField& T = thermo.T();

dimensionedScalar fracT("fractTvapour",dimTemperature,373.16); //A often used Temperature value for the calculation of saturation pressure

volScalarField pSaturationVapour
(
    IOobject
    (
        "pSaturationVapour",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    pow(-7.90298*(fracT/T-1) 
    +  5.02808 * log10(fracT/T)
    - 1.3816e-7 * (pow(10,11.344*(1-T/fracT)) - 1)
    + 8.1328e-3 * (pow(10,-3.49149*(fracT/T-1) ) - 1) 
    + log10(dimensionedScalar(dimless,1013.246)) ,10) * dimensionedScalar("pressureFactor",dimPressure,1000)
);

dimensionedScalar RVapour("RVapour",dimGasConstant,461.6); //Specific Gas Konstant of the Water Vapour Phase 

Info << "Creating Vapour Pressure Field" << nl << endl;
volScalarField pVapour
(
    IOobject
    (
        "pVapour",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    rho * chiVapour * RVapour * T
);

Info << "Creating saturation Field" << nl << endl;

volScalarField satVapour
(
    IOobject
    (
        "satVapour",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    pVapour / pSaturationVapour
);
#include "createMRF.H"
#include "createFvOptions.H"
