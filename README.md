Author : Karthik Vijayakumar
Email  : karthik4294@cmu.edu

# kdtree
---------
A C++ library for building kdtrees and NN query.

# To compile
------------
#In the main project directory 

$ cd kdtree/
$ cmake .
$ make

# Run Executables
-----------------
# Go to the bin directory 
$ cd kdtree/bin/

## run build kd-tree and write tree to file
$ ./runBuildKdTree ../config/params.cfg

## run search kd-tree and write results to file
$ ./runNNSearch ../config/params.cfg

## run entire pipeline without writing tree to file
$ ./runTest ../config/params.cfg

NOTE : Please execute files exactly as mentioned above
       else file paths may get messed up

NOTE : Get writeup from the writeup folder

