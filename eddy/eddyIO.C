// Backport of turbulentDFSEMInlet BC to OpenFOAM 5.x
// Copyright (C) 2015 OpenFOAM Foundation
// Copyright (C) 2016-2017 OpenCFD Ltd.
// Copyright (C) 2019 Alexey Matveichev
// License: GPLv3

#include "eddy.H"
#include "IOstreams.H"

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::eddy::eddy(Istream& is)
:
    patchFaceI_(readLabel(is)),
    position0_(is),
    x_(readScalar(is)),
    sigma_(is),
    alpha_(is),
    Rpg_(is),
    c1_(readScalar(is)),
    dir1_(readLabel(is))
{
    is.check(FUNCTION_NAME);
}


// * * * * * * * * * * * * * * * * * Operators * * * * * * * * * * * * * * * //

void Foam::eddy::operator=(const eddy& e)
{
    patchFaceI_ = e.patchFaceI_;
    position0_ = e.position0_;
    x_ = e.x_;
    sigma_ = e.sigma_;
    alpha_ = e.alpha_;
    Rpg_ = e.Rpg_;
    c1_ = e.c1_;
    dir1_ = e.dir1_;
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

Foam::Istream& Foam::operator>>(Istream& is, eddy& e)
{
    is.check(FUNCTION_NAME);

    is  >> e.patchFaceI_
        >> e.position0_
        >> e.x_
        >> e.sigma_
        >> e.alpha_
        >> e.Rpg_
        >> e.c1_
        >> e.dir1_;

    is.check(FUNCTION_NAME);
    return is;
}


Foam::Ostream& Foam::operator<<(Ostream& os, const eddy& e)
{
    os.check(FUNCTION_NAME);

    os  << e.patchFaceI_ << token::SPACE
        << e.position0_ << token::SPACE
        << e.x_ << token::SPACE
        << e.sigma_ << token::SPACE
        << e.alpha_ << token::SPACE
        << e.Rpg_ << token::SPACE
        << e.c1_ << token::SPACE
        << e.dir1_;

    os.check(FUNCTION_NAME);
    return os;
}


// ************************************************************************* //
