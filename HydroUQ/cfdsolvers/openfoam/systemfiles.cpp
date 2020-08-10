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

        // Close the file
        fvscheme.close();
    }
}

//*********************************************************************************
//Generate fvSolution file for OpenFOAM
//*********************************************************************************
void openfoam::fvSolutiongen(QDir systdirs)
{
    // Create teh fvSchemes file
    QFile fvsolution(systdirs.filePath("fvSolution"));
    if(!fvsolution.open(QIODevice::ReadWrite))
    {
        //qDebug() << "File open error";
    }
    else
    {
        // Clear the original file content
        fvsolution.resize(0);

        // Create a text stream and start writing
        QTextStream stream(&fvsolution);

        // Add header
        stream << "FoamFile\n";
        stream << "{\tversion\t2.0;\n\tformat\tascii;\n\tclass\tdictionary;";
        stream << "\n\tlocation\t\"system\";\n\tobject\tfvSolution;\n}\n\n";

        // Add solvers
        stream << "solvers\n{\n";

        // For Alpha
        stream << "\t\"alpha.water.*\"\n\t{\n\t\t";
        stream << "nAlphaCorr\t1;\n\t\t";
        stream << "nAlphaSubCycles\t1;\n\t\t";
        stream << "ncAlpha\t1;\n\t\t";
        stream << "nMULESCorr\tyes;\n\t\t";
        stream << "nnLimiterIter\t3;\n\t\t";
        stream << "solver\tsmoothSolver;\n\t\t";
        stream << "smoother\tsymGaussSeidel;\n\t\t";
        stream << "tolerance\t1e-8;\n\t\t";
        stream << "relTol\t0;\n\t}\n\n";

        // pcorr
        stream << "\tpcorr\n\t{\n\t\t";
        stream << "solver\tPCG;\n\t\t";
        stream << "preconditioner\n\t\t{\n\t\t\t";
        stream << "preconditioner\tGAMG;\n\t\t\t";
        stream << "tolerance\t1e-5;\n\t\t\t";
        stream << "relTol\t0;\n\t\t\t";
        stream << "smoother\tGaussSeidel;\n\t\t\t";
        stream << "nPreSweeps\t0;\n\t\t\t";
        stream << "nPostSweeps\t2;\n\t\t\t";
        stream << "nFinestSweeps\t2;\n\t\t\t";
        stream << "cacheAgglomeration\ttrue;\n\t\t\t";
        stream << "nCellsInCoarsestLevel\t10;\n\t\t\t";
        stream << "agglomerator\tfaceAreaPair;\n\t\t\t";
        stream << "mergeLevels\t1;\n";
        stream << "\t\t}\n\t\t";
        stream << "tolerance\t1e-5;\n\t\t";
        stream << "relTol\t0;\n\t\t";
        stream << "maxIter\t50;\n\t}\n\n";

        // For p_rgh
        stream << "\tp_rgh\n\t{\n\t\t";
        stream << "solver\tGAMG;\n\t\t";
        stream << "tolerance\t5e-9;\n\t\t";
        stream << "relTol\t0.01;\n\t\t";
        stream << "smoother\tsymGaussSeidel;\n\t\t";
        stream << "nPreSweeps\t0;\n\t\t";
        stream << "nPostSweeps\t2;\n\t\t";
        stream << "cacheAgglomeration\ttrue;\n\t\t";
        stream << "nCellsInCoarsestLevel\t10;\n\t\t";
        stream << "agglomerator\tfaceAreaPair;\n\t\t";
        stream << "mergeLevels\t1;\n\t\t";
        stream << "maxIter\t50;\n\t};\n\n";

        // For p_rghFinal
        stream << "\tp_rghFinal\n\t{\n\t\t";
        stream << "$p_rgh;\n\t\t";
        stream << "tolerance\t5e-9;\n\t\t";
        stream << "relTol\t0;\n\t}\n\n";

        // For pcorrFinal
        stream << "\tpcorrFinal\n\t{\n\t\t";
        stream << "$pcorr;\n\t\t";
        stream << "tolerance\t5e-9;\n\t\t";
        stream << "relTol\t0;\n\t}\n\n";

        // For U|k|omega
        stream << "\t\"(U|k|omega).*\"\n\t{\n\t\t";
        stream << "solver\tsmoothSolver;\n\t\t";
        stream << "smoother\tsymGaussSeidel;\n\t\t";
        stream << "nSweeps\t1;\n\t\t";
        stream << "tolerance\t1e-6;\n\t\t";
        stream << "relTol\t0.1;\n\t};\n}\n\n";

        // PIMPLE
        stream << "PIMPLE\n{\n\t";
        stream << "momentumPredictor\tno;\n\t";
        stream << "nCorrectors\t2;\n\t";
        stream << "nNonOrthogonalCorrectors\t0;\n}\n\n";

        // relaxationFactors
        stream << "relaxationFactors\n{\n\t";
        stream << "fields\n\t{\n\t}\n\t";
        stream << "\tequations\n\t{\n\t\t\".*\" 1;\n\t}\n}";

        // Close the file
        fvsolution.close();
    }
}

