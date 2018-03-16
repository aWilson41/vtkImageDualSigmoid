#include "vtkImageDualSigmoid.h"

#include <vtkSmartPointer.h>
#include <vtkPNGReader.h>
#include <vtkImageData.h>
#include <vtkImageActor.h>
#include <vtkImageViewer.h>
#include <vtkImageViewer2.h>
#include <vtkRenderWindowInteractor.h>

#include <vtkPNGWriter.h>

int main(int argc, char* argv[])
{
	vtkSmartPointer<vtkPNGReader> reader = vtkSmartPointer<vtkPNGReader>::New();
	reader->SetFileName(argv[1]);
	reader->Update();

	// This example does a lower threshold so upper beta doesn't need to be specified
	double* range = reader->GetOutput()->GetScalarRange();
	vtkSmartPointer<vtkImageDualSigmoid> sigmoidFilter = vtkSmartPointer<vtkImageDualSigmoid>::New();
	sigmoidFilter->SetOutputMinimum(range[0]);
	sigmoidFilter->SetOutputMaximum(range[1]);
	sigmoidFilter->SetBoundType(vtkImageDualSigmoid::LOWER);
	sigmoidFilter->SetLowerBeta(atof(argv[2]));
	sigmoidFilter->SetAlpha(10.0);
	sigmoidFilter->SetInputData(reader->GetOutput());
	sigmoidFilter->Update();

	vtkSmartPointer<vtkImageViewer2> imageViewer = vtkSmartPointer<vtkImageViewer2>::New();
	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	imageViewer->GetRenderWindow()->SetSize(1000, 800);
	imageViewer->SetInputData(sigmoidFilter->GetOutput());
	imageViewer->GetImageActor()->InterpolateOff();
	imageViewer->SetupInteractor(renderWindowInteractor);

	// Render image
	imageViewer->Render();
	renderWindowInteractor->Start();

	vtkSmartPointer<vtkPNGWriter> writer = vtkSmartPointer<vtkPNGWriter>::New();
	writer->SetInputData(sigmoidFilter->GetOutput());
	writer->SetFileName("output.png");
	writer->Write();
}