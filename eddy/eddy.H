// Backport of turbulentDFSEMInlet BC to OpenFOAM 5.x
// Copyright (C) 2015 OpenFOAM Foundation
// Copyright (C) 2016-2017 OpenCFD Ltd.
// Copyright (C) 2019 Alexey Matveichev
// License: GPLv3
// Class
//     Foam::eddy
// 
// Description
//     Class to describe eddies for the turbulentDFSEMInletFvPatchVectorField
//     boundary condition.

#ifndef turbulentDFSEMInletFvPatchVectorField_eddy_H
#define turbulentDFSEMInletFvPatchVectorField_eddy_H

#include "vector.H"
#include "point.H"
#include "tensor.H"
#include "Random.H"
#include "boundBox.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// Forward declarations
class eddy;
class Istream;
class Ostream;

bool operator==(const eddy& a, const eddy& b);
bool operator!=(const eddy& a, const eddy& b);
Istream& operator>>(Istream& is, eddy& e);
Ostream& operator<<(Ostream& os, const eddy& e);


/*---------------------------------------------------------------------------*\
                            Class eddy Declaration
\*---------------------------------------------------------------------------*/

class eddy
{
    // Private data

        static label Gamma2Values[8];
        static UList<label> Gamma2;

        //- Patch face index that spawned the eddy
        label patchFaceI_;

        //- Reference position
        point position0_;

        //- Distance from reference position in normal direction
        scalar x_;

        //- Length scales in 3-D space
        vector sigma_;

        //- Time-averaged intensity
        vector alpha_;

        //- Coordinate system transformation from local to global axes
        //  X-direction aligned with max stress eigenvalue
        tensor Rpg_;

        //- Model coefficient c1
        scalar c1_;

        //- Index of streamwise direction
        label dir1_;


    // Private Member Functions

        //- Set the eddy scales: length, intensity
        bool setScales
        (
            const scalar sigmaX,
            const label gamma2,
            const vector& e,
            const vector& lambda,
            vector& sigma,
            vector& alpha
        ) const;

        //- Return a number with zero mean and unit variance
        inline scalar epsi(Random& rndGen) const;


public:

    // Constructors

        //- Construct null
        eddy();

        //- Construct from Istream
        eddy(Istream& is);

        //- Construct from components
        eddy
        (
            const label patchFaceI,     // patch face index
            const point& position0,     // reference position
            const scalar x,             // distance from reference position
            const scalar sigmaX,        // length scale
            const symmTensor& R,        // Stress tensor
            Random& rndGen
        );

        //- Construct copy
        eddy(const eddy& e);

        static int debug;


    // Public Member Functions

        // Access

            //- Return the patch face index that spawned the eddy
            inline label patchFaceI() const;

            //- Return the reference position
            inline const point& position0() const;

            //- Return the distance from the reference position
            inline scalar x() const;

            //- Return the lLength scales in 3-D space
            inline const vector& sigma() const;

            //- Return the time-averaged intensity
            inline const vector& alpha() const;

            //- Return the coordinate system transformation from local
            //  principal to global axes
            inline const tensor& Rpg() const;

            //- Return the model coefficient c1
            inline scalar c1() const;

            //- Return the eddy position
            inline point position(const vector& n) const;

            //- Return the index of the streamwise direction
            inline label dir1() const;

            //- Return random vector of -1 and 1's
            inline vector epsilon(Random& rndGen) const;


        // Helper functions

            //- Volume
            inline scalar volume() const;

            //- Move the eddy
            inline void move(const scalar dx);

            //- Eddy bounds
            inline boundBox bounds(const bool global = true) const;


        // Evaluate

            //- Return the fluctuating velocity contribution at local point xp
            vector uDash(const point& xp, const vector& n) const;


        // Writing

            //- Write the eddy centre in OBJ format
            void writeCentreOBJ(const vector& n, Ostream& os) const;

            //- Write the eddy surface in OBJ format
            //  Returns the number of points used to describe the eddy surface
            label writeSurfaceOBJ
            (
                const label pointOffset,
                const vector& n,
                Ostream& os
            ) const;


    // Member Operators

        void operator=(const eddy& e);


    // Friend Operators

        friend bool operator==(const eddy& a, const eddy& b)
        {
            return
                a.patchFaceI_ == b.patchFaceI_
             && a.position0_ == b.position0_
             && a.x_ == b.x_
             && a.sigma_ == b.sigma_
             && a.alpha_ == b.alpha_
             && a.Rpg_ == b.Rpg_
             && a.c1_ == b.c1_
             && a.dir1_ == b.dir1_;
        }

        friend bool operator!=(const eddy& a, const eddy& b)
        {
            return !(a == b);
        }


    // IOstream Operators

        friend Istream& operator>>(Istream& is, eddy& e);
        friend Ostream& operator<<(Ostream& os, const eddy& e);
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "eddyI.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
