#include "vtkImageDualSigmoid.h"

#include <vtkImageData.h>
#include <vtkImageProgressIterator.h>
#include <vtkObjectFactory.h>

vtkStandardNewMacro(vtkImageDualSigmoid);

vtkImageDualSigmoid::vtkImageDualSigmoid()
{
	this->SetNumberOfInputPorts(1);
	this->SetNumberOfOutputPorts(1);
	Alpha = 1.0;
	LowerBeta = 0.0;
	UpperBeta = 0.0;
	MidBeta = 0.0;
	BoundType = LOWER;
	Range = 1.0;
	OutputMinimum = std::numeric_limits<double>::min();
	OutputMaximum = std::numeric_limits<double>::max();
}

template <class T>
void vtkImageDualSigmoidExecuteDual(vtkImageDualSigmoid* self, vtkImageData* inData, vtkImageData* outData, int outExt[6], int id, T*)
{
	vtkImageIterator<T> inIt(inData, outExt);
	vtkImageProgressIterator<T> outIt(outData, outExt, self, id);

	double upperBeta = self->GetUpperBeta();
	double lowerBeta = self->GetLowerBeta();
	double midBeta = self->GetMidBeta();
	double alpha = self->GetAlpha();
	double outputMin = self->GetOutputMinimum();
	double range = self->GetRange();

	// Loop through output pixels
	while (!outIt.IsAtEnd())
	{
		T* inSI = inIt.BeginSpan();
		T* outSI = outIt.BeginSpan();
		T* outSIEnd = outIt.EndSpan();
		while (outSI != outSIEnd)
		{
			// Piecewise function with two sigmoids
			if (*inSI > midBeta)
				*outSI = static_cast<T>(range / (1.0 + std::exp((*inSI - upperBeta) / alpha)) + outputMin);
			else
				*outSI = static_cast<T>(range / (1.0 + std::exp((lowerBeta - *inSI) / alpha)) + outputMin);

			outSI++;
			inSI++;
		}
		inIt.NextSpan();
		outIt.NextSpan();
	}
}

template <class T>
void vtkImageDualSigmoidExecuteLower(vtkImageDualSigmoid* self, vtkImageData* inData, vtkImageData* outData, int outExt[6], int id, T*)
{
	vtkImageIterator<T> inIt(inData, outExt);
	vtkImageProgressIterator<T> outIt(outData, outExt, self, id);

	double lowerBeta = self->GetLowerBeta();
	double alpha = self->GetAlpha();
	double outputMin = self->GetOutputMinimum();
	double range = self->GetRange();

	// Loop through output pixels
	while (!outIt.IsAtEnd())
	{
		T* inSI = inIt.BeginSpan();
		T* outSI = outIt.BeginSpan();
		T* outSIEnd = outIt.EndSpan();
		while (outSI != outSIEnd)
		{
			*outSI = static_cast<T>(range / (1.0 + std::exp((lowerBeta - *inSI) / alpha)) + outputMin);

			outSI++;
			inSI++;
		}
		inIt.NextSpan();
		outIt.NextSpan();
	}
}

template <class T>
void vtkImageDualSigmoidExecuteUpper(vtkImageDualSigmoid* self, vtkImageData* inData, vtkImageData* outData, int outExt[6], int id, T*)
{
	vtkImageIterator<T> inIt(inData, outExt);
	vtkImageProgressIterator<T> outIt(outData, outExt, self, id);

	double upperBeta = self->GetUpperBeta();
	double alpha = self->GetAlpha();
	double outputMin = self->GetOutputMinimum();
	double range = self->GetRange();

	// Loop through output pixels
	while (!outIt.IsAtEnd())
	{
		T* inSI = inIt.BeginSpan();
		T* outSI = outIt.BeginSpan();
		T* outSIEnd = outIt.EndSpan();
		while (outSI != outSIEnd)
		{
			*outSI = static_cast<T>(range / (1.0 + std::exp((*inSI - upperBeta) / alpha)) + outputMin);

			outSI++;
			inSI++;
		}
		inIt.NextSpan();
		outIt.NextSpan();
	}
}

void vtkImageDualSigmoid::ThreadedExecute(vtkImageData* inData, vtkImageData* outData, int outExt[6], int id)
{
	// this filter expects that input is the same type as output.
	if (inData->GetScalarType() != outData->GetScalarType())
	{
		vtkErrorMacro(<< "Execute: input ScalarType, " << inData->GetScalarType() << ", must match out ScalarType " << outData->GetScalarType());
		return;
	}

	switch (BoundType)
	{
	case DUAL:
		switch (inData->GetScalarType())
		{
			vtkTemplateMacro(vtkImageDualSigmoidExecuteDual(this, inData, outData, outExt, id, static_cast<VTK_TT*>(0)));
		default:
			vtkErrorMacro(<< "Execute: Unknown input ScalarType");
			return;
		};
		break;
	case LOWER:
		switch (inData->GetScalarType())
		{
			vtkTemplateMacro(vtkImageDualSigmoidExecuteLower(this, inData, outData, outExt, id, static_cast<VTK_TT*>(0)));
		default:
			vtkErrorMacro(<< "Execute: Unknown input ScalarType");
			return;
		};
		break;
	case UPPER:
		switch (inData->GetScalarType())
		{
			vtkTemplateMacro(vtkImageDualSigmoidExecuteUpper(this, inData, outData, outExt, id, static_cast<VTK_TT*>(0)));
		default:
			vtkErrorMacro(<< "Execute: Unknown input ScalarType");
			return;
		};
		break;

	default:
		vtkErrorMacro(<< "Execute: Unknown input BoundType");
		return;
	};
}