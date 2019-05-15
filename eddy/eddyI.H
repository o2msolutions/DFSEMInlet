// Backport of turbulentDFSEMInlet BC to OpenFOAM 5.x
// Copyright (C) 2015 OpenFOAM Foundation
// Copyright (C) 2016-2017 OpenCFD Ltd.
// Copyright (C) 2019 Alexey Matveichev
// License: GPLv3

#include "mathematicalConstants.H"

using namespace Foam::constant;

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

Foam::scalar Foam::eddy::epsi(Random& rndGen) const
{
    // Random number with zero mean and unit variance
    return rndGen.scalar01() > 0.5 ? 1 : -1;
}


inline Foam::label Foam::eddy::patchFaceI() const
{
    return patchFaceI_;
}


inline const Foam::point& Foam::eddy::position0() const
{
    return position0_;
}


inline Foam::scalar Foam::eddy::x() const
{
    return x_;
}


inline const Foam::vector& Foam::eddy::sigma() const
{
    return sigma_;
}


inline const Foam::vector& Foam::eddy::alpha() const
{
    return alpha_;
}


inline const Foam::tensor& Foam::eddy::Rpg() const
{
    return Rpg_;
}


inline Foam::point Foam::eddy::position(const vector& n) const
{
    return position0_ + n*x_;
}


inline Foam::scalar Foam::eddy::c1() const
{
    return c1_;
}


Foam::vector Foam::eddy::epsilon(Random& rndGen) const
{
    return vector(epsi(rndGen), epsi(rndGen), epsi(rndGen));
}


inline Foam::scalar Foam::eddy::volume() const
{
    return mathematical::pi*4.0/3.0*cmptProduct(sigma_);
}


void Foam::eddy::move(const scalar dx)
{
    x_ += dx;
}


Foam::boundBox Foam::eddy::bounds(const bool global) const
{
    boundBox bb;

    if (global)
    {
        bb.min() = Rpg_ & -sigma_;
        bb.max() = Rpg_ & sigma_;
    }
    else
    {
        bb.min() = -sigma_;
        bb.max() = sigma_;
    }

    return bb;
}


// ************************************************************************* //
