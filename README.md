# vtkImageDualSigmoid
Threaded smooth thresholding filter for vtk using a sigmoid function.

Inputs:

 Primary input is vtkImageData
 
Options:

To specify the range of the output we can use SetOutputMaximum(double max) and SetOutputMinimum(double min). Often you just want this to be the input image range.

To specify the smoothness of the curve we can use SetAlpha(double alpha)

To specify the threshold type or bound type we can use SetBoundType(SigmoidType type). You can choose between vtkImageDualSigmoid::DUAL, LOWER, or UPPER.

To specify the threshold values we can use SetLowerBeta(double lowerBeta) and SetUpperBeta(double upperBeta). Both are needed for double bounded (dual) thresholding, lower is only needed for lower, and upper is only needed for upper.

![Alt text](https://i2.wp.com/andaharoo.files.wordpress.com/2018/03/sigmoideq.png?ssl=1&w=450)

![Alt text](https://i2.wp.com/andaharoo.files.wordpress.com/2018/03/2018-03-16-15_54_14-desmos-_-graphing-calculator.png?ssl=1&w=450)

  
The example here thresholds an image argv[1] to the specified threshold argv[2]

Example input:

![Alt text](https://i2.wp.com/andaharoo.files.wordpress.com/2018/03/test.png?ssl=1&w=450)

Example output thresholded to 180:

![Alt text](https://i2.wp.com/andaharoo.files.wordpress.com/2018/03/output.png?ssl=1&w=450)