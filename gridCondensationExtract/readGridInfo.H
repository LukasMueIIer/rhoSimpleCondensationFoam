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

//Reading the tables
HashTable<vector,word> gridShape(gridInfo.lookup("gridShape"));

HashTable<label,word> gridResolution(gridInfo.lookup("gridResolution"));

//setting up variables for later use
Info << "Succesfully read dictionary " << nl << endl;

vector origin(gridShape["origin"]);
Info << "Grid origin at " << origin << endl;

vector direction1(gridShape["direction1"]);
Info << "Extending in direction " << direction1 << endl;

vector direction2(gridShape["direction2"]);
Info << "And also in direction " << direction2 << endl;

label stepsDirection1(gridResolution["stepsDirection1"]);
label stepsDirection2(gridResolution["stepsDirection2"]);

Info << "With a resolution of " << stepsDirection1 << " steps in first direction" << endl;
Info << "and " << stepsDirection2 << " steps in the second direction" << endl;
