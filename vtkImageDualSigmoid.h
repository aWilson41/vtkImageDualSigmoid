#pragma once

#include <vtkThreadedImageAlgorithm.h>

class vtkImageDualSigmoid : public vtkThreadedImageAlgorithm
{
public:
	enum SigmoidType
	{
		DUAL,
		LOWER,
		UPPER
	};

public:
	static vtkImageDualSigmoid* New();
	vtkTypeMacro(vtkImageDualSigmoid, vtkThreadedImageAlgorithm);

	vtkSetMacro(Alpha, double);
	vtkGetMacro(Alpha, double);

	void SetLowerBeta(double val)
	{
		LowerBeta = val;
		MidBeta = (UpperBeta + LowerBeta) * 0.5;
		this->Modified();
	}
	vtkGetMacro(LowerBeta, double);

	void SetUpperBeta(double val)
	{
		UpperBeta = val;
		MidBeta = (UpperBeta + LowerBeta) * 0.5;
		this->Modified();
	}
	vtkGetMacro(UpperBeta, double);

	vtkGetMacro(MidBeta, double);

	void SetOutputMaximum(double val)
	{
		OutputMaximum = val;
		Range = OutputMaximum - OutputMinimum;
		this->Modified();
	}
	vtkGetMacro(OutputMaximum, double);

	void SetOutputMinimum(double val)
	{
		OutputMinimum = val;
		Range = OutputMaximum - OutputMinimum;
		this->Modified();
	}
	vtkGetMacro(OutputMinimum, double);

	vtkGetMacro(Range, double);

	vtkSetMacro(BoundType, SigmoidType);
	vtkGetMacro(BoundType, SigmoidType);

protected:
	vtkImageDualSigmoid();
	~vtkImageDualSigmoid() VTK_OVERRIDE { }

	double Alpha = 0.0;
	double LowerBeta = 0.0;
	double UpperBeta = 0.0;
	double Range = 0.0;
	double MidBeta = 0.0;
	double OutputMinimum = 0.0;
	double OutputMaximum = 0.0;
	SigmoidType BoundType;

	void ThreadedExecute(vtkImageData* inData, vtkImageData* outData, int outExt[6], int id) VTK_OVERRIDE;

private:
	vtkImageDualSigmoid(const vtkImageDualSigmoid&) VTK_DELETE_FUNCTION;
	void operator=(const vtkImageDualSigmoid&) VTK_DELETE_FUNCTION;
};