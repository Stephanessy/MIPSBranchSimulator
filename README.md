# MIPSBranchSimulator
MIPS Branch Simulator using c++

* This is a simulation of a correlating branch predictor that makes use of 2-bit saturating counters.

* Branch Predictor Architecture: The simulator consist of <img src="https://render.githubusercontent.com/render/math?math=2^{m+k}"> 2-bit saturating counters indexed using *m* LSBs of each branch instruction and a *k* bit Branch History Register (BHR) that records the outcomes of the previous k branches. Each 2-bit saturating predictor starts in the 11 (Predict Taken with High Confidence) state and is updated as the following finite state machine. The BHR is initialized assuming the previous k branches were Taken.
![alt text](https://github.com/Stephanessy/MIPSBranchSimulator/blob/master/finite%20state%20machine.JPG)

* Config file: The config file config.txt contains a single line with the value of m and k.

* Trace file: The trace file, trace.txt, contains one branch per line. Each line has the PC for the corresponding branch (in hex format) followed by a single bit indicating Taken (1) or Not Taken (0).

* To compile the code, run: `g++ -o branchsimulator.out branchsimulator_skeleton.cpp`.
  
  To run the program, run: `./branchsimulator.out config.txt trace.txt`.
