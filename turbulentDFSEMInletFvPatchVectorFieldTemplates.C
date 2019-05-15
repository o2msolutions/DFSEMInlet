// Backport of turbulentDFSEMInlet BC to OpenFOAM 5.x
// Copyright (C) 2015 OpenFOAM Foundation
// Copyright (C) 2016-2017 OpenCFD Ltd.
// Copyright (C) 2019 Alexey Matveichev
// License: GPLv3

#include "pointToPointPlanarInterpolation.H"
#include "Time.H"
#include "IFstream.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class Type>
Foam::tmp<Foam::Field<Type>>
Foam::turbulentDFSEMInletFvPatchVectorField::interpolateOrRead
(
    const Foam::word& fieldName,
    const Foam::dictionary& dict,
    bool& interpolateField
) const
{
    if (dict.found(fieldName))
    {
        Foam::tmp<Foam::Field<Type>> tFld
        (
            new Foam::Field<Type>
            (
                fieldName,
                dict,
                this->patch().size()
            )
        );

        interpolateField = false;
        return tFld;
    }
    else
    {
        interpolateField = true;
        return interpolateBoundaryData<Type>(fieldName);
    }
}


template<class Type>
Foam::tmp<Foam::Field<Type>>
Foam::turbulentDFSEMInletFvPatchVectorField::interpolateBoundaryData
(
    const word& fieldName
) const
{
    const word& patchName = this->patch().name();

    fileName valsFile
    (
        fileHandler().filePath
        (
            fileName
            (
                this->db().time().path()
               /this->db().time().caseConstant()
               /"boundaryData"
               /patchName
               /"0"
               /fieldName
            )
        )
    );

    autoPtr<ISstream> isPtr
    (
        fileHandler().NewIFstream
        (
            valsFile
        )
    );

    Field<Type> vals(isPtr());

    Info<< "Turbulent DFSEM patch " << patchName
        << ": interpolating field " << fieldName
        << " from " << valsFile << endl;

    return patchMapper().interpolate(vals);
}


// ************************************************************************* //
