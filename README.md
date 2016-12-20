Author : Karthik Vijayakumar
Email  : karthik4294@cmu.edu

# kdtree
---------
A C++ library for building kdtrees and NN query.

# To compile
------------
## In the main project directory 

$ cd kdtree/
$ cmake .
$ make

# Run Executables
-----------------
## Go to the bin directory 
$ cd kdtree/bin/

## Run build kd-tree and write tree to file
$ ./runBuildKdTree ../config/params.cfg

## Run search kd-tree and write results to file
$ ./runNNSearch ../config/params.cfg

## Run entire pipeline without writing tree to file
$ ./runTest ../config/params.cfg

NOTE : 

1) Please execute files exactly as mentioned above
   else file paths may get messed up

2) Depends of Eigen library

3) Get writeup from the writeup folder

