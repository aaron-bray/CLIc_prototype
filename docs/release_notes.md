# 0.5.0 - On-going

## Bug fixes
- Remove extra context manager class left in Tier1 folder.

## New features  
- Improve error message in Manager classes, with try/catch blocks for OpenCL error management.
- Add more unity test for manager classes.

## Miscellaneous
- Exclude throw branches from coverage analysis. This is to avoid taking in account the branche coverage of the `stl` or other library on which we do not have control. Though it makes the coverage less precise, it is a bit more honnest of the state of our API. 

# 0.4.0 - August 20th 2021

## Bug fixes
- Fixe display compiling log when error occure during program build.

## New features  
- Rework of the Data classes (`LightObject`, `Int`, `Float`, `Buffer`) into (`LightObject`, `Scalar<T>`, `Buffer`).
- Add new type for `Scalar` and `Buffer`: float, double, int, unsigned int, char, unsigned char, short, unsigned short.
- General speed up through smart pointer usage.
- Integrate `GPU` class in `Clesperanto` class.
- Add `CustomKernel` class to run kernel from source (not integrated into `Clesperanto` class, must be run from lower level).
- Improve error message details during kernel construction and compilation.

## Miscellaneous
- Rename `.h` extention to `.hpp` for the library header. Autogenerated opencl header file remain in `.h`.
- Rename `CLE` class into `Clesperanto` class for clarity.

# 0.3.0 - July 23th 2021

## Bug fixes
- Fix issue of `#include <cl2.hpp>` vs `#include <opencl.hpp>` ([#37](https://github.com/clEsperanto/CLIc_prototype/issues/37))
- Fix crossplatform OpenCL include `#include <opencl.hpp>` vs `#include <CL/opencl.hpp>` vs `#include <OpenCL/opencl.hpp>`

## New features  

- OpenCL kernels are now stored included into header instead of behind read at execution time. ([#32](https://github.com/clEsperanto/CLIc_prototype/issues/32))
- Rework of CMake project configuration
  - CMake search for OpenCL system installation: `find_package(OpenCL REQUIRED)`
  - Use [OpenCL API C++ Binding](https://github.com/KhronosGroup/OpenCL-CLHPP) submodule if not installed on system.
  - Run Python script `stringify.py` at build time for converting `.cl` into `.h`
  - Run Python script `autogeneration_script.py` at build time for generating repetivive code (e.g. `cleKernelList.h`)
  - New configuration options for building test, benchmark, code coverage, and documentations
  - Define OpenCL standard version to use (Default: 1.2)
- Rewrite of installation documentation
- Organising filters into Tiers folders
- `cleGPU` now display information on all platform and device or on specific device.
- User can now select specific device based on name.

## Miscellaneous
- Split library tests into two sets, low level for testing library classes, methods, and functions (developper oriented, unity tests, etc.), and high level to test getway operations (user oriented, clesperanto functionalities, etc.).
- Remove 2D and 3D from function call name. Dimensionability is defined by 3rd dimension parameters not equal to 0. 

# 0.2.0 - February 1st 2020 (not released)

## Bug fixes
- Fix memory leak from GPU due to a wrong object deletion

## New features
- CI github actions for testing build
- Generic benchmark for execution speed comparison between two filters
- `cleGPU` now allows save and reload compiled kernel. Avoid recompiling source if not needed. 
- Implementation of complexe filters:
  - block_enumerate
  - maximum_of_all_pixels
  - minimum_of_all_pixels
  - sum_of_all_pixels
  - difference_of_Gaussian
  - close_index_gaps_in_label_map
  - connected_component_labelling_box

## Miscellaneous

- Rework on Manager classes, now relying on [OpenCL API C++ Binding](https://github.com/KhronosGroup/OpenCL-CLHPP).
  
# 0.1.0 - November 30th 2020
First release for I2K2020 Tutorial.

## New features
- Setup of CMake configuration
- Creation of the core classes
  * Manager classes: `cleGPU`, `clePlatformManager`, `cleDeviceManager`, `cleContextManager`, `cleCommandQueueManager` 
  * Data and filters classes: `cleBuffer`, `cleKernel`
  * DataType classes: `cleLightObject`, `cleInt`, `cleFloat`
  * Data operations: `Pull`, `Push`, `Create`
- Creation of a Gateway class for users `CLE`
- Implementation of several basic filters
  * absolute
  * add_image_and_scalar
  * add_images_weighted
  * copy
  * detect_maxima
  * dilate_sphere
  * equal
  * equal_constant
  * erode_sphere
  * flag_existing_labels
  * gaussian_blur_separable
  * greater
  * greater_constant
  * greater_or_equal
  * greater_or_equal_constant
  * maximum_separable
  * maximum_x_projection
  * maximum_y_projection
  * maximum_z_projection
  * mean_separable
  * mean_sphere
  * minimum_separable
  * minimum_x_projection
  * minimum_y_projection
  * minimum_z_projection
  * nonzero_minimum_box
  * not_equal
  * not_equal_constant
  * replace_intensities
  * replace_intensity
  * set
  * set_column
  * set_nonzero_pixels_to_pixelindex
  * smaller
  * smaller_constant
  * smaller_or_equal
  * smaller_or_equal_constant
  * sobel
  * sum_reduction
  * sum_x_projection
  * sum_y_projection
  * sum_z_projection
