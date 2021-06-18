# DFSEMInlet

Backport of turbulentDFSEMInlet BC from OpenFOAM(R) v1812 to OpenFOAM 5.x.

## Jun. 18, 2021

After bug report(s) and email message decided to add this paragraphe here. If we take a look at `turbulentDFSEMInletFvPatchVectorField.H`, in the header comment there is a table:


| Property | Description | Required | Default value |
|---|---|---|--|
| `value` | Restart value | yes |
| `delta` | Local limiting length scale  | yes |
| `R` | Reynolds stress field | no |
| `U` | Velocity field | no |
| `L` | Turbulence length scale field | no |
| `d` | Eddy density(fill fraction) | no | 1 |
| `kappa` | Von Karman constant | no | 0.41 |
| `mapMethod` | Method to map reference values | no | `planarInterpolation` |
| `perturb`   | Point perturbation for interpolation | no | 1e-5 |
| `writeEddies` | Flag to write eddies as OBJ file | no | no |

No in Required column of `R`, `U`, and `L` can be a bit misleading. They are, in fact, required but can be supplied in two ways:

- As a single value in B.C. dictionary
- As an interpolated values in `constant/boundaryData/<patch name>/0/<field name>`. Interpolated value usually are taken from another simulation outlet. Format of input files for interpolation can be found in the following tutorials:
  ```
  $ find . -name 'boundaryData'
  ./incompressible/pimpleFoam/LES/channel395DFSEM/constant/boundaryData
  ./incompressible/simpleFoam/pitzDailyExptInlet/constant/boundaryData
  ./verificationAndValidation/atmosphericModels/atmFlatTerrain/successor/constant/boundaryData
  ./verificationAndValidation/turbulentInflow/PCF/constant/boundaryData
  ```

## Disclamer

This offering is not approved or endorsed by OpenCFD Limited, producer and
distributor of the OpenFOAM software via www.openfoam.com, and owner of the
OPENFOAM(R)  and OpenCFD(R)  trade marks.

## Acknowledgement

OPENFOAM(R)  is a registered trade mark of OpenCFD Limited, producer and
distributor of the OpenFOAM software via www.openfoam.com.