//*********************************************************************************
//Generate controlDict file for OpenFOAM
//*********************************************************************************
void openfoam::controldictgen(QDir systdirs,QStringList data)
{
    // Create teh fvSchemes file
    QFile controlDict(systdirs.filePath("controlDict"));
    if(!controlDict.open(QIODevice::ReadWrite))
    {
        //qDebug() << "File open error";
    }
    else
    {
        // Clear the original file content
        controlDict.resize(0);

        // Create a text stream and start writing
        QTextStream stream(&controlDict);

        // Add header
        stream << "FoamFile\n";
        stream << "{\tversion\t2.0;\n\tformat\tascii;\n\tclass\tdictionary;";
        stream << "\n\tlocation\t\"system\";\n\tobject\tcontrolDict;\n}\n\n";

        // Add information
        stream << "application\tinterFoam;\n\n";
        stream << "startFrom\tlatestTime;\n\n";
        stream << "startTime\t" << data[0] << ";\n\n";
        stream << "stopAt\tendTime;\n\n";
        stream << "endTime\t" << data[1] << ";\n\n";
        stream << "deltaT\t" << data[2] << ";\n\n";
        stream << "writeControl\tadjustableRunTime;\n\n";
        stream << "writeInterval\t" << data[3] << ";\n\n";
        stream << "purgeWrite\t0;\n\n";
        stream << "writeFormat\tascii;\n\n";
        stream << "writePrecision\6t;\n\n";
        stream << "writeCompression\tuncompressed;\n\n";
        stream << "timeFormat\tgeneral;\n\n";
        stream << "timePrecision\t6;\n\n";
        stream << "runTimeModifiable\tyes;\n\n";
        stream << "adjustTimeStep\tyes;\n\n";
        stream << "maxCo\t1.0;\n\n";
        stream << "maxAlphaCo\t1.0;\n\n";
        stream << "maxDeltaT\t1;\n\n";

        stream << "libs\n(\n\t\"libwaves.so\"\n)";

        // Close the file
        controlDict.close();
    }

}

//*********************************************************************************
//Generate decomposeParDict file for OpenFOAM
//*********************************************************************************
void openfoam::decomposepargen(QDir systdirs,QStringList data)
{
    // Create teh fvSchemes file
    QFile decomposeParDict(systdirs.filePath("decomposeParDict"));
    if(!decomposeParDict.open(QIODevice::ReadWrite))
    {
        //qDebug() << "File open error";
    }
    else
    {
        // Clear the original file content
        decomposeParDict.resize(0);

        // Create a text stream and start writing
        QTextStream stream(&decomposeParDict);

        // Add header
        stream << "FoamFile\n";
        stream << "{\tversion\t2.0;\n\tformat\tascii;\n\tclass\tdictionary;";
        stream << "\n\tlocation\t\"system\";\n\tobject\tdecomposeParDict;\n}\n\n";

        // Add information
        stream << "numberOfSubdomains\t" << data[1] << ";\n\n";
        stream << "method\t" << data[0] << ";\n\n";

        // Simple
        stream << "simpleCoeffs\n{\n\t";
        stream << "n\t(" << data[2] << " " << data[3] << " " << data[4] << ");\n\t";
        stream << "delta\t0.001;\n}\n\n";

        // Hierarchical
        stream << "hierarchicalCoeffs\n{\n\t";
        stream << "n\t(" << data[2] << " " << data[3] << " " << data[4] << ");\n\t";
        stream << "delta\t0.001;\n\t";
        stream << "order\txyz;\n}\n\n";

        // Close the file
        decomposeParDict.close();
    }

}

