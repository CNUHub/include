#ifndef __SupportFuncs_h
#define __SupportFuncs_h
// ========== File: SupportFuncs.h ========== 

#include <iostream.h>
#include <time.h>

const int TRUE  = 1;
const int FALSE = 0;

// Purpose: To convert seconds into hours, minutes, seconds
// Input:   Number of seconds
// Output:  hours, minutes, seconds

void SecToHMS(int sec, int& hours, int& minutes, int& seconds);

// Purpose: To print out hours, minutes seconds.
// Input:   hours, minutes, seconds
// Output:  None.

void PrintHMS(int hours, int minutes, int seconds);

// Purpose: To indicate an approx. of the % of task completed and how
//          much longer it will take to complete.
// Input:   The time at the start of the task, The percentile
//          increment.
// Output:  The next percentile.        

void TimeToCompletion(time_t BaseTime, double DeltaPercentile,
                      double& percentile);

// Purpose: To print a message and the time it takes to complete a
//          task.
// Input:   The start time of the task and the message.
// Output:  None.

void CompletionTime(time_t BaseTime, char *message);

// Purpose: To compute the minimum of two integers.
// Input:   The 2 integers.
// Output:  The minimum of the 2 integers.

int imin(int a, int b);

// Purpose: To compute the maximum of two integers.
// Input:   The 2 integers.
// Output:  The maximum of the 2 integers.

int imax(int a, int b);

// Purpose: To indicate if an integer is even.
// Input:   An integer.
// Output:  Returns TRUE if even, FALSE if odd.

int even(int i);

#endif
