/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

#include "itkMeshFileReader.h"
#include "itkMeshFileWriter.h"
#include "itkQuadEdgeMesh.h"

#include "itkDelaunayConformingQuadEdgeMeshFilter.h"

int main( int argc, char* argv[] )
{
  // Error message and help.
  if( argc != 3 )
    {
    std::cerr << "Usage:" <<std::endl;
    std::cerr << argv[0] << " <InputFileName> <OutputFileName>" << std::endl;
    return EXIT_FAILURE;
    }

  // Basic types.
  const unsigned int    Dimension = 3;
  typedef double        CoordType;

  typedef itk::QuadEdgeMesh< CoordType, Dimension >          MeshType;

  // Read the file in.
  typedef itk::MeshFileReader< MeshType >                    ReaderType;
  ReaderType::Pointer reader = ReaderType::New( );
  reader->SetFileName( argv[1] );

  // Process the mesh.
  MeshType::Pointer mesh = reader->GetOutput( );
  typedef itk::DelaunayConformingQuadEdgeMeshFilter< MeshType, MeshType >
  DelaunayConformFilterType;
  DelaunayConformFilterType::Pointer filter = DelaunayConformFilterType::New();
  filter->SetInput( mesh );

  // Write the output.
  typedef itk::MeshFileWriter< MeshType >                    WriterType;
  WriterType::Pointer writer = WriterType::New( );
  writer->SetInput( filter->GetOutput( ) );
  writer->SetFileName( argv[2] );

  try
    {
    writer->Update();
    }
  catch( itk::ExceptionObject & error )
    {
    std::cerr << "Error: " << error << std::endl;
    return EXIT_FAILURE;
    }

  std::cout << "Number of Edge flipped performed: "
            << filter->GetNumberOfEdgeFlips() <<std::endl;

  return EXIT_SUCCESS;
}
