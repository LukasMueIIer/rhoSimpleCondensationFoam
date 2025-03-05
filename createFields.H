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

Info<< "Createing Air Mass Fraction Field" << nl << endl;

volScalarField air
(
    IOobject
    (
        "air",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

Info<< "Createing Water Vapour Mass Fraction Field" << nl << endl;

volScalarField vapourH2O
(
    IOobject
    (
        "vapourH2O",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

volScalarField& T = thermo.T();

Info<< "Creating Saturation Pressure Field wrt. liquid Water" << nl << endl;

dimensionedScalar fracT("fractTvapour",dimTemperature,373.16); //A often used Temperature value for the calculation of saturation pressure

volScalarField pSaturationWater
(
    IOobject
    (
        "pSaturationWater",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    pow(-7.90298 * ((fracT/T) - 1) 
    +  5.02808 * log10(fracT/T)
    - 1.3816e-7 * (pow(10,11.344*(1-T/fracT)) - 1)
    + 8.1328e-3 * (pow(10,-3.49149*(fracT/T-1) ) - 1) 
    + log10(dimensionedScalar(dimless,1013.246)) ,10) * dimensionedScalar("pressureFactor",dimPressure,100)
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
    rho * vapourH2O * RVapour * T
);

Info << "Creating saturation Field" << nl << endl;

volScalarField satWater
(
    IOobject
    (
        "satWater",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    pVapour / pSaturationWater
);

Info<< "Reading phase specific properties" << nl << endl;
//Read species properties

//First create the dictionaries
IOdictionary speciesThermoDict
(
    IOobject
    (
        "thermophysicalProperties",
        mesh.time().constant(),
        mesh,
        IOobject::MUST_READ
    )
);

IOdictionary speciesTransportDict
(
    IOobject
    (
        "transportProperties",
        mesh.time().constant(),
        mesh,
        IOobject::MUST_READ
    )
);


//now read the properties
dimensionedScalar DVapourH2O
(
    "DVapourH2O",
    //dimViscosity,
    speciesTransportDict.get<dimensionedScalar>
    (
        "DVapourH2O"
    )
); //Diffusivity for fricks law

scalar PrtVapourH2O
(
    speciesTransportDict.get<scalar>
    (
        "PrtVapourH2O"
    )
);


#include "createMRF.H"
#include "createFvOptions.H"
