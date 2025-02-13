//read the information about the Grid we are supposed to probe
Info << nl << "Reading information of the grid to be probed ..." << nl << endl;

IOdictionary gridInfo
(
    IOobject
    (
        "gridCondensationExtractDict",
        runTime.system(),
        mesh,
        IOobject::MUST_READ,
        IOobject::NO_WRITE
    )
);

vector origin()