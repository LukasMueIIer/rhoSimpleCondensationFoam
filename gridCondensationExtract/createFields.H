//All fields that are loaded here are then also written into the dicionary
//dont forget to append the field to the fieldList

List<volScalarField*> fieldList;

Info << "Reading fields from latest timestep ..." << nl << endl;

Info << "Reading T field ..." << endl;

volScalarField T
(
    IOobject
    (
        "T",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::NO_WRITE
    ),
    mesh
);

fieldList.append(&T);

Info << "Reading pVapour field ..." << endl;

volScalarField pVapour
(
    IOobject
    (
        "pVapour",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::NO_WRITE
    ),
    mesh
);

fieldList.append(&pVapour);

Info << "Reading pSaturationWater field ..." << endl;

volScalarField pSaturationWater
(
    IOobject
    (
        "pSaturationWater",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::NO_WRITE
    ),
    mesh
);

fieldList.append(&pSaturationWater);

Info << "Reading satWater field ..." << endl;

volScalarField satWater
(
    IOobject
    (
        "satWater",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::NO_WRITE
    ),
    mesh
);

fieldList.append(&satWater);

