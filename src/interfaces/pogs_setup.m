function pogs_setup(platform)
%% Setup script for pogs

cuda_bin = '/usr/local/cuda/bin';
cuda_lib = '/usr/local/cuda/lib';

if nargin == 0 || ~strcmp(platform, 'gpu')
  unix(sprintf('make pogs.o -f Makefile -C .. IFLAGS=-D__MEX__'));
  mex -largeArrayDims -I.. LDFLAGS='\$LDFLAGS -framework Accelerate' ...
      ../pogs.o pogs_mex.cpp
else
  unix(sprintf(['export PATH=$PATH:%s;' ...
                'export DYLD_LIBRARY_PATH=%s:$DYLD_LIBRARY_PATH;' ...
                'make pogs_cu.o -f Makefile -C .. IFLAGS=-D__MEX__;' ...
                'make pogs_cu_link.o -f Makefile -C .. IFLAGS=-D__MEX__'], ...
               cuda_bin, cuda_lib));
  mex -largeArrayDims -I.. -L/usr/local/cuda/lib -lcudart -lcublas ...
      pogs_mex.cpp ../pogs_cu.o ../pogs_cu_link.o ...
      LDFLAGS='\$LDFLAGS -stdlib=libstdc++' ...
      CXXFLAGS='\$CXXFLAGS -stdlib=libstdc++'
end

