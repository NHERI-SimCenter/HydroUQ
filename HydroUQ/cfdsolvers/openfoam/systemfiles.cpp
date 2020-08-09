//*********************************************************************************
// Include user headers
//*********************************************************************************
#include "openfoam.h"

//*********************************************************************************
//Generate system files related to OpenFOAM
//*********************************************************************************
void openfoam::fvSchemegen(QDir systdirs)
{
    // Create teh fvSchemes file
    QFile fvscheme(systdirs.filePath("fvSchemes"));
    if(!fvscheme.open(QIODevice::ReadWrite))
    {
        //qDebug() << "File open error";
    }
    else
    {
        // Clear the original file content
        fvscheme.resize(0);

        // Create a text stream and start writing
        QTextStream stream(&fvscheme);

        // Add header
        stream << "FoamFile\n";
        stream << "{\tversion\t2.0;\n\tformat\tascii;\n\tclass\tdictionary;";
        stream << "\n\tlocation\t\"system\";\n\tobject\tfvSchemes;\n}\n\n";

        //ddt Schemes
        stream << "ddtSchemes\n";
        stream << "{\n\tdefault\tGauss linear;\n}\n\n";

        // grad Schemes
        stream << "gradSchemes\n";
        stream << "{\n\tdefault\tGauss linear;\n}\n\n";

        // div Schemes
        stream << "divSchemes\n";
        stream << "{\n\tdiv(rhoPhi,U)\tGauss linearUpwind grad(U);\n";
        stream << "\tdiv(phi,alpha)\tGauss vanLeer;\n";
        stream << "\tdiv(phirb,alpha)\tGauss linear;\n";
        stream << "\tdiv(phi,k)\tGauss upwind;\n";
        stream << "\tdiv(phi,omega)\tGauss upwind;\n\n";
        stream << "\tdiv(((rho*nuEff)*dev2(T(grad(U)))))\tGauss linear;\n}\n\n";

        // laplacian Schemes
        stream << "laplacianSchemes\n";
        stream << "{\n\tdefault\tGauss linear corrected;\n}\n\n";

        // interpolation Schemes
        stream << "interpolationSchemes\n";
        stream << "{\n\tdefault\tlinear;\n}\n\n";

        // snGrad Schemes
        stream << "snGradSchemes\n";
        stream << "{\n\tdefault\tcorrected;\n}\n\n";

        // wallDist
        stream << "wallDist\n";
        stream << "{\n\tmethod\tmeshWave;\n}\n\n";

    }
}
