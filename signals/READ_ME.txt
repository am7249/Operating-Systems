Name: Abdullah Mobeen
Net ID: am7249
HW on Signals

Q1) I use a for-loop to test different sleep times. 

Q3) 
3.1 ~ Minimum number of signal emission required = 6. 2 for each process as we're masking SIGUSR1 and SIGUSR2 for each process.
3.2 ~ No, because at each process we need mask for the remaining processes, which in this case is 2. So we need both SIGUSR1 and SIGUSR2. 


