Compute Curvature Anisotropic Diffusion
=======================================

.. index::
   single: CurvatureAnisotropicDiffusionImageFilter

Synopsis
--------

Perform anisotropic diffusion on an image.


Results
-------

.. figure:: BrainProtonDensitySlice.png
  :scale: 50%
  :alt: Input image

  Input image

.. figure:: OutputBaseline.png
  :scale: 50%
  :alt: Output image

  Output image


Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Python
......

.. literalinclude:: Code.py
   :lines: 1, 20-

Classes demonstrated
--------------------

.. breathelink:: itk::CurvatureAnisotropicDiffusionImageFilter
