#include "LPSolver.hpp"
#include <boost/filesystem.hpp>
#include <sstream>
#include "../MapInitializer.hpp"
#include <base-logging/Logging.hpp>

#ifdef WITH_GLPK
#warning Using GLPK solver
#include "GLPKSolver.hpp"
#endif

#ifdef WITH_SCIP
#warning Using SCIP solver
#include "ScipSolver.hpp"
#endif

namespace graph_analysis {
namespace algorithms {

std::map<LPSolver::Type, std::string> LPSolver::TypeTxt =
    InitMap<LPSolver::Type, std::string>
    (LPSolver::UNKNOWN_LP_SOLVER, "UNKNOWN_LP_SOLVER")
    (LPSolver::GLPK_SOLVER, "GLPK_SOLVER")
    (LPSolver::SCIP_SOLVER, "SCIP_SOLVER")
    (LPSolver::LP_SOLVER_TYPE_END, "LP_SOLVER_TYPE_END")
    ;

LPSolver::~LPSolver()
{}

LPSolver::Ptr LPSolver::getInstance(LPSolver::Type solverType)
{
    switch(solverType)
    {
        case GLPK_SOLVER:
            return dynamic_pointer_cast<LPSolver>( make_shared<GLPKSolver>() );
#ifdef WITH_SCIP
        case SCIP_SOLVER:
            return dynamic_pointer_cast<LPSolver>( make_shared<ScipSolver>() );
#endif
        default:
            throw std::invalid_argument("graph_analysis::algorithms::LPSolver::getInstance: unknown solver type provided");

    }
}

std::string LPSolver::getVariableNameByColumnIdx(uint32_t idx) const
{
    std::stringstream ss;
    ss << "x" << idx;
    return ss.str();
}

uint32_t LPSolver::getColumnIdxByVariableName(const std::string& varName) const
{
    uint32_t index;
    std::stringstream ss;
    ss << varName.substr(1);
    ss >> index;
    return index;
}

std::string LPSolver::saveProblemToTempfile(LPSolver::ProblemFormat format) const
{
    boost::filesystem::path tempDir = boost::filesystem::temp_directory_path();
    boost::filesystem::path temp = tempDir / boost::filesystem::unique_path();
    mProblemFile = temp.native() + "-problem.lp";
    mProblemFileFormat = format;

    LOG_INFO_S << "Saving problem to: " << mProblemFile;
    saveProblem(mProblemFile, mProblemFileFormat);
    return mProblemFile;
}

std::string LPSolver::saveSolutionToTempfile(LPSolver::SolutionType format) const
{
    boost::filesystem::path tempDir = boost::filesystem::temp_directory_path();
    boost::filesystem::path temp = tempDir / boost::filesystem::unique_path();
    mSolutionFile = temp.native() + ".lp";
    mSolutionFileFormat = format;

    LOG_INFO_S << "Saving solution to: " << mSolutionFile;
    saveSolution(mSolutionFile, mSolutionFileFormat);
    return mSolutionFile;
}

} // end namespace algorithms
} // end graph_analysis