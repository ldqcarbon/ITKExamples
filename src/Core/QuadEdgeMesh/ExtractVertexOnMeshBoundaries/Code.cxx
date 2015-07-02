#include "itkQuadEdgeMesh.h"
#include "itkVTKPolyDataReader.h"
#include "itkQuadEdgeMeshBoundaryEdgesMeshFunction.h"

int main( int argc, char* argv [] )
{
  if( argc != 2 )
    {
    std::cerr << "Usage: " << argv[0] << " <InputFileName>" << std::endl;
    return EXIT_FAILURE;
    }

  const unsigned int Dimension = 3;
  typedef double CoordType;

  typedef itk::QuadEdgeMesh< CoordType, Dimension > MeshType;
  typedef itk::VTKPolyDataReader< MeshType >        VTKReaderType;

  VTKReaderType::Pointer reader = VTKReaderType::New();
  reader->SetFileName( argv[1] );

  try
    {
    reader->Update();
    }
  catch( itk::ExceptionObject& e )
    {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
    }

  MeshType::Pointer mesh = reader->GetOutput();

  typedef itk::QuadEdgeMeshBoundaryEdgesMeshFunction< MeshType > BoundaryExtractorType;

  BoundaryExtractorType::Pointer extractor = BoundaryExtractorType::New();

  typedef MeshType::PointIdentifier     MeshPointIdentifier;

  typedef MeshType::QEType              MeshQEType;
  typedef MeshQEType::IteratorGeom      MeshIteratorGeom;

  typedef MeshType::EdgeListType        EdgeListType;
  typedef MeshType::EdgeListPointerType EdgeListPointer;
  typedef EdgeListType::iterator        EdgeListIterator;

  EdgeListPointer list = extractor->Evaluate( *mesh );

  if( list->empty() )
    {
    std::cerr << "There is no border on this mesh" << std::endl;
    return EXIT_FAILURE;
    }

  std::cout << "There are " << list->size() << " borders on this mesh" << std::endl;

  EdgeListIterator it = list->begin();
  const EdgeListIterator end = list->end();

  size_t i = 0;
  while( it != end )
    {
    std::cout << i << ": ";

    MeshIteratorGeom eIt = (*it)->BeginGeomLnext();
    const MeshIteratorGeom eEnd = (*it)->EndGeomLnext();

    MeshPointIdentifier id = MeshType::m_NoPoint;

    while( eIt != eEnd )
      {
      MeshQEType* qe = eIt.Value();

      if( qe->GetOrigin() != id )
        {
        std::cout << qe->GetOrigin();
        }

      id = qe->GetDestination();

      std::cout << " -> " << id;
      ++eIt;
      }

    std::cout << std::endl;

    ++it;
    }

  return EXIT_SUCCESS;
}
