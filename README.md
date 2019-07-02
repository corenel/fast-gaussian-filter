# fast-gaussian-filter
Yet a fast implementation of Gaussian filter.

## Usage

```bash
USAGE:

   ./fast_gaussian_filter  -i <string> [--] [--version] [-h]


Where:

   -i <string>,  --image <string>
     (required)  path to image file

   --,  --ignore_rest
     Ignores the rest of the labeled arguments following this flag.

   --version
     Displays version information and exits.

   -h,  --help
     Displays usage information and exits.


   Fast Gaussian Filter
```

## Benchmarks

- Intel(R) Core(TM) i7-8700K CPU @ 3.70GHz
- Ubuntu 16.04.6
- OpenCV 3.4.0
- Image shape: 590x428x3

| Methods                                                      | Execution Time (ms) |
| ------------------------------------------------------------ | ------------------- |
| OpenCV                                                       | 0.80434             |
| [StackBlur](http://vitiy.info/stackblur-algorithm-multi-threaded-blur-for-cpp/) (single core) | 3.2774              |
| [FastestBlur](http://blog.ivank.net/fastest-gaussian-blur.html) | 8.2725              |