//*********************************************************************************
//Generate topoSetDict file for OpenFOAM: Creating buildings
//*********************************************************************************
void openfoam::toposetdictgen(QDir systdirs,QStringList data)
{
    // Create teh fvSchemes file
    QFile topoSetDict(systdirs.filePath("topoSetDict"));
    if(!topoSetDict.open(QIODevice::ReadWrite))
    {
        //qDebug() << "File open error";
    }
    else
    {
        // Clear the original file content
        topoSetDict.resize(0);

        // Create a text stream and start writing
        QTextStream stream(&topoSetDict);

        // Add header
        stream << "FoamFile\n";
        stream << "{\tversion\t2.0;\n\tformat\tascii;\n\tclass\tdictionary;";
        stream << "\n\tlocation\t\"system\";\n\tobject\ttopoSetDict;\n}\n\n";

        stream << "actions\n(\n\t{\n\t\t";
        stream << "name\tc0;\n\t\t";
        stream << "type\tcellSet;\n\t\t";
        stream << "action\tnew;\n\t\t";
        stream << "source\tboxToCell;\n\t\t";
        stream << "sourceInfo\n\t\t{\n";

        // Building data type
        int bdatatype = data[0].split(" ")[0].toInt();

        if(bdatatype == 1) // Parametric building definition
        {
            int nx = data[1].split(" ")[0].toInt();
            int ny = data[2].split(" ")[0].toInt();
            double dx = data[3].split(" ")[0].toDouble();
            double dy = data[4].split(" ")[0].toDouble();
            double dc = data[5].split(" ")[0].toDouble();
            double Ox = data[6].split(" ")[0].toDouble();
            double Oy = data[7].split(" ")[0].toDouble();
            int bdist = data[8].split(" ")[0].toInt();
            double bs = data[9].split(" ")[0].toDouble();

            //qDebug() << nx << ny << dx << dy << dc << Ox << Oy;

            Eigen::MatrixXf builddata(nx*ny,6);
            if(bdist == 1) // Simple building configuration
            {
                builddata = getbuilddatasimple(nx,ny,dx,dy,dc,Ox,Oy,bs);
                for(int ii=0; ii < nx*ny; ii++)
                {
                    stream << "\t\t\tbox (" << builddata(ii,0) << " "
                              << builddata(ii,1) << " "
                              << builddata(ii,2) << ")\t("
                              << builddata(ii,3) << " "
                              << builddata(ii,4) << " "
                              << builddata(ii,5) << ");\n";
                }
            }
            else if(bdist == 2) // Staggered building configuration
                stream << "This option is not yet available. "
                          "Contact developer for updates";

        }
        else if(bdatatype == 0) // Building from table
        {
            stream << "This option is not yet available";
        }

        stream << "\t\t}\n\t}\n\t{\n\t\t";
        stream << "name\tc0;\n\t\t";
        stream << "type\tcellSet;\n\t\t";
        stream << "action\tinvert;\n\t}\n);";

        // Close the file
        topoSetDict.close();
    }
}

//*********************************************************************************
// Generate building data
//*********************************************************************************
Eigen::MatrixXf openfoam::getbuilddatasimple(int nx, int ny,
                                       double dx, double dy, double dc,
                                       double Ox, double Oy, double bs)
{
    Eigen::MatrixXf builddata(nx*ny,6);
    double x1,x2,y1,y2;
    // Get coordinate of first building
    if(nx % 2 == 0) // Even number of buildings
    {
        x1 = Ox - ((nx/2)*(dx+bs));
        y1 = Oy + dc;
        x2 = x1 + bs;
        y2 = y1 + bs;
    }
    else // Odd number of buildings
    {
        x1 = Ox - ((nx*bs)/2.0 + (dx*(nx-1))/2.0);
        x2 = x1 + bs;
        y1 = Oy + dc;
        y2 = y1 + bs;
    }

    // Setup the coordinates of rest of the buildings
    int ll = 0;
    for(int ii = 1; ii <= nx; ii++)
    {
        for(int jj = 1; jj <= ny; jj++)
        {
            if((ii==1) && (jj==1))
            {
                // Set the first building
                builddata(0,0) = x1; builddata(0,1) = y1; builddata(0,2) = 0.0;
                builddata(0,3) = x2; builddata(0,4) = y2; builddata(0,5) = 0.0;
            }
            else
            {
                builddata(ll,0) = x1 + (ii-1)*(bs+dx);
                builddata(ll,1) = Oy + dc + ((jj-1)*(bs+dy));
                builddata(ll,2) = 0.0;
                builddata(ll,3) = builddata(ll,1) + bs;
                builddata(ll,4) = builddata(ll,2) + bs;
                builddata(ll,5) = bs;
            }
            ll = ll+1;
        }
    }

    return builddata;
}

//*********************************************************************************
//Generate decomposeParDict file for OpenFOAM
//*********************************************************************************
void openfoam::setFieldsDictgen(QDir systdirs,QStringList data)
{
    // Create teh fvSchemes file
    QFile setFieldsDict(systdirs.filePath("setFieldsDict"));
    if(!setFieldsDict.open(QIODevice::ReadWrite))
    {
        //qDebug() << "File open error";
    }
    else
    {
        // Clear the original file content
        setFieldsDict.resize(0);

        // Create a text stream and start writing
        QTextStream stream(&setFieldsDict);

        // Add header
        stream << "FoamFile\n";
        stream << "{\tversion\t2.0;\n\tformat\tascii;\n\tclass\tdictionary;";
        stream << "\n\tlocation\t\"system\";\n\tobject\tsetFieldsDict;\n}\n\n";

        // Add default field values
        stream << "defaultFieldValues\n(\n\t";
        stream << "volScalarFieldValue alpha.water " << data[0].split(" ")[0].toInt() << "\n\t";
        stream << "volScalarFieldValue p " << data[1] << "\n\t";
        stream << "volVectorFieldValue U (" << data[2] << " " << data[3] << " " << data[4] << ")";
        stream << "\n);\n\n";

        // Add regions

        // Close the file
        setFieldsDict.close();
    }
}
