/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2025 AUTHOR,AFFILIATION
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Application
    gridCondensationExtract

Description
    This Application is used for Post Processing of rhoSimpleCondensationFoam runs.
    It extracts local values for Vapour Pressure, Temperature, saturation pressure wrt Water and saturation wrt Water

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{
    #include "setRootCase.H"
    #include "createTime.H"

    #include "createMesh.H"

    #include "createFields.H"

    #include "readGridInfo.H"

    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
    
    Info << "Looping over and extracting values " << nl << endl;

    for (label i = 0; i < stepsDirection1; ++i){
        for(label j = 0; j < stepsDirection2; ++j){
            vector cellPos = origin + scalar(i) * delta1 + scalar(j) * delta2; //Postition of the cell

            label cellID = mesh.findCell(cellPos);

            if(cellID == -1){ //check if the point is in the mesh
                Info << "WARNING!!! Probed point is outside of the mesh. Location " << cellPos << endl;
            }else{
                //Append Cordinates
                exportList[0].append(mesh.C()[cellID].x());
                exportList[1].append(mesh.C()[cellID].y());
                exportList[2].append(mesh.C()[cellID].z());

                //Append the remaining fields
                for (label n = 3; n < exportList.size(); ++n){
                    scalar cellValue = fieldList[n-3]->field()[cellID];
                    List<scalar>& fieldPointer = exportList[n];
                    fieldPointer.append(test); //append only the scalar value
                }
            }
        }
    }

    Info << "Done with value extraction" << nl << endl;

    Info << "Writing to File" << nl << endl;

    Info<< nl;
    runTime.printExecutionTime(Info);

    Info<< "End\n" << endl;

    return 0;
}


// ************************************************************************* //
