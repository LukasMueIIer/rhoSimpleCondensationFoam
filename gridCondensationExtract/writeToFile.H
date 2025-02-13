//writing the results to an output dictionary

fileName outputDir = mesh.time().path()/"postProcessing"; //write results to postProcessing Folder

mkDir(outputDir);

autoPtr<OFstream> outputFilePtr;

outputFilePtr.reset(new OFstream(outputDir/"customOutputFile.dat"));


Info << "Printing fileheader " << nl << endl;
//print Header
outputFilePtr() << "x, y, z";
forAll(fieldList,fieldID){
    outputFilePtr() << ", " << fieldList[fieldID]->name();
};
outputFilePtr() << endl;



label cellCount = exportList[0].size();
Info << "Printing field data for " << cellCount << " cells..." << endl;
//write the data for each Cell
for(label i = 0; i < cellCount; ++i){

    bool first = true;
    forAll(exportList,exportID){
        //dont write the comma infront at first entry
        if(!first){
            outputFilePtr() << ", ";
        }else{
            first = false;
        }
        outputFilePtr() << exportList[exportID][i];
    }

    outputFilePtr() << endl;
}


