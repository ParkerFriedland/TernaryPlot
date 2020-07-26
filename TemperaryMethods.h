/*

In the future, these methods will be seperate classes that inherit from VotingMethod,
take in OrdinalVotes instead of just taking in an array of 3 types of votes.
and return a Result instead of an int:

3 types of votes (T = approval threshold)
votes[0]: C>T>Y>M
votes[1]: M>C>T>Y
votes[2]: 50% Y>M>T>C and 50% Y>T>M>C

Though once the general cases of each method are coded into their own classes,
these can be used to compare with the general cases to test whether
they produce the same results.

*/

int TempIRV(double votes[3]);
int TempFPTP(double votes[3]);
int TempCoombs(double votes[3]);
int TempMinimax(double votes[3]);
int TempBorda(double votes[3]);
int TempBucklin(double votes[3]);
int TempApproval(double votes[3]);
int TempApprovalRunoff(double votes[3]);
int TempScore(double votes[3]);
int TempSTAR(double votes[3]);
int TempDistributed(double votes[3]);

int* TempPAV(int seats[3], double votes[3]);
int* TempSainteLaguePAV(int seats[3], double votes[3]);
int* TempEbert(int seats[3], double votes[3]);
int* TempMonroeApproval(int seats[3], double votes[3]);
int* TempSPAV(int seats[3], int numSeats, double votes[3], double k);
int* TempAllocatedApproval(int seats[3], int numSeats, double votes[3], double k);
int* TempSTV(int seats[3], int numSeats, double votes[3]);