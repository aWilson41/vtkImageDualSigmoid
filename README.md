# vtkImageDualSigmoid
Threaded smooth thresholding filter for vtk using a sigmoid function.

Inputs:

 Primary input is vtkImageData
 
Options:

SetOutputMaximum(double max)
 
SetOutputMinimum(double min)
 
	Using the output max and min you can specify the range of the resulting image. Usually you want this to be the original image range.
  
SetAlpha(double alpha)
 
	This is the smoothness of the curve
  
SetLowerBeta(double lowerBeta)
 
	This is the lower threshold
  
SetUpperBeta(double upperBeta)
 
	This is the upper threshold
  
SetBoundType(SigmoidType type)
 
	This needs the enum specified in the filter vtkImageDualSigmoid::DUAL, LOWER, or UPPER. Allowing you to threshold using only the lower threshold, upper threshold, or both.
  
The example here thresholds an image argv[1] to the specified threshold argv[2]

Example input

![Alt text](https://i2.wp.com/andaharoo.files.wordpress.com/2018/03/test.png?ssl=1&w=450)

Example output thresholded to 180

![Alt text](https://i2.wp.com/andaharoo.files.wordpress.com/2018/03/output.png?ssl=1&w=450)